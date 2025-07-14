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

int n,m,a[maxn];
#define mid (l+r>>1)
int rt[maxn],mn[maxn<<5],ls[maxn<<5],rs[maxn<<5],idx;
void updata(int &nd,int nd1,int p,int w,int l=0,int r=n){
	if(!nd)nd=++idx;
	if(l==r){
		mn[nd]=w;
		return ;
	}
	if(p<=mid)updata(ls[nd],ls[nd1],p,w,l,mid),rs[nd]=rs[nd1];
	else updata(rs[nd],rs[nd1],p,w,mid+1,r),ls[nd]=ls[nd1];
	mn[nd]=min(mn[ls[nd]],mn[rs[nd]]);
}
int query(int nd,int p,int l=0,int r=n){
	if(mn[nd]>=p)return r+1;
	if(l==r)return l;
	if(mn[ls[nd]]<p)return query(ls[nd],p,l,mid);
	return query(rs[nd],p,mid+1,r);
}
#undef mid

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)updata(rt[i],rt[i-1],read(),i);
	while(m--){
		int u=read(),v=read();
		printf("%lld\n",query(rt[v],u));
	}
}
