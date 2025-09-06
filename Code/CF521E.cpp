#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n;
// 新增：并查集、树结构与LCA相关数组
struct DSU{
	vector<int> f;
	void init(int n){ f.resize(n+1); for(int i=0;i<=n;i++) f[i]=i; }
	int find(int x){ return f[x]==x?x:f[x]=find(f[x]); }
	bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; f[a]=b; return true; }
} dsu;

vector<int> tree[maxn];
vector<pii> extraEdges;
int up[20][maxn];
int depth[maxn];
int cnt[maxn];
bool vis[maxn];
bool okAns;

// 新增：Euler 序以判断子树包含关系
int tin[maxn], tout[maxn], timerClk;
inline bool inSub(int root,int x){ return tin[root]<=tin[x] && tout[x]<=tout[root]; }

inline int lca(int u,int v){
	if(depth[u]<depth[v]) swap(u,v);
	int diff=depth[u]-depth[v];
	for(int k=0;k<20;k++) if((diff>>k)&1) u=up[k][u];
	if(u==v) return u;
	for(int k=19;k>=0;k--){
		if(up[k][u]!=up[k][v]){ u=up[k][u]; v=up[k][v]; }
	}
	return up[0][u];
}

void buildEuler(){
	timerClk=0;
	for(int i=1;i<=n;i++) if(up[0][i]==0){
		struct Frame{int u;int p;int st;};
		stack<Frame> st; // st:0 进点, 1 出点
		st.push({i,0,0});
		while(!st.empty()){
			Frame cur=st.top(); st.pop();
			int u=cur.u, p=cur.p, stt=cur.st;
			if(stt==0){
				tin[u]=++timerClk;
				st.push({u,p,1});
				for(int v:tree[u]) if(v!=p){
					st.push({v,u,0});
				}
			}else{
				tout[u]=timerClk;
			}
		}
	}
}

// 取树上路径 u->v 的节点序列
vector<int> getTreePath(int u,int v){
	int a=u,b=v;
	vector<int> leftPart, rightPart;
	if(depth[a]<depth[b]) swap(a,b); // 保证 a 更深
	int da=depth[a], depb=depth[b];
	while(da>depb){ leftPart.pb(a); a=up[0][a]; da--; }
	while(a!=b){ leftPart.pb(a); rightPart.pb(b); a=up[0][a]; b=up[0][b]; }
	// 现在 a==b==lca
	vector<int> res;
	for(int x:leftPart) res.pb(x);
	res.pb(a);
	reverse(rightPart.begin(), rightPart.end());
	for(int x:rightPart) res.pb(x);
	// 若最初交换过 a,b（此处不影响，因为我们最终返回的是原始 u->v 的路径）
	if(u!=res.front()) reverse(res.begin(), res.end());
	return res;
}

// k 级祖先
inline int kthAncestor(int x,int k){
	for(int i=0;i<20;i++) if((k>>i)&1) x=up[i][x];
	return x;
}
// 求 x 位于 u 的哪个儿子子树（要求 x 在 u 的子树内）
inline int childOf(int u,int x){
	int needDepth=depth[u]+1;
	int diff=depth[x]-needDepth;
	if(diff<0) return -1;
	return kthAncestor(x, diff);
}

void work(){
	n=read();
	int m=read();
	// 初始化
	dsu.init(n);
	extraEdges.clear();
	for(int i=1;i<=n;i++) tree[i].clear();
	mems(up,0); mems(depth,0); mems(cnt,0); mems(vis,0);
	okAns=false;
	// 读边并构建生成森林与非树边集合
	for(int i=1;i<=m;i++){
		int u=read(), v=read();
		if(dsu.unite(u,v)){
			tree[u].pb(v);
			tree[v].pb(u);
		}else{
			extraEdges.pb({u,v});
		}
	}
	// BFS 预处理 up[0] 与 depth（按每个连通块）
	for(int i=1;i<=n;i++) if(!vis[i]){
		queue<int> q; q.push(i); vis[i]=true; up[0][i]=0; depth[i]=0;
		while(!q.empty()){
			int u=q.front(); q.pop();
			for(int v:tree[u]) if(v!=up[0][u]){
				up[0][v]=u;
				depth[v]=depth[u]+1;
				vis[v]=true;
				q.push(v);
			}
		}
	}
	// 二进制提升表
	for(int k=1;k<20;k++) for(int i=1;i<=n;i++) up[k][i]=up[k-1][ up[k-1][i] ];
	// 建 Euler 序，供判断子树包含关系
	buildEuler();
	// 树上差分：对每条非树边 (u,v) 在路径上 +1
	for(auto e: extraEdges){
		int u=e.fi, v=e.se; int w=lca(u,v);
		cnt[u]++; cnt[v]++; cnt[w]-=2;
	}
	// 记录首个满足覆盖>=2的树边 child->parent
	int chosenChild=-1, chosenParent=0;
	// 按深度从大到小累加，并检查是否有树边覆盖>=2
	vector<int> order(n); for(int i=0;i<n;i++) order[i]=i+1;
	sort(order.begin(), order.end(), [&](int a,int b){ return depth[a]>depth[b]; });
	for(int u: order){
		int p=up[0][u];
		if(p && cnt[u]>=2){ okAns=true; if(chosenChild==-1){ chosenChild=u; chosenParent=p; } }
		if(p) cnt[p]+=cnt[u];
	}
	// 若需要构造方案：找到两条覆盖 (chosenParent, chosenChild) 的非树边
	pii cover1={-1,-1}, cover2={-1,-1};
	if(!okAns){
		puts("NO");
		return;
	}
	if(chosenChild!=-1){
		int u=chosenChild;
		for(auto e: extraEdges){
			int a=e.fi, b=e.se;
			bool ia=inSub(u,a), ib=inSub(u,b);
			if(ia^ib){
				if(cover1.fi==-1) cover1=e; else { cover2=e; break; }
			}
		}
	}
	puts("YES");
	// printf("%lld %lld\n", (long long)chosenChild, (long long)chosenParent);
	// printf("%lld %lld\n", (long long)cover1.fi, (long long)cover1.se);
	// printf("%lld %lld\n", (long long)cover2.fi, (long long)cover2.se);
	// 在新图上：两条 cover 的树上整条路径（x->LCA 和 y->LCA），并添加两条非树边，然后找度数为 3 的两个点 s,t
	vector<vector<pair<int,int>>> G(n+1);
	vector<pair<int,int>> newE; newE.reserve(4*n);
	vector<char> usedNode(n+1,0);
	unordered_set<long long> seen;
	auto addEdgeNew = [&](int a,int b){ if(a==b) return; int x=min(a,b), y=max(a,b); long long key=((long long)x<<32)|y; if(seen.insert(key).second){ int id=(int)newE.size(); newE.pb({a,b}); G[a].pb({b,id}); G[b].pb({a,id}); usedNode[a]=usedNode[b]=1; } };
	auto addTreePathNew = [&](int a,int b){ int w=lca(a,b); int p=a; while(p!=w){ int q=up[0][p]; addEdgeNew(p,q); p=q; } p=b; while(p!=w){ int q=up[0][p]; addEdgeNew(p,q); p=q; } };
	// 覆盖 cover1	n
	addTreePathNew(cover1.fi, cover1.se); addEdgeNew(cover1.fi, cover1.se);
	// 覆盖 cover2
	addTreePathNew(cover2.fi, cover2.se); addEdgeNew(cover2.fi, cover2.se);
	// 统计度数并找 s,t
	vector<int> deg(n+1,0); for(int i=1;i<=n;i++) deg[i]=(int)G[i].size();
	int s=-1, t=-1; for(int i=1;i<=n;i++) if(deg[i]==3){ if(s==-1) s=i; else if(t==-1) t=i; }
	// printf("%lld %lld\n", (long long)s, (long long)t);
	// 从 s 出发找三条到 t 的路径，逐条找并标记已用边
	vector<char> usedEdge(newE.size(),0);
	auto findPath = [&](int S,int T){
		vector<int> parNode(n+1,-1), parEdge(n+1,-1);
		vector<char> vis2(n+1,0);
		stack<int> st; st.push(S); vis2[S]=1; bool found=false;
		while(!st.empty()){
			int u=st.top(); st.pop();
			if(u==T){ found=true; break; }
			for(auto pr:G[u]){
				int v=pr.fi, id=pr.se;
				if(usedEdge[id]||vis2[v]) continue;
				vis2[v]=1; parNode[v]=u; parEdge[v]=id; st.push(v);
			}
		}
		vector<int> path;
		if(!found) return path;
		vector<int> nodes; vector<int> eids;
		int cur=T; nodes.pb(cur);
		while(cur!=S){ int id=parEdge[cur]; int p=parNode[cur]; eids.pb(id); cur=p; nodes.pb(cur); }
		reverse(nodes.begin(), nodes.end()); reverse(eids.begin(), eids.end());
		for(int id: eids) usedEdge[id]=1;
		return nodes;
	};
	vector<int> P1=findPath(s,t);
	vector<int> P2=findPath(s,t);
	vector<int> P3=findPath(s,t);
	printf("%lld ", (long long)P1.size()); for(size_t i=0;i<P1.size();i++) printf("%lld%c", (long long)P1[i], i+1==P1.size()?'\n':' ');
	printf("%lld ", (long long)P2.size()); for(size_t i=0;i<P2.size();i++) printf("%lld%c", (long long)P2[i], i+1==P2.size()?'\n':' ');
	printf("%lld ", (long long)P3.size()); for(size_t i=0;i<P3.size();i++) printf("%lld%c", (long long)P3[i], i+1==P3.size()?'\n':' ');
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}