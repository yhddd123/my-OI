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
const int maxn=300010;
const int maxm=1000010;
const int inf=1e18;
bool mbe;

int n,m,k,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxm<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis[maxn],pre[maxn],d[maxn];
vector<tuple<int,int,int>> edge;
bool vis[maxn];
int ans[maxn];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=k;i++)a[i]=read();
	for(int i=1;i<=n;i++)ans[i]=0;
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	edge.clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read()*2;
		add(u,v,w),add(v,u,w);
		edge.pb({u,v,w});
	}
	priority_queue<pii> q;
	for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=0;
	dis[1]=0,q.push({0,1});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push({-dis[v],v});
			}
		}
	}
	for(int i=1;i<=n;i++)d[i]=dis[i];
	int mx=0;for(int i=1;i<=k;i++)mx=max(mx,dis[a[i]]);
	for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=0;
	for(int i=1;i<=k;i++){
		dis[a[i]]=0,pre[a[i]]=i,q.push({0,a[i]});
	}
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;pre[v]=pre[u];
				q.push({-dis[v],v});
			}
		}
	}
	for(auto[u,v,w]:edge){
		if(pre[u]==pre[v])continue;
		if(dis[u]+w+d[v]<=mx||dis[v]+w+d[u]<=mx){
			ans[pre[u]]=max(ans[pre[u]],mx-(dis[u]+dis[v]+w)/2);
			ans[pre[v]]=max(ans[pre[v]],mx-(dis[u]+dis[v]+w)/2);
		}
	}
	for(int i=1;i<=k;i++){
		printf("%lld.%lld ",ans[i]/2,(ans[i]&1)?5:0);
	}
	puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}