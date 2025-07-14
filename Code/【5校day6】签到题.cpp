#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=3000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn];
int fa[maxn];
bool bk[maxn],vis[maxn];
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		fa[v]=u;dfs(v,u);bk[i/2]=1;
	}
}
#define ull unsigned long long
ull val[maxn],f[maxn];
map<ull,bool> mp;
mt19937 rnd(time(0));
int siz[maxn];
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(fa[v]!=u)continue;
		dfs1(v,u);f[u]^=f[v];siz[u]+=siz[v];
	}
}
int lca(int u,int v){
	if(u==v)return ;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=log2(v-u+1);
	return min(st[k][u],st[k][v-(1<<k)+1],cmp);
}
map<ull,vector<int>> a;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1);
	for(int i=1;i<=m;i++)if(!bk[i]){
		val[i]=rnd();mp[val[i]]=1;
		int u=g[i].fi,v=g[i].se;
		f[u]^=val[i],f[v]^=val[i];
	}
	dfs1(1);
	for(int i=2;i<=n;i++)mp[f[i]].pb(i);
	
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
