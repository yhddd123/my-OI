#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,q,a[maxn];
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
struct basis{
	int p[65],pos[65];
	void insert(int x,int id){
		for(int i=60;~i;i--)if(x&(1ll<<i)){
			if(!p[i]){
				p[i]=x;
				pos[i]=id;
				return ;
			}
			if(pos[i]<id)swap(p[i],x),swap(pos[i],id);
			x^=p[i];
		}
	}
	int query(int id){
		int ans=0;
		for(int i=60;~i;i--){
			if(pos[i]>=id)ans=max(ans,ans^p[i]);
		}
		return ans;
	}
}w[maxn];
int dep[maxn],to[maxn][21];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;to[u][0]=fa;
	for(int i=1;i<=20;i++)to[u][i]=to[to[u][i-1]][i-1];
	w[u].insert(a[u],dep[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		w[v]=w[u];
		dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=20;~i;i--)if(dep[v]<=dep[to[u][i]])u=to[u][i];
	if(u==v)return u;
	for(int i=20;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
basis merge(basis a,basis b){
	basis res=a;
	for(int i=60;~i;i--){
		if(b.p[i])res.insert(b.p[i],b.pos[i]);
	}
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	while(q--){
		int u=read(),v=read();
		int tp=lca(u,v);
		printf("%lld\n",merge(w[u],w[v]).query(dep[tp]));
	}
}
