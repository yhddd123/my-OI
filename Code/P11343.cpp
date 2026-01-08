#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define pii pair<int,ll>
#define fi first
#define se second
const int maxn=100010;
const ll inf=1e18;

extern std::vector<long long> travel(std::vector<long long> A,
        std::vector<int> B, std::vector<int> U, std::vector<int> V, std::vector<int> W);
    
int n;
ll a[maxn],b[maxn],lim=1e11;    
vector<pii> e[maxn];
ll dis[maxn];
ll f[maxn];
int id[maxn];
vector<pii> pos[maxn];
int siz[maxn],w[maxn],sum,grt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(auto[v,ww]:e[u]){
		if(v==fa||vis[v])continue;
		getrt(v,u);siz[u]+=siz[v];
		w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)grt=u;
}
vector<int> idd;
void dfs(int u,int fa){
	siz[u]=1;idd.pb(u);
	for(auto[v,w]:e[u]){
		if(v==fa||vis[v])continue;
		dis[v]=dis[u]+w;dfs(v,u);siz[u]+=siz[v];
	}
}
void sovle(int u){
	vis[u]=1;
	dis[u]=0;idd.clear();dfs(u,0);
	for(int p:idd)pos[p].pb({u,dis[p]});
	for(auto[v,w]:e[u]){
		if(vis[v])continue;
		sum=siz[v];getrt(v,u);sovle(grt);
	}
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct line{
	ll k,b;
	ll calc(ll x){return k*x+b;}
}tree[maxn<<7];
int lc[maxn<<7],rc[maxn<<7],idx,rt[maxn];
void updata(int &nd,ll l,ll r,line w){
	if(!nd)nd=++idx,tree[nd].b=inf;
	if(tree[nd].calc(mid)>w.calc(mid))swap(tree[nd],w);
	if(l==r)return ;
	if(tree[nd].calc(l)>w.calc(l))updata(ls,l,mid,w);
	else updata(rs,mid+1,r,w);
}
ll query(int nd,ll l,ll r,ll p){
	if(!nd)return inf;
	if(p<=mid)return min(query(ls,l,mid,p),tree[nd].calc(p));
	else return min(query(rs,mid+1,r,p),tree[nd].calc(p));
}
vector<ll> travel(vector<ll> A,vector<int> B,vector<int> U,vector<int> V,vector<int> W){
	n=A.size();
	for(int i=0;i<n;i++)a[i+1]=A[i],b[i+1]=B[i];
	for(int i=0;i<n-1;i++){
		int u=U[i]+1,v=V[i]+1,w=W[i];
		e[u].pb({v,w}),e[v].pb({u,w});
	}
	sum=n;getrt(1,0);sovle(grt);
	memset(f,0x3f,sizeof(f));f[1]=0;
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return b[u]>b[v];});
	tree[0].b=inf;
	for(int i=1;i<=n;i++){
		int u=id[i];
		// for(int j=1;j<i;j++){
			// int v=id[j];
			// f[u]=min(f[u],f[v]+a[v]+calc(u,v)*b[v]);
		// }
		for(auto[p,d]:pos[u]){
			f[u]=min(f[u],query(rt[p],0,lim,d));
		}
		for(auto[p,d]:pos[u]){
			updata(rt[p],0,lim,{b[u],f[u]+a[u]+d*b[u]});
		}
		// cout<<u<<" "<<f[u]<<" "<<rt[u]<<" "<<tree[rt[u]].k<<" "<<tree[rt[u]].b<<"\n";
	}
	for(int u=1;u<=n;u++){
		// for(int v=1;v<=n;v++)f[u]=min(f[u],f[v]+a[v]+calc(u,v)*b[v]);
		for(auto[p,d]:pos[u]){
			f[u]=min(f[u],query(rt[p],0,lim,d));
		}
	}
	vector<ll> ans(n-1);
	for(int i=2;i<=n;i++)ans[i-2]=f[i];
	return ans;
}

// void my_assert(bool p, int cs)
// {
    // if(!p)
    // {
        // if(cs == 1) puts("Wrong input");
        // if(cs == 2) puts("Length of array should be N-1");
        // exit(0);
    // }
// }
// 
// int main()
// {
    // int n;
    // my_assert(scanf("%d", &n) == 1, 1);
    // std::vector<long long> A(n);
    // std::vector<int> B(n), U(n - 1), V(n - 1), W(n - 1);
    // for(int i = 0; i < n; ++i) my_assert(scanf("%lld", &A[i]) == 1, 1);
    // for(int i = 0; i < n; ++i) my_assert(scanf("%d", &B[i]) == 1, 1);
    // for(int i = 0; i < n - 1; ++i) my_assert(scanf("%d%d%d", &U[i], &V[i], &W[i]) == 3, 1);
    // std::vector<long long> ans = travel(A, B, U, V, W);
    // my_assert((int)ans.size() == n - 1, 2);
    // for(int i = 0; i < n - 1; ++i) printf("%lld\n", ans[i]);
    // return 0;
// }
// 