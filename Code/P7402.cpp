#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,q,a[maxn];
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	int tree[maxn<<2][2][2];
	void push(int nd,int p){
		for(int i=0;i<=1;i++)for(int j=0;j<=1;j++){
			if(a[p]*a[p+1]>=0)tree[nd][i][j]=tree[ls][i][1]+tree[rs][1][j];
			else tree[nd][i][j]=max(tree[ls][i][1]+tree[rs][0][j],tree[ls][i][0]+tree[rs][1][j]);
		}
	}
	void build(int nd,int l,int r){
		if(l==r){
			tree[nd][1][1]=abs(a[l]);
			return ;
		}
		build(ls,l,mid);build(rs,mid+1,r);
		push(nd,mid);
	}
	void updata(int nd,int l,int r,int p){
		if(l==r){
			tree[nd][1][1]=abs(a[p]);
			return ;
		}
		if(p<=mid)updata(ls,l,mid,p);
		else updata(rs,mid+1,r,p);
		push(nd,mid);
	}
	int query(){
		return tree[1][1][1];
	}
#undef mid
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)a[i]=a[i+1]-a[i];
	sgt::build(1,1,n-1);
	while(q--){
		int u=read(),v=read(),w=read();
		if(u!=1){
			a[u-1]+=w;
			sgt::updata(1,1,n-1,u-1);
		}
		if(v!=n){
			a[v]-=w;
			sgt::updata(1,1,n-1,v);
		}
		printf("%lld\n",sgt::query());
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
