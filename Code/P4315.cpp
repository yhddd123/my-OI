#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
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

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
	int fr;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w,u};
	head[u]=tot;
}
int dep[maxn],siz[maxn],wt[maxn],f[maxn];
int a[maxn];
void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;siz[u]=1;f[u]=fa;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		a[v]=e[i].w;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[wt[u]])wt[u]=v;
	}
}
int dfn[maxn],idx,rnk[maxn],tp[maxn];
void dfs2(int u,int t){
	dfn[u]=++idx;rnk[idx]=u;tp[u]=t;
	if(!wt[u])return ;
	dfs2(wt[u],t);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f[u]||v==wt[u])continue;
		dfs2(v,v);
	}
}
int mx[maxn<<2],tag[maxn<<2],laz[maxn<<2];
void build(int nd,int l,int r){
	laz[nd]=-1;
	if(l==r){
		mx[nd]=a[rnk[l]];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	mx[nd]=max(mx[ls],mx[rs]);
}
void change(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		mx[nd]=w;laz[nd]=w;tag[nd]=0;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(laz[nd]!=-1){
		mx[ls]=laz[nd];laz[ls]=laz[nd];tag[ls]=0;
		mx[rs]=laz[nd];laz[rs]=laz[nd];tag[rs]=0;
	}
	if(tag[nd]){
		mx[ls]+=tag[nd];tag[ls]+=tag[nd];
		mx[rs]+=tag[nd];tag[rs]+=tag[nd];
	}
	laz[nd]=-1;tag[nd]=0;
	if(ql<=mid)change(ls,l,mid,ql,qr,w);
	if(qr>mid)change(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		mx[nd]+=w;tag[nd]+=w;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(laz[nd]!=-1){
		mx[ls]=laz[nd];laz[ls]=laz[nd];tag[ls]=0;
		mx[rs]=laz[nd];laz[rs]=laz[nd];tag[rs]=0;
	}
	if(tag[nd]){
		mx[ls]+=tag[nd];tag[ls]+=tag[nd];
		mx[rs]+=tag[nd];tag[rs]+=tag[nd];
	}
	laz[nd]=-1;tag[nd]=0;
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
void updchg(int u,int v,int w){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		change(1,1,n,dfn[tp[u]],dfn[u],w);
		u=f[tp[u]];
	}
	if(u==v)return ;
	if(dep[u]<dep[v])swap(u,v);
	change(1,1,n,dfn[v]+1,dfn[u],w);
}
void updadd(int u,int v,int w){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		updata(1,1,n,dfn[tp[u]],dfn[u],w);
		u=f[tp[u]];
	}
	if(u==v)return ;
	if(dep[u]<dep[v])swap(u,v);
	updata(1,1,n,dfn[v]+1,dfn[u],w);
}
int querymx(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(laz[nd]!=-1){
		mx[ls]=laz[nd];laz[ls]=laz[nd];tag[ls]=0;
		mx[rs]=laz[nd];laz[rs]=laz[nd];tag[rs]=0;
	}
	if(tag[nd]){
		mx[ls]+=tag[nd];tag[ls]+=tag[nd];
		mx[rs]+=tag[nd];tag[rs]+=tag[nd];
	}
	laz[nd]=-1;tag[nd]=0;
	if(qr<=mid)return querymx(ls,l,mid,ql,qr);
	if(ql>mid)return querymx(rs,mid+1,r,ql,qr);
	return max(querymx(ls,l,mid,ql,qr),querymx(rs,mid+1,r,ql,qr));
}
int askmx(int u,int v){
	if(u==v)return 0;
	int res=-inf;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res=max(res,querymx(1,1,n,dfn[tp[u]],dfn[u]));
		u=f[tp[u]];
	}
	if(u==v)return res;
	if(dep[u]<dep[v])swap(u,v);
	res=max(res,querymx(1,1,n,dfn[v]+1,dfn[u]));
	return res;
}
char s[6];
int l,r,w;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<n;i++){
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs1(1,0);dfs2(1,1);
	build(1,1,n);
	while(1){
		scanf("%s",s);
		if(s[1]=='t')break;
		l=read();r=read();
		if(s[1]=='h')updchg(e[l*2].fr,e[l*2].to,r);
		else if(s[1]=='o')w=read(),updchg(l,r,w);
		else if(s[1]=='d')w=read(),updadd(l,r,w);
		else printf("%lld\n",askmx(l,r));
	}
}
