// Problem: P3950 部落冲突
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3950
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-23 18:27:48
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=300010;
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
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],siz[maxn],son[maxn],fa[maxn];
int dfn[maxn],idx,rnk[maxn],tp[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1,siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
void dfs1(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;
	if(!son[u])return ;
	dfs1(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs1(v,v);
	}
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
bool tree[maxn<<2];
void updata(int nd,int l,int r,int p){
	if(l==r){tree[nd]^=1;return ;}
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
	tree[nd]=tree[ls]|tree[rs];
}
bool query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)|query(rs,mid+1,r,ql,qr);
}
bool que(int u,int v){
	bool res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res|=query(1,1,n,dfn[tp[u]],dfn[u]);
		u=fa[tp[u]];
	}
	if(u!=v){
		if(dep[u]<dep[v])swap(u,v);
		res|=query(1,1,n,dfn[v]+1,dfn[u]);
	}
	return res;
}
int id[maxn],tim;
char op[3];
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1),dfs1(1,1);
	while(m--){
		scanf("%s",op+1);
		if(op[1]=='Q'){
			int u=read(),v=read();
			que(u,v)?printf("No\n"):printf("Yes\n");
		}
		if(op[1]=='C'){
			int u=read(),v=read();
			if(dep[u]<dep[v])swap(u,v);
			id[++tim]=u;
			updata(1,1,n,dfn[u]);
		}
		if(op[1]=='U'){
			int u=read();
			updata(1,1,n,dfn[id[u]]);
		}
	}
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
