#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define pii pair<ll,int>
#define fi first
#define se second
const int maxn=100010;
const int maxm=maxn<<5;
const ll inf=1e18;

int n,m,idx;
vector<int> e[maxn];
vector<pii> upd[maxn];
int siz[maxn],w[maxn],sum,rt;
bool bk[maxn];
void getrt(int u,int fa){
	siz[u]=1;w[u]=0;
	for(int v:e[u]){
		if(v==fa||bk[v])continue;
		getrt(v,u);siz[u]+=siz[v];
		w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
int dep[maxn],mxd;
vector<int> id;
void dfs(int u,int fa){
	dep[u]=dep[fa]+1,mxd=max(mxd,dep[u]);id.pb(u);
	siz[u]=1;
	for(int v:e[u]){
		if(v==fa||bk[v])continue;
		dfs(v,u);siz[u]+=siz[v];
	}
}
int pid[maxn];
vector<pii> g[maxm];
vector<int> h[maxm];
void sovle(int u){
	bk[u]=1;mxd=0;id.clear();dfs(u,0);
	idx++;for(int i=0;i<mxd;i++)h[idx+i].pb(idx+i+1);
	for(int u:id)h[u+n+m].pb(idx+dep[u]);
	for(int u:id){
		for(auto[p,d]:upd[u])if(dep[u]<=d)h[idx+min(mxd,d-dep[u])].pb(p);
	}
	idx+=mxd;
	idx++;for(int i=0;i<mxd;i++)h[idx+i+1].pb(idx+i);
	for(int u:id)h[idx+dep[u]].pb(u+m);
	for(int u:id){
		for(auto[p,d]:upd[u])if(dep[u]<=d)h[p].pb(idx+min(mxd,d-dep[u]));
	}
	idx+=mxd;
	for(int v:e[u]){
		if(bk[v])continue;
		sum=siz[v];getrt(v,u);sovle(rt);
	}
}
ll dis[maxm];
bool vis[maxm];
priority_queue<pii> q;
queue<int> q1;
vector<long long> find_spread(int N, int M, vector<int> A, vector<int> B, vector<int> P, vector<int> D, vector<int> C){
	n=N,m=M;idx=2*n+m;
	for(int i=0;i<n-1;i++){
		int u=A[i]+1,v=B[i]+1;
		e[u].pb(v),e[v].pb(u);
	}
	for(int i=1;i<=m;i++){
		int p=P[i-1]+1,d=D[i-1];
		upd[p].pb({i,d});
	}
	for(int i=1;i<=n;i++){
		int w=C[i-1];
		g[i+m].pb({i+n+m,w});
	}
	dep[0]=-1;sum=n;getrt(1,0);sovle(rt);
	for(int i=1;i<=idx;i++)dis[i]=inf,vis[i]=0;
	dis[1]=0;q.push({-dis[1],1});
	auto mdf=[&](int u){
		vis[u]=1;
		for(auto[v,w]:g[u]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({-dis[v],v});
			}
		}
		for(auto v:h[u]){
			if(dis[v]>dis[u]){
				dis[v]=dis[u];
				q1.push(v);
			}
		}
	};
	// cout<<idx<<"\n";
	// for(int i=1;i<=idx;i++){
		// for(int j:h[i])cout<<i<<" "<<j<<"\n";
	// }
	while(!q.empty()||!q1.empty()){
		while(!q1.empty()){
			int u=q1.front();q1.pop();
			if(vis[u])continue;mdf(u);
		}
		if(q.empty())break;
		int u=q.top().se;q.pop();
		if(vis[u])continue;mdf(u);
	}
	vector<ll> ans(m);
	for(int i=1;i<=m;i++)ans[i-1]=(dis[i]>=inf?-1:dis[i]);
	return ans;
}

// int main() {
	// ios_base::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	// int N, M;
	// cin >> N >> M;
	// vector<int> A(N - 1), B(N - 1), P(M), D(M), C(N);
	// for (int i = 0; i < N - 1; i++)
		// cin >> A[i] >> B[i];
	// for (int i = 0; i < M; i++)
		// cin >> P[i] >> D[i];
	// for(int i = 0; i < N; i++) cin >> C[i];
	// vector<long long> ans = find_spread(N, M, A, B, P, D, C);
	// for (auto &x : ans)
		// cout << x << "\n";
// }