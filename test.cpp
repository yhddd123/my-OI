#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// ================= 优化配置 =================
const int TARGET_HOLD_NUM = 15;    // 适度增加持仓，捕捉更多机会
const int MIN_DATA_DAYS = 60;
const double CASH_RESERVE = 0.99;  // 进一步提高资金利用率
const double STOP_LOSS_RATIO = 0.06;  // 收紧止损到6%，减少亏损
const double TAKE_PROFIT_RATIO = 0.30;  // 提高止盈到30%，让利润奔跑
const double TRAILING_STOP_RATIO = 0.08;  // 收紧移动止盈到8%，保护利润

struct StockState {
    string code;
    vector<double> closes;
    vector<double> opens;
    vector<double> highs;
    vector<double> lows;
    vector<long long> volumes;
    int holdings;
    double ma5, ma10, ma20, ma60, vol_ma5, vol_ma20;
    double entry_price;
    int hold_days;
    double highest_price;  // 持仓期间最高价
    double rsi;  // RSI指标
    double momentum;  // 动量指标
    double volatility;  // 波动率
    double macd;  // MACD指标
    double macd_signal;  // MACD信号线
    double ema12, ema26;  // EMA用于MACD计算

    StockState() : holdings(0), ma5(0), ma10(0), ma20(0), ma60(0), 
                   vol_ma5(0), vol_ma20(0), entry_price(0), hold_days(0),
                   highest_price(0), rsi(50), momentum(0), volatility(0),
                   macd(0), macd_signal(0), ema12(0), ema26(0) {}

    void update_indicators() {
        int n = closes.size();
        if (n < 20) return;
        
        auto get_ma = [&](const vector<double>& v, int days) {
            double s = 0;
            for(int i=0; i<days; ++i) s += v[n-1-i];
            return s / days;
        };

        ma5 = get_ma(closes, 5);
        ma10 = get_ma(closes, 10);
        ma20 = get_ma(closes, 20);
        if (n >= 60) ma60 = get_ma(closes, 60);

        // 成交量均线
        double vs5 = 0, vs20 = 0;
        for(int i=0; i<5 && i<n; ++i) vs5 += (double)volumes[n-1-i];
        for(int i=0; i<20 && i<n; ++i) vs20 += (double)volumes[n-1-i];
        vol_ma5 = vs5 / min(5, n);
        vol_ma20 = vs20 / min(20, n);

        // 计算RSI (14日)
        if (n >= 15) {
            double gain = 0, loss = 0;
            int period = 14;
            for(int i = n-1; i >= max(1, n-period); --i) {
                double change = closes[i] - closes[i-1];
                if (change > 0) gain += change;
                else loss -= change;
            }
            if (loss > 1e-9) {
                double rs = (gain / period) / (loss / period);
                rsi = 100.0 - (100.0 / (1.0 + rs));
            } else rsi = 100;
        }

        // 计算动量 (5日收益率)
        if (n >= 6) {
            momentum = (closes[n-1] - closes[n-6]) / closes[n-6];
        }

        // 计算波动率 (20日标准差)
        if (n >= 20) {
            double mean = ma20;
            double var = 0;
            for(int i=0; i<20; ++i) {
                double diff = closes[n-1-i] - mean;
                var += diff * diff;
            }
            volatility = sqrt(var / 20.0) / mean;
        }

        // 计算MACD (12日EMA, 26日EMA, 9日信号线)
        if (n >= 26) {
            // 计算EMA12和EMA26
            double alpha12 = 2.0 / 13.0;
            double alpha26 = 2.0 / 27.0;
            
            // 初始化EMA（使用SMA）
            double sum12 = 0, sum26 = 0;
            for(int i = 0; i < 12 && i < n; ++i) sum12 += closes[n-1-i];
            for(int i = 0; i < 26 && i < n; ++i) sum26 += closes[n-1-i];
            ema12 = sum12 / min(12, n);
            ema26 = sum26 / min(26, n);
            
            // 从后往前计算EMA
            for(int i = n-2; i >= 0; --i) {
                ema12 = alpha12 * closes[i] + (1 - alpha12) * ema12;
                ema26 = alpha26 * closes[i] + (1 - alpha26) * ema26;
            }
            
            macd = ema12 - ema26;
            
            // 计算MACD信号线（9日EMA of MACD）
            if (n >= 35) {
                // 需要历史MACD值，这里简化处理
                double macd_sum = 0;
                int macd_count = 0;
                for(int i = 0; i < 9 && i < n-26; ++i) {
                    // 简化：使用当前MACD的近似值
                    macd_sum += macd;
                    macd_count++;
                }
                macd_signal = macd_count > 0 ? macd_sum / macd_count : macd;
            } else {
                macd_signal = macd;
            }
        }
    }

    // 计算买入评分
    double get_buy_score() {
        if (closes.size() < MIN_DATA_DAYS) return -1e9;
        double cp = closes.back();
        double score = 0;

        // 趋势得分 (最重要)
        if (ma5 > ma20 && ma20 > ma60) score += 35;  // 完美多头排列
        else if (ma5 > ma20 && ma10 > ma20) score += 25;  // 部分多头
        else if (ma5 > ma20) score += 15;
        else if (ma5 > ma10 && ma10 > ma20) score += 10;  // 潜在金叉
        
        // 价格位置得分
        double bias_ma20 = (cp - ma20) / ma20;
        if (bias_ma20 > 0 && bias_ma20 < 0.03) score += 25;  // 刚突破，最佳买入点
        else if (bias_ma20 > 0 && bias_ma20 < 0.05) score += 18;
        else if (bias_ma20 < 0 && bias_ma20 > -0.02) score += 20;  // 回调到均线附近，好买点
        else if (bias_ma20 < 0 && bias_ma20 > -0.03) score += 12;
        
        // 成交量得分
        double vol_ratio = (double)volumes.back() / max(vol_ma20, 1.0);
        if (vol_ratio > 2.0) score += 25;  // 显著放量
        else if (vol_ratio > 1.5) score += 18;
        else if (vol_ratio > 1.2) score += 12;
        else if (vol_ratio > 1.0) score += 5;

        // RSI得分 (40-65为最佳买入区间)
        if (rsi > 45 && rsi < 65) score += 20;
        else if (rsi > 40 && rsi < 70) score += 15;
        else if (rsi > 30 && rsi < 40) score += 10;  // 可能反弹
        else if (rsi < 30) score += 5;  // 超卖，但风险较大

        // 动量得分
        if (momentum > 0.03 && momentum < 0.10) score += 18;  // 适度上涨动量
        else if (momentum > 0.01 && momentum < 0.15) score += 12;
        else if (momentum > 0) score += 5;

        // 波动率得分 (适中波动率更好，太低可能缺乏弹性)
        if (volatility > 0.015 && volatility < 0.035) score += 12;
        else if (volatility > 0.01 && volatility < 0.05) score += 8;
        else if (volatility > 0.005 && volatility < 0.06) score += 4;

        // 价格趋势得分 (最近5日是否上涨)
        if (closes.size() >= 6) {
            double price_change = (cp - closes[closes.size()-6]) / closes[closes.size()-6];
            if (price_change > 0.02) score += 10;  // 明显上涨
            else if (price_change > 0) score += 5;
        }

        // MACD得分（添加到买入评分，适度降低权重）
        if (closes.size() >= 26) {
            if (macd > macd_signal && macd > 0) score += 12;  // MACD金叉且为正，买入信号（降低权重）
            else if (macd > macd_signal) score += 8;  // MACD金叉
            else if (macd > 0) score += 4;  // MACD为正
        }

        return score;
    }
};

// ... (全局变量与解析函数同上) ...
int N, D, L, K_MAX;
double M, ALPHA, COM_MIN, BETA, current_cash;
vector<StockState> stocks;
map<string, int> code_to_id;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string init_line;
    while(getline(cin, init_line) && init_line.empty());
    stringstream ss(init_line); string cmd;
    ss >> cmd >> N >> D >> M >> L >> ALPHA >> COM_MIN >> BETA >> K_MAX;

    current_cash = M;
    stocks.resize(N);

    // Day 0
    for (int i = 0; i < N; ++i) {
        string line; getline(cin, line);
        for (char &c : line) if (c == ',') c = ' ';
        stringstream ss2(line); 
        string dummy, code; 
        double open, high, low, close; 
        long long vol;
        ss2 >> dummy >> code >> open >> high >> low >> close >> vol;
        stocks[i].code = code;
        stocks[i].opens.push_back(open);
        stocks[i].highs.push_back(high);
        stocks[i].lows.push_back(low);
        stocks[i].closes.push_back(close);
        stocks[i].volumes.push_back(vol);
        code_to_id[code] = i;
    }

    while (true) {
        for(auto &s : stocks) s.update_indicators();
        vector<pair<string, int>> orders;

        // 计算市场整体趋势（简化，参考test1.cpp）
        double market_ma5 = 0, market_ma20 = 0;
        int market_count = 0;
        for(auto &s : stocks) {
            if (s.closes.size() >= 20) {
                market_ma5 += s.ma5;
                market_ma20 += s.ma20;
                market_count++;
            }
        }
        if (market_count > 0) {
            market_ma5 /= market_count;
            market_ma20 /= market_count;
        }
        bool bull_market = market_ma5 > market_ma20;

        // 1. 卖出逻辑（简化，参考test1.cpp）
        for (int i = 0; i < N; ++i) {
            StockState &s = stocks[i];
            if (s.holdings > 0) {
                double cp = s.closes.back();
                double profit_ratio = (cp - s.entry_price) / s.entry_price;
                bool sell = false;
                
                // 更新持仓期间最高价
                if (cp > s.highest_price) s.highest_price = cp;
                s.hold_days++;

                // 硬止损：动态止损（根据波动率调整，但不超过6%）
                double stop_loss = STOP_LOSS_RATIO;
                if (s.volatility > 0) {
                    stop_loss = min(STOP_LOSS_RATIO, max(0.05, s.volatility * 2));
                }
                if (cp < s.entry_price * (1 - stop_loss)) {
                    sell = true;
                }
                // 移动止盈：从最高点回撤超过8%（在有利市场更宽松）
                else if (s.highest_price > s.entry_price * 1.05 && 
                         cp < s.highest_price * (1 - TRAILING_STOP_RATIO)) {
                    // 如果盈利较多，放宽移动止盈条件
                    if (profit_ratio > 0.20 && bull_market) {
                        // 有利市场且盈利>20%，需要回撤更大才卖出
                        if (cp < s.highest_price * 0.85) sell = true;  // 回撤15%才卖
                    } else {
                        sell = true;
                    }
                }
                // 止盈：涨幅超过30%（在有利市场提高阈值）
                else if (profit_ratio > (bull_market ? 0.35 : TAKE_PROFIT_RATIO)) {
                    sell = true;
                }
                // 趋势破坏：MA5跌破MA20且RSI转弱（在有利市场更宽松）
                else if (s.ma5 < s.ma20 && s.rsi < 50) {
                    // 有利市场下，只有亏损或微利时才因趋势破坏卖出
                    if (bull_market && profit_ratio > 0.05) {
                        // 有利市场且盈利>5%，不因趋势破坏卖出
                    } else {
                        sell = true;
                    }
                }
                // 长期持仓但趋势转弱：持仓超过30天且MA5<MA10
                else if (s.hold_days > 30 && s.ma5 < s.ma10 && profit_ratio > 0.05) {
                    // 有利市场下，放宽条件
                    if (bull_market && profit_ratio > 0.15) {
                        // 有利市场且盈利>15%，不卖出
                    } else {
                        sell = true;
                    }
                }
                // RSI超买且价格开始回落（在有利市场更宽松）
                else if (s.rsi > 80 && cp < s.ma5) {
                    // 有利市场下，需要更高盈利才卖出
                    if (bull_market && profit_ratio < 0.15) {
                        // 有利市场但盈利<15%，不因超买卖出
                    } else {
                        sell = true;
                    }
                }

                if (sell) {
                    orders.push_back({"SELL " + s.code + " ", s.holdings});
                    double val = cp * s.holdings;
                    current_cash += (val - (max(COM_MIN, val * ALPHA) + val * BETA));
                    s.holdings = 0;
                    s.hold_days = 0;
                    s.highest_price = 0;
                }
            }
        }

        // 2. 买入逻辑（简化，参考test1.cpp）
        vector<pair<double, int>> buy_candidates;  // {score, idx}
        int cur_holds = 0;
        for(auto &s : stocks) if(s.holdings > 0) cur_holds++;

        for (int i = 0; i < N; ++i) {
            StockState &s = stocks[i];
            if (s.holdings == 0 && s.closes.size() >= MIN_DATA_DAYS) {
                double cp = s.closes.back();
                double cv = (double)s.volumes.back();
                
                // 跳过停牌股票
                if (cp < 1e-6) continue;

                // 基础条件筛选（优化：在不利市场放宽条件）
                bool basic_ok = false;
                if (bull_market) {
                    // 牛市：更激进，允许MA5刚上穿MA20或MACD金叉
                    basic_ok = (s.ma5 > s.ma20 || (s.ma5 > s.ma10 && s.ma10 > s.ma20) ||
                                (s.closes.size() >= 26 && s.macd > s.macd_signal))
                                && cp > s.ma60 && cv > s.vol_ma20 * 1.1;
                } else {
                    // 熊市或震荡：放宽条件，允许MACD金叉或部分多头
                    basic_ok = ((s.ma5 > s.ma20 && s.ma20 > s.ma60) ||
                               (s.ma5 > s.ma20 && s.closes.size() >= 26 && s.macd > s.macd_signal))
                                && cp > s.ma60 && cv > s.vol_ma20 * 1.15;  // 降低成交量要求
                }

                if (basic_ok) {
                    // 价格位置检查：不追高（在不利市场适当放宽）
                    double bias_ma20 = (cp - s.ma20) / s.ma20;
                    double max_bias = bull_market ? 0.06 : 0.08;  // 不利市场允许8%
                    if (bias_ma20 < max_bias) {
                        double score = s.get_buy_score();
                        // 根据市场情况动态调整评分阈值（不利市场降低要求）
                        double score_threshold = bull_market ? 55 : 58;  // 从60降到58
                        if (score > score_threshold) {  // 只考虑评分较高的股票
                            buy_candidates.push_back({-score, i});  // 负号用于降序排序
                        }
                    }
                }
            }
        }
        sort(buy_candidates.begin(), buy_candidates.end());  // 按评分从高到低

        // 根据评分分配仓位（简化，参考test1.cpp）
        for (auto &p : buy_candidates) {
            if (cur_holds >= TARGET_HOLD_NUM) break;
            int idx = p.second;
            StockState &s = stocks[idx];
            
            // 根据评分调整仓位权重（参考test1.cpp）
            double score_weight = 1.0;
            double score = -p.first;
            if (score > 80) score_weight = 1.2;  // 高分股票加仓
            else if (score > 70) score_weight = 1.0;
            else score_weight = 0.8;
            
            double target = (current_cash / (TARGET_HOLD_NUM - cur_holds)) * CASH_RESERVE * score_weight;
            double price = s.closes.back();
            int qty = (int)(target / (price * (1 + ALPHA)) / L) * L;
            
            if (qty >= L) {
                // 检查资金是否足够
                double val = price * qty;
                double cost = val + max(COM_MIN, val * ALPHA);
                if (cost <= current_cash) {
                    orders.push_back({"BUY " + s.code + " ", qty});
                    current_cash -= cost;
                    s.holdings = qty;
                    s.entry_price = price;
                    s.highest_price = price;
                    s.hold_days = 0;
                    cur_holds++;
                }
            }
        }

        for (auto &o : orders) cout << o.first << o.second << "\n";
        cout << "DONE" << endl;
        cout.flush();

        string line;
        if (!getline(cin, line) || line.rfind("FINISH", 0) == 0) break;
        
        auto process = [&](string l) {
            for (char &c : l) if (c == ',') c = ' ';
            stringstream ss3(l); 
            string dummy, code; 
            double open, high, low, close; 
            long long vol;
            ss3 >> dummy >> code >> open >> high >> low >> close >> vol;
            int id = code_to_id[code];
            stocks[id].opens.push_back(open);
            stocks[id].highs.push_back(high);
            stocks[id].lows.push_back(low);
            stocks[id].closes.push_back(close);
            stocks[id].volumes.push_back(vol);
        };
        process(line);
        for(int i=1; i<N; ++i) { getline(cin, line); process(line); }
    }
    return 0;
}