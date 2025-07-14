#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int N=200000;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
struct ask{
	int l,r,s;
}p[maxn];
int ans[maxn];
vector<int> a[maxn];
namespace sgt{
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
	int tree[maxn<<5],lc[maxn<<5],rc[maxn<<5],rt[maxn],idx;
	void updata(int &nd,int nd1,int l,int r,int p){
		nd=++idx,tree[nd]=tree[nd1]+1;
		if(l==r)return ;
		if(p<=mid)updata(ls,lc[nd1],l,mid,p),rs=rc[nd1];
		else updata(rs,rc[nd1],mid+1,r,p),ls=lc[nd1];
	}
	int query(int nd,int nd1,int l,int r,int k){
		if(tree[nd]-tree[nd1]<k)return m+1;
		if(l==r)return l;
		if(tree[ls]-tree[lc[nd1]]>=k)return query(ls,lc[nd1],l,mid,k);
		else return query(rs,rc[nd1],mid+1,r,k-(tree[ls]-tree[lc[nd1]]));
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)p[i]={read(),read(),read()};
	for(int i=1;i<=m;i++)a[read()].push_back(i);
	for(int i=1;i<=N;i++)if(!a[i].size())a[i].push_back(m+1);
	for(int i=1;i<=N;i++){
		sgt::rt[i]=sgt::rt[i-1];
		for(int j:a[i])sgt::updata(sgt::rt[i],sgt::rt[i],1,m+1,j);
	}
	for(int i=1;i<=n;i++){
		int t=sgt::query(sgt::rt[p[i].r],sgt::rt[p[i].l-1],1,m+1,p[i].s);
		ans[t]++;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
