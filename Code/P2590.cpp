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

int n,a[maxn],p;
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
int sum[maxn<<2],mx[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){
		sum[nd]=mx[nd]=a[rnk[l]];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	sum[nd]=sum[ls]+sum[rs];
	mx[nd]=max(mx[ls],mx[rs]);
}
void updata(int nd,int l,int r,int ql,int w){
	if(l==r){
		sum[nd]=mx[nd]=w;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,w);
	else updata(rs,mid+1,r,ql,w);
	sum[nd]=sum[ls]+sum[rs];
	mx[nd]=max(mx[ls],mx[rs]);
}
int querymx(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return querymx(ls,l,mid,ql,qr);
	if(ql>mid)return querymx(rs,mid+1,r,ql,qr);
	return max(querymx(ls,l,mid,ql,qr),querymx(rs,mid+1,r,ql,qr));
}
int querysum(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return querysum(ls,l,mid,ql,qr);
	if(ql>mid)return querysum(rs,mid+1,r,ql,qr);
	return querysum(ls,l,mid,ql,qr)+querysum(rs,mid+1,r,ql,qr);
}
int askmx(int u,int v){
	int res=-inf;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res=max(res,querymx(1,1,n,dfn[tp[u]],dfn[u]));
		u=f[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	res=max(res,querymx(1,1,n,dfn[v],dfn[u]));
	return res;
}
int asksum(int u,int v){
	int res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res+=querysum(1,1,n,dfn[tp[u]],dfn[u]);
		u=f[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	res+=querysum(1,1,n,dfn[v],dfn[u]);
	return res;
}
char s[7];
int l,r;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs1(1,0);dfs2(1,1);
	build(1,1,n);
	p=read();
	while(p--){
		scanf("%s",s);l=read();r=read();
		if(s[1]=='H')updata(1,1,n,dfn[l],r);
		else if(s[1]=='M')printf("%lld\n",askmx(l,r));
		else printf("%lld\n",asksum(l,r));
	}
}
