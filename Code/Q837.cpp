#include<bits/stdc++.h>
// #define int long long
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,k,q;
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> e[maxn],g[maxn],h[maxn];
vector<int> id;
vector<pii> que[maxn];
int ans[maxn<<1];
int siz[maxn],w[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1;w[u]=0;
	for(int v:e[u])if(v!=fa&&!vis[v]){
		getrt(v,u);siz[u]+=siz[v];
		w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
vector<int> pid;
int tp[maxn];
void dfs(int u,int fa,int lst){
	pid.pb(u);siz[u]=1;tp[u]=lst;
	for(int v:e[u])if(v!=fa&&!vis[v]){
		dfs(v,u,(!lst)?v:lst);siz[u]+=siz[v];
	}
}
int dis[21][maxn];
void bfs(int k){
	int s=id[k];
	for(int u:pid)dis[k][u]=n+1;
	queue<int> q;
	dis[k][s]=0;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:g[u]){
			if(!vis[v]&&dis[k][v]==n+1)dis[k][v]=dis[k][u]+1,q.push(v);
		}
	}
	// for(int u:pid)cout<<dis[k][u]<<" ";cout<<"\n";
}
int mn[21];
void upd(int u){
	for(int i=0;i<k;i++)mn[i]=min(mn[i],dis[i][u]);
}
int ask(int u){
	int res=n+1;
	for(int i=0;i<k;i++)res=min(res,mn[i]+dis[i][u]);
	return res;
}
bool bk[maxn];
void sovle(int u){
	pid.clear();dfs(u,0,0);
	id.clear();for(int u:pid)bk[u]=1;
	for(int p:pid)if(u!=p){
		for(int v:h[p])if(bk[v]&&tp[p]!=tp[v]){id.pb(p);break;}
	}
	for(int u:pid)bk[u]=0;
	id.pb(u);k=id.size();
	// cout<<u<<" "<<k<<" "<<pid.size()<<" "<<que[u].size()<<" s\n";
	for(int i=0;i<k;i++)bfs(i),mn[i]=n+1;
	vis[u]=1;
	for(auto[id,p]:que[u]){
		if(!id)upd(p);
		else ans[id]=min(ans[id],ask(p));
	}
	for(auto[id,p]:que[u])if(p!=u){
		que[tp[p]].pb({id,p});
		// cout<<u<<" "<<p<<" "<<tp[p]<<"\n";
	}
	for(int v:e[u])if(!vis[v]){
		sum=siz[v];
		getrt(v,u);
		// cout<<u<<" "<<v<<" "<<rt<<"\n";
		if(v!=rt)que[rt]=que[v],que[v].clear();
		sovle(rt);
	}
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		g[u].pb(v),g[v].pb(u);
		if(fd(u)!=fd(v))e[u].pb(v),e[v].pb(u),f[fd(u)]=fd(v);
		else h[u].pb(v),h[v].pb(u);
	}
	sum=n;getrt(1,0);
	q=read();int qq=0;
	for(int i=1;i<=q;i++){
		int op=read(),u=read();
		if(op==1)que[rt].pb({0,u});
		else que[rt].pb({++qq,u}),ans[qq]=n+1;
	}
	sovle(rt);
	for(int i=1;i<=qq;i++)printf("%d\n",ans[i]);
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