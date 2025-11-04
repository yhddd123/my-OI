#include<bits/stdc++.h>
#define int long long
using namespace std;

static const int N = 100; // 节点数
static const int MAX_CYCLES_PER_NODE = 10; // 每点最多参与的环数

struct Edge { int u, v; };

int n;
vector<Edge> edges; // 最终边集（无向，存储u<v）
vector<vector<int>> treeAdj; // 基础生成树的邻接表
vector<int> depth;
int up[101][8]; // 2^0..2^7>=100
vector<int> cyclesOnNode; // 每个点参与的环数量
bool hasEdge[101][101];

mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

int lca(int a, int b){
	if(depth[a] < depth[b]) swap(a, b);
	int diff = depth[a] - depth[b];
	for(int k = 0; diff; k++){
		if(diff & 1) a = up[a][k];
		diff >>= 1;
	}
	if(a == b) return a;
	for(int k = 7; k >= 0; k--){
		if(up[a][k] != up[b][k]){
			a = up[a][k];
			b = up[b][k];
		}
	}
	return up[a][0];
}

void collectPathNodes(int u, int v, vector<int>& pathNodes){
	int w = lca(u, v);
	// 从u走到w（包含u，不包含w）
	int x = u;
	while(x != w){
		pathNodes.push_back(x);
		x = up[x][0];
	}
	// 加入w
	pathNodes.push_back(w);
	// 从w到v：先收集v->w（不含w），再反转
	vector<int> tmp;
	int y = v;
	while(y != w){
		tmp.push_back(y);
		y = up[y][0];
	}
	reverse(tmp.begin(), tmp.end());
	for(int node : tmp) pathNodes.push_back(node);
}

void buildRandomTree(){
	// 生成1..n的随机树（每个i>1连接到[1..i-1]随机父亲）
	treeAdj.assign(n + 1, {});
	vector<int> parent(n + 1, 0);
	depth.assign(n + 1, 0);
	parent[1] = 1;
	depth[1] = 0;
	for(int i = 2; i <= n; i++){
		uniform_int_distribution<int> dist(1, i - 1);
		int p = dist(rng);
		parent[i] = p;
		treeAdj[p].push_back(i);
		treeAdj[i].push_back(p);
	}
	// 根为1，做一次BFS确定depth和up[*][0]
	queue<int> q;
	q.push(1);
	vector<int> vis(n + 1, 0);
	vis[1] = 1;
	up[1][0] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : treeAdj[u]) if(!vis[v]){
			vis[v] = 1;
			depth[v] = depth[u] + 1;
			up[v][0] = u;
			q.push(v);
		}
	}
	for(int k = 1; k < 8; k++){
		for(int v = 1; v <= n; v++) up[v][k] = up[ up[v][k-1] ][k-1];
	}
	// 将树边加入最终边集
	edges.clear();
	memset(hasEdge, 0, sizeof(hasEdge));
	for(int v = 2; v <= n; v++){
		int u = up[v][0];
		int a = min(u, v), b = max(u, v);
		edges.push_back({a, b});
		hasEdge[a][b] = hasEdge[b][a] = true;
	}
}

void tryAddCycleEdges(){
	cyclesOnNode.assign(n + 1, 0);
	// 尝试添加若干条非树边，每条边在树路径上形成恰好一个简单环
	int maxTrials = 2000; // 尝试次数上限
	int targetExtra = 50; // 目标附加边数量上限
	int added = 0;
	uniform_int_distribution<int> nodeDist(1, n);
	for(int t = 0; t < maxTrials && added < targetExtra; t++){
		int u = nodeDist(rng), v = nodeDist(rng);
		if(u == v) continue;
		int a = min(u, v), b = max(u, v);
		if(hasEdge[a][b]) continue; // 已有边
		vector<int> pathNodes; pathNodes.reserve(n);
		collectPathNodes(u, v, pathNodes);
		// 校验：路径上所有点的环数+1不超过上限
		bool ok = true;
		for(int x : pathNodes){
			if(cyclesOnNode[x] + 1 > MAX_CYCLES_PER_NODE){ ok = false; break; }
		}
		if(!ok) continue;
		// 接受本次加边
		for(int x : pathNodes) cyclesOnNode[x]++;
		edges.push_back({a, b});
		hasEdge[a][b] = hasEdge[b][a] = true;
		added++;
	}
}

void work(){
	n = N;
	buildRandomTree();
	tryAddCycleEdges();
	// 输出：n m，然后m条无向边
	cout << n << " " << (int)edges.size() << "\n";
	for(const auto &e : edges){
		cout << e.u << " " << e.v << "\n";
	}
}

signed main(){
	freopen("1.out","w",stdout);
	work();
	return 0;
}

