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
const int maxn=1010;
const int inf=1e9;
bool mbe;

int n,m,s,t;
int a[maxn],b[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<2];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
vector<pii> edge;
int lw[maxn],dfn[maxn],idx,fa[maxn];
vector<int> id;
bool vis[maxn];
bool dfs(int u){
	dfn[u]=lw[u]=++idx;vis[u]=1;
	bool fl=u==t;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			fa[v]=u;fl|=dfs(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(fl)id.pb(u);
	return fl;
}
queue<int> q;
int d[maxn];
vector<int> nxt[maxn];
int st[maxn],tp;
void dfs1(int u){
	if(vis[u])return ;vis[u]=1;
	st[++tp]=u;
	for(int v:nxt[dfn[u]])dfs1(v);
}
bool Bipolar_Orientation(){
	idx=0;id.clear();dfs(s);
	for(int i=1;i<=n;i++)d[i]=0;
	for(int i:id)d[i]++;
	for(int i=1;i<=n;i++)d[fa[i]]++;
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	for(int i=1;i<=n;i++)nxt[i].clear();
	while(!q.empty()){
		int u=q.front();q.pop();
		nxt[lw[u]].pb(u),nxt[dfn[fa[u]]].pb(u);
		d[fa[u]]--;
		if(!d[fa[u]])q.push(fa[u]);
	}
	tp=0;
	for(int i=1;i<=n;i++)vis[i]=0;
	while(id.size())dfs1(id.back()),id.pop_back();
	if(st[1]!=s||st[tp]!=t)return 0;
	if(tp!=n)return 0;
	for(int i=1;i<=n;i++)vis[i]=0;
	vis[st[1]]=1;
	for(int i=2;i<=tp;i++){
		int u=st[i];bool fl=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			fl|=vis[v];
		}
		if(!fl)return 0;
		vis[u]=1;
	}
	for(int i=1;i<=n;i++)vis[i]=0;
	vis[st[tp]]=1;
	for(int i=tp-1;i;i--){
		int u=st[i];bool fl=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			fl|=vis[v];
		}
		if(!fl)return 0;
		vis[u]=1;
	}
	return 1;
}
int pre[maxn];
vector<int> pid;
void dfs2(int u){
	pii mn={inf,0};pid.pb(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		mn=min(mn,{a[v],v});
	}
	if(mn.fi<a[s])dfs2(mn.se);
}
void work(){
	n=read();m=read();s=read();t=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		edge.pb({u,v});
	}
	if(!Bipolar_Orientation()){puts("-1");return ;}
	for(int i=1;i<=n;i++)b[st[i]]=i;
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(auto[u,v]:edge){
		if(b[u]>b[v])swap(u,v);	
		add(u,v);pre[v]=u;
	}
	printf("%d\n",n-1);
	for(int i=n-1;i;i--){
		pid.clear();
		for(int u=pre[st[i]];u;u=pre[u])pid.pb(u);
		reverse(pid.begin(),pid.end());
		dfs2(st[i]);
		for(int j=1;j<pid.size();j++)swap(a[pid[j-1]],a[pid[j]]);
		printf("%d ",pid.size());for(int u:pid)printf("%d ",u);puts("");
	}
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