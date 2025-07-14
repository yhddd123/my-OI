#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
struct ask{
	int u,v,opt;
}p[maxn];
int ans[maxn],ansc;
int g[maxn][2];
unordered_set<int> s;
int id(int u,int v){
	if(u>v)swap(u,v);
	return u*n+v;
}
bool vis[maxn];
int dep[maxn],siz[maxn],wt[maxn],f[maxn];
int dfn[maxn],idx,rnk[maxn],tp[maxn];
void dfs1(int u,int fa){
	vis[u]=1;
	dep[u]=dep[fa]+1;f[u]=fa;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[wt[u]])wt[u]=v;
		}
	}
}
void dfs2(int u,int t){
	dfn[u]=++idx;rnk[idx]=u;tp[u]=t;
	if(!wt[u])return ;
	dfs2(wt[u],t);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(f[v]==u&&v!=wt[u])dfs2(v,v);
	}
}
int sum[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){
		sum[nd]=1;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	sum[nd]=sum[ls]+sum[rs];
}
void push(int nd,int l,int r){
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	sum[ls]=0;tag[ls]=tag[nd];
	sum[rs]=0;tag[rs]=tag[nd];
	tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){
		sum[nd]=0;
		tag[nd]=1;
		return ;
	}
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr);
	if(qr>mid)updata(rs,mid+1,r,ql,qr);
	sum[nd]=sum[ls]+sum[rs];
}
void upd(int u,int v){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		updata(1,1,n,dfn[tp[u]],dfn[u]);
		u=f[tp[u]];
	}
	if(u==v)return ;
	if(dep[u]<dep[v])swap(u,v);
	updata(1,1,n,dfn[v]+1,dfn[u]);
}
int querysum(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return querysum(ls,l,mid,ql,qr);
	if(ql>mid)return querysum(rs,mid+1,r,ql,qr);
	return querysum(ls,l,mid,ql,qr)+querysum(rs,mid+1,r,ql,qr);
}
int asksum(int u,int v){
	int res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res+=querysum(1,1,n,dfn[tp[u]],dfn[u]);
		u=f[tp[u]];
	}
	if(u==v)return res;
	if(dep[u]<dep[v])swap(u,v);
	res+=querysum(1,1,n,dfn[v]+1,dfn[u]);
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++)g[i][0]=read(),g[i][1]=read();
	while(1){
		q++;
		p[q].opt=read();
		if(p[q].opt==-1)break;
		p[q].u=read();p[q].v=read();
		if(!p[q].opt)s.insert(id(p[q].u,p[q].v));
	}
	q--;
	for(int i=1;i<=m;i++){
		if(s.count(id(g[i][0],g[i][1])))continue;
		add(g[i][0],g[i][1]);add(g[i][1],g[i][0]);
	}
	dfs1(1,0);dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		if(s.count(id(g[i][0],g[i][1])))continue;
		if(f[g[i][0]]==g[i][1]||f[g[i][1]]==g[i][0])continue;
		upd(g[i][0],g[i][1]);
	}
	for(int i=q;i>=1;i--){
		if(p[i].opt)ans[++ansc]=asksum(p[i].u,p[i].v);
		else upd(p[i].u,p[i].v);
	}
	for(int i=ansc;i>=1;i--)printf("%lld\n",ans[i]);
}
