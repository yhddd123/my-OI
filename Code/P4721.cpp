#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=270010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

namespace ploy{
	inline int ksm(int a,int b=mod-2,int p=mod){
		int ans=1;
		while(b){
			if(b&1)ans=ans*a%p;
			a=a*a%p;
			b>>=1;
		}
		return ans;
	}
	const int g=3,invg=ksm(3);
	int to[maxn];
	void ntt(int *a,int n,int flag){
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int k=2;k<=n;k<<=1){
			int bas=ksm(flag==1?g:invg,(mod-1)/k),l=k>>1;
			for(int i=0;i<n;i+=k){
				int mul=1;
				for(int j=i;j<i+l;j++){
					int val=mul*a[j+l]%mod;
					a[j+l]=a[j]-val;
					if(a[j+l]<0)a[j+l]+=mod;
					a[j]=a[j]+val;
					if(a[j]>=mod)a[j]-=mod;
					mul=mul*bas%mod;
				}
			}
		}
		int invn=ksm(n);
		if(flag==-1)for(int i=0;i<n;i++)a[i]*=invn,a[i]%=mod;
	}
	int a[maxn],b[maxn];
	void mul(int *f,int *g,int *ans,int n,int m,int p=mod){
		for(int i=0;i<=n;i++)a[i]=f[i];
		for(int i=0;i<=m;i++)b[i]=g[i];
		m+=n,n=1;while(n<=m)n<<=1;
		for(int i=0;i<n;i++)to[i]=(to[i>>1]>>1)|(i&1?n>>1:0);
		ntt(a,n,1);ntt(b,n,1);
		for(int i=0;i<n;i++)a[i]=a[i]*b[i]%mod;
		ntt(a,n,-1);
		for(int i=0;i<n;i++)ans[i]=0;
		for(int i=0;i<n;i++)ans[i%p]+=a[i],ans[i%p]%=mod;
		for(int i=0;i<n;i++)a[i]=b[i]=0;
	}
}
using ploy::mul;
int n,f[maxn],g[maxn];
int a[maxn],b[maxn];
void cdq(int *f,int *g,int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq(f,g,l,mid);
	for(int i=l;i<=mid;i++)a[i-l]=f[i];
	for(int i=0;i<=r-l;i++)b[i]=g[i];
	mul(a,b,a,mid-l,r-l);
	for(int i=mid+1;i<=r;i++)f[i]+=a[i-l],f[i]%=mod;
	cdq(f,g,mid+1,r);
}
void work(){
	n=read()-1;
	for(int i=1;i<=n;i++)g[i]=read();
	f[0]=1;cdq(f,g,0,n);
	for(int i=0;i<=n;i++)printf("%lld ",f[i]);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
