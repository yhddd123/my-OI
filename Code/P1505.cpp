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
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
}
int dep[maxn],siz[maxn],wt[maxn],f[maxn];
int a[maxn],p[maxn];
void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;siz[u]=1;f[u]=fa;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		a[v]=e[i].w;p[(i+1)/2]=v;
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
int sum[maxn<<2],mn[maxn<<2],mx[maxn<<2],tag[maxn<<2];
void up(int nd){
	int ls=nd<<1,rs=nd<<1|1;
	sum[nd]=sum[ls]+sum[rs];
	mn[nd]=min(mn[ls],mn[rs]);
	mx[nd]=max(mx[ls],mx[rs]);
}
void build(int nd,int l,int r){
	if(l==r){
		sum[nd]=mn[nd]=mx[nd]=a[rnk[l]];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	up(nd);
}
void push(int nd){
	tag[nd]^=1;
	sum[nd]=-sum[nd];
	mn[nd]=-mn[nd];
	mx[nd]=-mx[nd];
	swap(mn[nd],mx[nd]);
}
void down(int nd){
	int ls=nd<<1,rs=nd<<1|1;
	push(ls);push(rs);
	tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int w){
	if(l==r){
		sum[nd]=mn[nd]=mx[nd]=w;
		tag[nd]=0;
		return ;
	}
	if(tag[nd])down(nd);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,w);
	else updata(rs,mid+1,r,ql,w);
	up(nd);
}
void change(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){
		push(nd);
		return ;
	}
	if(tag[nd])down(nd);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)change(ls,l,mid,ql,qr);
	if(qr>mid)change(rs,mid+1,r,ql,qr);
	up(nd);
}
void updchg(int u,int v){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		change(1,1,n,dfn[tp[u]],dfn[u]);
		u=f[tp[u]];
	}
	if(u==v)return ;
	if(dep[u]<dep[v])swap(u,v);
	change(1,1,n,dfn[v]+1,dfn[u]);
}
int querysum(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	if(tag[nd])down(nd);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return querysum(ls,l,mid,ql,qr);
	if(ql>mid)return querysum(rs,mid+1,r,ql,qr);
	return querysum(ls,l,mid,ql,qr)+querysum(rs,mid+1,r,ql,qr);
}
int asksum(int u,int v){
	if(u==v)return 0;
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
int querymn(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[nd];
	if(tag[nd])down(nd);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return querymn(ls,l,mid,ql,qr);
	if(ql>mid)return querymn(rs,mid+1,r,ql,qr);
	return min(querymn(ls,l,mid,ql,qr),querymn(rs,mid+1,r,ql,qr));
}
int askmn(int u,int v){
	if(u==v)return 0;
	int res=inf;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res=min(res,querymn(1,1,n,dfn[tp[u]],dfn[u]));
		u=f[tp[u]];
	}
	if(u==v)return res;
	if(dep[u]<dep[v])swap(u,v);
	res=min(res,querymn(1,1,n,dfn[v]+1,dfn[u]));
	return res;
}
int querymx(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	if(tag[nd])down(nd);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
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
char s[3];
int l,r;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<n;i++){
		int u,v,w;
		u=read()+1;v=read()+1;w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs1(1,0);dfs2(1,1);
	build(1,1,n);
	m=read();
	while(m--){
		scanf("%s%lld%lld",s,&l,&r);l++;r++;
		if(s[0]=='C')updata(1,1,n,dfn[p[l-1]],r-1);
		else if(s[0]=='N')updchg(l,r);
		else if(s[0]=='S')printf("%lld\n",asksum(l,r));
		else if(s[1]=='A')printf("%lld\n",askmx(l,r));
		else printf("%lld\n",askmn(l,r));
	}
}
