#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,k,d;
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
int sum[maxn<<2],lmx[maxn<<2],rmx[maxn<<2],tree[maxn<<2];
void up(int nd){
	sum[nd]=sum[ls]+sum[rs];
	tree[nd]=max({tree[ls],tree[rs],rmx[ls]+lmx[rs]});
	lmx[nd]=max(lmx[ls],sum[ls]+lmx[rs]);
	rmx[nd]=max(rmx[rs],sum[rs]+rmx[ls]);
}
void build(int nd,int l,int r){
	if(l==r){
		sum[nd]=-k;
		return ;
	}
	build(ls,l,mid);build(rs,mid+1,r);
	up(nd);
}
void updata(int nd,int l,int r,int p,int w){
	if(l==r){
		sum[nd]+=w;
		if(sum[nd]>0)lmx[nd]=rmx[nd]=tree[nd]=sum[nd];
		else lmx[nd]=rmx[nd]=tree[nd]=0;
		return ;
	}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	up(nd);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();k=read();d=read();
	build(1,1,n);
	while(m--){
		int u=read(),v=read();
		updata(1,1,n,u,v);
		if(tree[1]<=d*k)printf("TAK\n");
		else printf("NIE\n");
	}
}
