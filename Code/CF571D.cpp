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

inline char readOp(){
	char ch=getchar();
	while(ch!='U'&&ch!='M'&&ch!='A'&&ch!='Z'&&ch!='Q') ch=getchar();
	return ch;
}

struct Fenwick{
	int n; vector<long long> t;
	Fenwick(){}
	Fenwick(int n):n(n),t(n+1,0){}
	inline void add(int i,long long v){
		for(; i<=n; i+=i&-i) t[i]+=v;
	}
	inline long long sum(int i){
		long long r=0; for(; i>0; i-=i&-i) r+=t[i]; return r;
	}
};

struct DSU{
	vector<int> fa;
	DSU(){}
	DSU(int n):fa(n+1){ for(int i=1;i<=n;i++) fa[i]=i; }
	inline int find(int x){ return fa[x]==x?x:fa[x]=find(fa[x]); }
	inline void unite(int x,int y){ x=find(x); y=find(y); if(x!=y) fa[y]=x; }
};

signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	int n=read(), m=read();

	int maxNodes = n + m + 5;
	vector<vector<int>> ch1(maxNodes), ch2(maxNodes);
	vector<int> indeg1(maxNodes,0), indeg2(maxNodes,0);
	vector<vector<int>> timesA(maxNodes), timesZ(maxNodes);
	vector<vector<pii>> qOnLeaf1(n+1), qOnLeaf2(n+1);

	DSU d1(n), d2(n);
	vector<int> nodeOfRep1(n+1), nodeOfRep2(n+1);
	for(int i=1;i<=n;i++){ nodeOfRep1[i]=i; nodeOfRep2[i]=i; }
	int tot1=n, tot2=n;

	int qcnt=0;
	vector<int> qOrder; qOrder.reserve(m);
	for(int i=1;i<=m;i++){
		char op=readOp();
		if(op=='U'){
			int x=read(), y=read();
			int rx=d1.find(x), ry=d1.find(y);
			if(rx==ry) continue;
			++tot1; ch1[tot1].pb(nodeOfRep1[rx]); indeg1[nodeOfRep1[rx]]++;
			ch1[tot1].pb(nodeOfRep1[ry]); indeg1[nodeOfRep1[ry]]++;
			d1.fa[ry]=rx; nodeOfRep1[rx]=tot1;
		}else if(op=='M'){
			int x=read(), y=read();
			int rx=d2.find(x), ry=d2.find(y);
			if(rx==ry) continue;
			++tot2; ch2[tot2].pb(nodeOfRep2[rx]); indeg2[nodeOfRep2[rx]]++;
			ch2[tot2].pb(nodeOfRep2[ry]); indeg2[nodeOfRep2[ry]]++;
			d2.fa[ry]=rx; nodeOfRep2[rx]=tot2;
		}else if(op=='A'){
			int x=read();
			int rx=d1.find(x); int node=nodeOfRep1[rx];
			timesA[node].pb(i);
		}else if(op=='Z'){
			int x=read();
			int rx=d2.find(x); int node=nodeOfRep2[rx];
			timesZ[node].pb(i);
		}else if(op=='Q'){
			int x=read();
			++qcnt; qOrder.pb(qcnt);
			qOnLeaf1[x].pb({i,qcnt});
			qOnLeaf2[x].pb({i,qcnt});
		}
	}

	vector<int> lastClear(qcnt+1,0);
	{
		// pass 1 on second-type forest: compute last clear time for each query
		set<int> active;
		vector<int> roots2; roots2.reserve(tot2);
		for(int u=1; u<=tot2; u++) if(indeg2[u]==0) roots2.pb(u);
		vector<pair<int,int>> stk; stk.reserve(tot2*2);
		for(int r: roots2){
			stk.clear(); stk.pb({r,0});
			while(!stk.empty()){
				auto [u, st]=stk.back(); stk.pop_back();
				if(st==0){
					stk.pb({u,1});
					for(int t: timesZ[u]) active.insert((int)t);
					if(u<=n){
						for(auto &qq: qOnLeaf2[u]){
							int t=qq.fi, id=qq.se;
							auto it = active.upper_bound((int)t);
							if(it==active.begin()) lastClear[id]=0;
							else { --it; lastClear[id]=*it; }
						}
					}
					for(int v: ch2[u]) stk.pb({v,0});
				}else{
					for(int t: timesZ[u]) active.erase((int)t);
				}
			}
		}
	}

	// compute sizes on first-type forest
	vector<int> siz1(tot1+1,0);
	{
		vector<int> roots1; roots1.reserve(tot1);
		for(int u=1; u<=tot1; u++) if(indeg1[u]==0) roots1.pb(u);
		vector<pair<int,int>> stk; stk.reserve(tot1*2);
		for(int r: roots1){
			stk.clear(); stk.pb({r,0});
			while(!stk.empty()){
				auto [u, st]=stk.back(); stk.pop_back();
				if(st==0){
					stk.pb({u,1});
					for(int v: ch1[u]) stk.pb({v,0});
				}else{
					if(u<=n) siz1[u]=1;
					else{
						int s=0; for(int v: ch1[u]) s+=siz1[v]; siz1[u]=s;
					}
				}
			}
		}
	}

	// pass 2 on first-type forest: apply A along path and answer Q using Fenwick over time
	vector<long long> ans(qcnt+1,0);
	{
		Fenwick bit((int)m+2);
		vector<int> roots1; roots1.reserve(tot1);
		for(int u=1; u<=tot1; u++) if(indeg1[u]==0) roots1.pb(u);
		vector<pair<int,int>> stk; stk.reserve(tot1*2);
		for(int r: roots1){
			stk.clear(); stk.pb({r,0});
			while(!stk.empty()){
				auto [u, st]=stk.back(); stk.pop_back();
				if(st==0){
					stk.pb({u,1});
					if(!timesA[u].empty()){
						long long w = siz1[u];
						for(int t: timesA[u]) bit.add((int)t, w);
					}
					if(u<=n){
						for(auto &qq: qOnLeaf1[u]){
							int t=qq.fi, id=qq.se;
							ans[id] = bit.sum((int)t) - bit.sum((int)lastClear[id]);
						}
					}
					for(int v: ch1[u]) stk.pb({v,0});
				}else{
					if(!timesA[u].empty()){
						long long w = siz1[u];
						for(int t: timesA[u]) bit.add((int)t, -w);
					}
				}
			}
		}
	}

	for(int i=1;i<=qcnt;i++){
		printf("%lld\n", ans[i]);
	}
	return 0;
}