#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const ll inf=2e14;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;ll ans;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
const int maxm=21000010;
ll tree[maxm],tag[maxm];
int lc[maxm],rc[maxm],idx;
void down(int nd){
	if(!ls)ls=++idx;
	if(!rs)rs=++idx;
	tree[ls]+=tag[nd],tag[ls]+=tag[nd];
	tree[rs]+=tag[nd],tag[rs]+=tag[nd];
	tag[nd]=0;
}
void updata(int &nd,ll l,ll r,ll p,ll w){
	if(!nd)nd=++idx;
	if(l==r){
		tree[nd]=max(tree[nd],w);
		return ;
	}
	if(tag[nd])down(nd);
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=max(tree[ls],tree[rs]);
}
ll query(int nd,ll l,ll r,ll ql,ll qr){
	if(ql>qr||!nd)return 0;
	if(l>=ql&&r<=qr)return tree[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void updata(int &nd,ll l,ll r,ll ql,ll qr,ll w){
	if(ql>qr)return ;
	if(!nd)nd=++idx;
	if(l>=ql&&r<=qr){
		tree[nd]+=w,tag[nd]+=w;
		return ;
	}
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=max(tree[ls],tree[rs]);
}
int merge(int u,int v,ll l,ll r){
	if(!u||!v)return u|v;
	if(tree[u]==tag[u])return v;
	if(tree[v]==tag[v])return u;
	if(l==r){
		tree[u]=max(tree[u],tree[v]);
		return u;
	}
	if(tag[u])down(u);
	if(tag[v])down(v);
	lc[u]=merge(lc[u],lc[v],l,mid);
	rc[u]=merge(rc[u],rc[v],mid+1,r);
	tree[u]=max(tree[lc[u]],tree[rc[u]]);
	return u;
}
ll dis[maxn];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dis[v]=dis[u]+e[i].w;dfs(v,u);
	}
}
int rt[maxn];
void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs1(v,u);
		ll v0=query(rt[v],0,inf,dis[u],inf),v1=query(rt[u],0,inf,dis[u],inf);
		// cout<<u<<" "<<v<<" "<<v0<<endl;
		// for(int i=0;i<=4;i++)cout<<query(rt[u],0,inf,i,i)<<" ";cout<<"\n";
		updata(rt[u],0,inf,0,inf,v0);
		updata(rt[v],0,inf,0,inf,v1);
		// for(int i=0;i<=4;i++)cout<<query(rt[u],0,inf,i,i)<<" ";cout<<"\n";
		if(u!=1)rt[u]=merge(rt[u],rt[v],0,inf);
	}
	// cout<<u<<" "<<tree[rt[u]]<<endl;
	// for(int i=0;i<=10;i++)cout<<query(rt[u],0,inf,i,i)<<" ";cout<<"\n";
	ans=max(ans,tree[rt[u]]);
}
ll v[maxn],l[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		int k=read(),u=read();
		for(int j=1;j<=k;j++)v[j]=read();
		for(int j=1;j<=k;j++)l[j]=read();
		for(int j=1;j<=k;j++){
			v[j]+=v[j-1],l[j]+=l[j-1];
			if(l[j]<=dis[u])updata(rt[u],0,inf,dis[u]-l[j],v[j]);
			else break;
		}
	}
	dfs1(1,0);
	printf("%lld\n",ans);
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
