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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,q;
vector<int> e[maxn];
int dep[maxn],siz[maxn],son[maxn],fa[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
	for(int v:e[u]){
		if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],tp[maxn],idx;
void dfs(int u,int lst){
	dfn[u]=++idx,tp[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int v:e[u])if(v!=fa[u]&&v!=son[u]){
		dfs(v,v);
	}
}
#pragma GCC optimize("Ofast,unroll-loops")
int a[maxn];
void upd(int l,int r,int w){
	for(;l<=r;l++)a[l]+=w;
}
void que(int l,int r,int &res){
	for(;l<=r;l++)res^=a[l];
}
void upd_path(int u,int v,int w){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		upd(dfn[tp[u]],dfn[u],w);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	upd(dfn[v],dfn[u],w);
}
int que_path(int u,int v){
	int res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		que(dfn[tp[u]],dfn[u],res);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	que(dfn[v],dfn[u],res);
	return res;
}
void work(){
	n=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1);dfs(1,1);
	for(int i=1;i<=n;i++)a[dfn[i]]=i;
	while(q--){
		char ch=getchar();
		while(ch!='+'&&ch!='?')ch=getchar();
		if(ch=='+'){
			int u=read(),v=read(),w=read();
			upd_path(u,v,w);
		}
		else{
			int u=read(),v=read();
			write(que_path(u,v)),puts("");
		}
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