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

int n,a[maxn],m;
#define mid (l+r>>1)
int rt[maxn],tree[maxn<<5],ls[maxn<<5],rs[maxn<<5],idx;
void updata(int &nd,int nd1,int p,int l=1,int r=inf){
	if(!nd)nd=++idx;
	tree[nd]=tree[nd1]+p;
	if(l==r)return ;
	if(p<=mid)updata(ls[nd],ls[nd1],p,l,mid),rs[nd]=rs[nd1];
	else updata(rs[nd],rs[nd1],p,mid+1,r),ls[nd]=ls[nd1];
}
int query(int ndr,int ndl,int ql,int qr,int l=1,int r=inf){
	if(l>=ql&&r<=qr)return tree[ndr]-tree[ndl];
	int res=0;
	if(ql<=mid)res+=query(ls[ndr],ls[ndl],ql,qr,l,mid);
	if(qr>mid)res+=query(rs[ndr],rs[ndl],ql,qr,mid+1,r);
	return res;
}
#undef mid

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)updata(rt[i],rt[i-1],a[i]);
	m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		int ans=1;
		while(1){
			int res=query(rt[v],rt[u-1],1,ans);
			if(res>=ans)ans=res+1;
			else break;
		}
		printf("%lld\n",ans);
	}
}
