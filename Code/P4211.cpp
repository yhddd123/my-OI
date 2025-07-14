#include<bits/stdc++.h>
#define int long long
#define mod 201314
using namespace std;
const int maxn=50010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],m;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int dep[maxn],siz[maxn],wt[maxn],f[maxn];
int dfn[maxn],idx,rnk[maxn],tp[maxn];
void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;f[u]=fa;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
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
		if(v!=f[u]&&v!=wt[u])dfs2(v,v);
	}
}
int sum[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	sum[nd]=0;
	if(l==r)return ;
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
}
void push(int nd,int l,int r){
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	sum[ls]+=(mid-l+1)*tag[nd];sum[ls]%=mod;
	tag[ls]+=tag[nd];tag[ls]%=mod;
	sum[rs]+=(r-mid)*tag[nd];sum[rs]%=mod;
	tag[rs]+=tag[nd];tag[rs]%=mod;
	tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		sum[nd]+=w*(r-l+1);sum[nd]%=mod;
		tag[nd]+=w;tag[nd]%=mod;
		return ;
	}
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	sum[nd]=sum[ls]+sum[rs];sum[nd]%=mod;
}
void updsum(int u,int v,int w){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		updata(1,1,n,dfn[tp[u]],dfn[u],w);
		u=f[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	updata(1,1,n,dfn[v],dfn[u],w);
}
int querysum(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return querysum(ls,l,mid,ql,qr);
	if(ql>mid)return querysum(rs,mid+1,r,ql,qr);
	return (querysum(ls,l,mid,ql,qr)+querysum(rs,mid+1,r,ql,qr))%mod;
}
int asksum(int u,int v){
	int res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res+=querysum(1,1,n,dfn[tp[u]],dfn[u]);res%=mod;
		u=f[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	res+=querysum(1,1,n,dfn[v],dfn[u]);
	return res;
}
struct ask{
	int l,x;
	int id,fl;
}p[maxn<<1];
bool cmp(ask u,ask v){return u.l<v.l;}
int l,r,z;
int ans[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=2;i<=n;i++){
		int u=read()+1;
		add(u,i);
	}
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=m;i++){
		l=read()+1;r=read()+1;z=read()+1;
		p[i*2-1]={l-1,z,i,-1};p[i*2]={r,z,i,1};
	}
	build(1,1,n);
	sort(p+1,p+2*m+1,cmp);
	for(int i=1,j=1;i<=n;i++){
		if(i==1)while(j<=2*m&&!p[j].l)j++;
		updsum(1,i,1);
		while(j<=2*m&&p[j].l==i){
			ans[p[j].id]+=p[j].fl*asksum(1,p[j].x)%mod+mod;
			ans[p[j].id]%=mod;j++;
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
