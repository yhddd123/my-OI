#include<bits/stdc++.h>
#define mid (l+r>>1)
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int rt[maxn],idx;
int sum[maxn<<5],ls[maxn<<5],rs[maxn<<5];
void updata(int &nd,int nd1,int p,int l=1,int r=n){
	nd=++idx;
	sum[nd]=sum[nd1]+1;
	if(l==r)return ;
	if(p<=mid)updata(ls[nd],ls[nd1],p,l,mid),rs[nd]=rs[nd1];
	else updata(rs[nd],rs[nd1],p,mid+1,r),ls[nd]=ls[nd1];
}
int query(int nd,int nd1,int p,int l=1,int r=n){
	if(l==r)return sum[nd]-sum[nd1];
	if(p<=mid)return query(ls[nd],ls[nd1],p,l,mid);
	else return query(rs[nd],rs[nd1],p,mid+1,r);
}
int f[maxn][18],dep[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f[u][0]=fa;for(int i=1;i<=17;i++)f[u][i]=f[f[u][i-1]][i-1];
	updata(rt[u],rt[fa],a[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=17;i>=0;i--)if(dep[f[u][i]]>=dep[v])u=f[u][i];
	if(u==v)return u;
	for(int i=17;i>=0;i--)if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
	return f[u][0];
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	while(m--){
		int u=read(),v=read(),w=read();
		int tp=lca(u,v);
		if(query(rt[u],rt[tp],w)||query(rt[v],rt[tp],w)||a[tp]==w)printf("1");
		else printf("0");
	}
}
