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
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
vector<pair<pii,int>> que[maxn];
int ans[maxn],id[maxn];
int in[maxn],out[maxn],idx,siz[maxn],w[maxn];
vector<int> rnk[maxn];
void dfs(int u,int fa){
	rnk[u].pb(in[u]=++idx);siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];w[v]=e[i].w;
		rnk[u].pb(++idx);
	}
	out[u]=idx;
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],mx[maxn<<2],tag[maxn<<2],ab[maxn<<2],bc[maxn<<2],abc[maxn<<2];
void upd(int nd,int w){
	mn[nd]+=w,mx[nd]+=w,ab[nd]-=w,bc[nd]-=w,tag[nd]+=w;
}
void down(int nd){
	upd(ls,tag[nd]),upd(rs,tag[nd]);
	tag[nd]=0;
}
void up(int nd){
	mn[nd]=min(mn[ls],mn[rs]);mx[nd]=max(mx[ls],mx[rs]);
	ab[nd]=max({ab[ls],ab[rs],mx[ls]-2*mn[rs]});
	bc[nd]=max({bc[ls],bc[rs],-2*mn[ls]+mx[rs]});
	abc[nd]=max({abc[ls],abc[rs],ab[ls]+mx[rs],mx[ls]+bc[rs]});	
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		upd(nd,w);
		return ;
	}
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	up(nd);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void work(){
	n=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=q;i++){
		int p=read(),val=read(),k=read();
		int u=e[p<<1].to,v=e[p<<1|1].to;
		if(in[u]<in[v])swap(u,v);
		// cout<<p<<" "<<u<<"\n";
		que[k].pb({{u,val-e[p<<1].w},i});
	}
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return min(siz[u],n-siz[u])>min(siz[v],n-siz[v]);});
	for(int k=n/2,i=1;k;k--){
		while(i<=n&&min(siz[id[i]],n-siz[id[i]])==k){
			// cout<<i<<" "<<id[i]<<" "<<in[id[i]]<<" "<<out[id[i]]<<" "<<w[id[i]]<<"\n";
			updata(1,1,idx,in[id[i]],out[id[i]],w[id[i]]);
			i++;
		}
		// cout<<k<<" "<<abc[1]<<" "<<mx[1]<<" "<<mn[1]<<" "<<query(1,1,idx,8,8)<<"\n";
		for(auto [p,id]:que[k]){
			if(min(siz[p.fi],n-siz[p.fi])>=k)updata(1,1,idx,in[p.fi],out[p.fi],p.se);
			ans[id]=abc[1];
			if(min(siz[p.fi],n-siz[p.fi])>=k)updata(1,1,idx,in[p.fi],out[p.fi],-p.se);
		}
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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
