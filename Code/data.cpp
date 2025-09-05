#include <bits/stdc++.h>
using namespace std;

  std::random_device rd;
  std::mt19937 rng(rd());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  n=8,m=n-1;

  // 仙人掌的边数范围：n-1 <= m <= n-1 + floor((n-1)/2)
  int maxCycles = (n - 1) / 2;
  int minEdges = max(0, n - 1);
  int maxEdges = (n == 0 ? 0 : (n - 1) + maxCycles);
  if (m < minEdges || m > maxEdges) {
    cerr << "m out of range for cactus: must satisfy n-1 <= m <= n-1+floor((n-1)/2)\n";
    return 1;
  }

  // 随机数引擎

  // 顶点编号 [1..n]
  vector<pair<int, int>> edges;
  edges.reserve(m);

  // 当前已加入的顶点集，初始只有 1 号点
  vector<int> existingVertices;
  existingVertices.reserve(n);
  existingVertices.push_back(1);

  // 可用的“新顶点池”
  vector<int> availableVertices;
  availableVertices.reserve(n - 1);
  for (int v = 2; v <= n; ++v) availableVertices.push_back(v);
  shuffle(availableVertices.begin(), availableVertices.end(), rng);

  // 需要加入的环个数
  int cyclesToAdd = m - (n - 1);

  // 先随机加入若干环（每个环附着在一个已有顶点上，使用 L-1 个新顶点，L>=3）
  for (int c = 0; c < cyclesToAdd; ++c) {
    // 选择中心顶点
    uniform_int_distribution<int> pickCenter(0, (int)existingVertices.size() - 1);
    int center = existingVertices[pickCenter(rng)];

    int remainingCycles = cyclesToAdd - c;
    int remainingNewVertices = (int)availableVertices.size();

    // 为保证剩余环最小长度 3（即各需至少 2 个新顶点），当前可用的最大环长：
    // L_max 满足 (L_max - 1) <= remainingNewVertices - 2*(remainingCycles - 1)
    int upperBound = remainingNewVertices - 2 * (remainingCycles - 1) + 1;
    // 也不能超过“现有新顶点+1”
    upperBound = min(upperBound, remainingNewVertices + 1);

    if (upperBound < 3) {
      // 防御：若随机条件导致不可行，直接退出失败
      cerr << "Internal generation error: cannot allocate cycle length.\n";
      return 1;
    }

    uniform_int_distribution<int> pickL(3, upperBound);
    int L = pickL(rng);
    int needNew = L - 1;

    if (needNew > (int)availableVertices.size()) {
      cerr << "Internal generation error: not enough vertices for cycle.\n";
      return 1;
    }

    // 取出 L-1 个新顶点
    vector<int> cyc;
    cyc.reserve(L - 1);
    for (int i = 0; i < needNew; ++i) {
      int v = availableVertices.back();
      availableVertices.pop_back();
      cyc.push_back(v);
      existingVertices.push_back(v);
    }

    // 构造环：center -> cyc[0] -> ... -> cyc[L-2] -> center
    int prev = center;
    for (int i = 0; i < (int)cyc.size(); ++i) {
      edges.emplace_back(prev, cyc[i]);
      prev = cyc[i];
    }
    edges.emplace_back(prev, center);
  }

  // 剩余的新顶点全部用“桥”连上，形成连通结构
  while (!availableVertices.empty()) {
    int u = availableVertices.back();
    availableVertices.pop_back();
    uniform_int_distribution<int> pickAttach(0, (int)existingVertices.size() - 1);
    int v = existingVertices[pickAttach(rng)];
    edges.emplace_back(u, v);
    existingVertices.push_back(u);
  }

  // 打乱边顺序增加随机性
  shuffle(edges.begin(), edges.end(), rng);

  // 输出
  cout << n << ' ' << (int)edges.size() << '\n';
  for (auto &e : edges) cout << e.first << ' ' << e.second << '\n';
  return 0;
}
