#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=50010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,p,c,a[maxn],cnt=1;
map<int,int> mp,idx;
int ph(int n){
	int x=n,res=n;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			while(x%i==0)x/=i;
			res=res*(i-1)/i;
		}
	}
	if(x>1)res=res*(x-1)/x;
	return mp[n]=res;
}
int pw[55][maxn][2],bas=10000,mul;
inline int ksm(int b,int mod){
	int ans=pw[idx[mod]][b%bas][0]*pw[idx[mod]][b/bas][1];
	if(ans>=mod)ans%=mod,ans+=mod;
	return ans;
}
int s(int n,int l,int r,int mod){
	if(l==r+1){
		if(n>=mod)n%=mod,n+=mod;
		return n;
	}
	if(mod==1)return 1;
	return ksm(s(n,l+1,r,mp[mod]),mod);
}
int opt,l,r;
int tree[maxn<<2],mn[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){
		tree[nd]=a[l];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	tree[nd]=(tree[ls]+tree[rs])%p;
}
void updata(int nd,int l,int r,int ql,int qr){
	if(mn[nd]>=cnt)return ;
	if(l==r){
		mn[nd]++;
		tree[nd]=s(a[l],1,mn[nd],p)%p;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr);
	if(qr>mid)updata(rs,mid+1,r,ql,qr);
	tree[nd]=(tree[ls]+tree[rs])%p;
	mn[nd]=min(mn[ls],mn[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return (query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr))%p;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();p=read();c=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=p;i>1;i=ph(i)){
		idx[i]=++cnt;
		pw[cnt][0][0]=pw[cnt][0][1]=1;
		for(int j=1;j<=bas;j++){
			pw[cnt][j][0]=pw[cnt][j-1][0]*c;
			if(pw[cnt][j][0]>=i)pw[cnt][j][0]%=i,pw[cnt][j][0]+=i;
		}
		mul=pw[cnt][bas][0];
		for(int j=1;j<=bas;j++){
			pw[cnt][j][1]=pw[cnt][j-1][1]*mul;
			if(pw[cnt][j][1]>=i)pw[cnt][j][1]%=i,pw[cnt][j][1]+=i;
		}
	}
	build(1,1,n);
	while(m--){
		opt=read();l=read();r=read();
		if(!opt)updata(1,1,n,l,r);
		else printf("%lld\n",query(1,1,n,l,r));
	}
}
