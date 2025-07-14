#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=300010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans,mx;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int to[maxn][22],dis[maxn],dep[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;to[u][0]=fa;
	for(int i=1;i<=21;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dis[v]=dis[u]+e[i].w;
			dfs(v,u);
		}
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=21;i>=0;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=21;i>=0;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
int f[maxn];
void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs1(v,u);
			f[u]+=f[v];
		}
	}
}
struct ask{
	int u,v,tp,len;
}p[maxn];
bool check(int x){
	memset(f,0,sizeof(f));
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(p[i].len>x){
			f[p[i].u]++,f[p[i].v]++,f[p[i].tp]-=2;
			++cnt;
		}
	}
	dfs1(1,0);
	for(int i=1;i<=tot;i+=2){
		int u=e[i].to,v=e[i+1].to;
		if(dep[u]>dep[v])swap(u,v);
		if(f[v]==cnt&&mx-e[i].w<=x)return true;
	}
	return false;
}
void solve(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		int tp=lca(u,v);
		p[i]={u,v,tp,dis[u]+dis[v]-2*dis[tp]};
		mx=max(mx,dis[u]+dis[v]-2*dis[tp]);
	}
	int l=0,r=mx;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)solve();
}
