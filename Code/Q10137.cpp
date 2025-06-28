#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<ll,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1025;
const int maxm=500010;
const int inf=2e9;
bool mbe;

int n,q;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
pii operator*(pii u,pii v){
	if(u.se==v.se)return {u.fi+v.fi,u.se};
	if(u.fi==v.fi)return {0,-1};
	if(u.fi>v.fi)return {u.fi-v.fi,u.se};
	else return {v.fi-u.fi,v.se};
}
struct seg{
	pii tree[maxn<<1];
	void build(int nd,int l,int r){
		tree[nd]={0,-1};
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void updata(int nd,int l,int r,int ql,int qr,pii w){
		if(l>=ql&&r<=qr){
			tree[nd]=tree[nd]*w;
			return ;
		}
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	}
	void down(int nd,int l,int r){
		if(l==r)return ;
		tree[ls]=tree[ls]*tree[nd],tree[rs]=tree[rs]*tree[nd];
		down(ls,l,mid),down(rs,mid+1,r);
	}
}tree[maxn<<1];
seg operator*(seg u,seg v){
	seg res;
	for(int i=1;i<(maxn<<1);i++)res.tree[i]=u.tree[i]*v.tree[i];
	return res;
}
int pos[maxn];
void build(int nd,int l,int r){
	tree[nd].build(1,1,n);
	if(l==r){pos[l]=nd;return ;}
	build(ls,l,mid),build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int ql,int qr,int qql,int qqr,pii w){
	if(l>=ql&&r<=qr)return tree[nd].updata(1,1,n,qql,qqr,w);
	if(ql<=mid)updata(ls,l,mid,ql,qr,qql,qqr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,qql,qqr,w);
}
void down(int nd,int l,int r){
	if(l==r)return ;
	tree[ls]=tree[ls]*tree[nd],tree[rs]=tree[rs]*tree[nd];
	down(ls,l,mid),down(rs,mid+1,r);
}
ll sum[maxn][maxn];
struct bit{
	ll tree[maxn][maxn];
	int lb(int x){return x&(-x);}
	void upd(int x,int y,int w){
		for(int i=x;i<=n;i+=lb(i)){
			for(int j=y;j<=n;j+=lb(j))tree[i][j]+=w;
		}
	}
	ll que(int x,int y){
		ll res=0;
		for(int i=x;i;i-=lb(i)){
			for(int j=y;j;j-=lb(j))res+=tree[i][j];
		}
		return res;
	}
}t;
vector<tuple<int,int,int,int,int>> que[maxm];
vector<pii> ask[maxm];
int ans[maxn][maxn];
void work(){
	n=read();q=read();
	build(1,1,n);
	while(q--){
		int u=read(),v=read(),x=read(),y=read(),col=read(),k=read();
		que[col].pb({u,v,x,y,k});
		sum[u][v]+=k,sum[u][y+1]-=k,sum[x+1][v]-=k,sum[x+1][y+1]+=k;
		updata(1,1,n,u,x,v,y,{k,col});
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	}
	for(int i=1;i<(maxn<<1);i++)tree[i].down(1,1,n);
	down(1,1,n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans[i][j]=tree[pos[i]].tree[pos[j]].se;
			if(~ans[i][j])ask[ans[i][j]].pb({i,j});
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)printf("%d ",ans[i][j]);puts("");
	// }
	// puts("");
	for(int i=1;i<maxm;i++)if(ask[i].size()){
		for(auto[u,v,x,y,k]:que[i]){
			t.upd(u,v,k),t.upd(u,y+1,-k),t.upd(x+1,v,-k),t.upd(x+1,y+1,k);
		}
		// cout<<i<<" "<<ask[i].size()<<"\n";
		for(auto[u,v]:ask[i]){
			if(2*t.que(u,v)<=sum[u][v])ans[u][v]=-1;
			// cout<<u<<" "<<v<<" "<<sum[u][v]<<" "<<t.que(u,v)<<"\n";
		}
		for(auto[u,v,x,y,k]:que[i]){
			t.upd(u,v,-k),t.upd(u,y+1,k),t.upd(x+1,v,k),t.upd(x+1,y+1,-k);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)printf("%d ",ans[i][j]);puts("");
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