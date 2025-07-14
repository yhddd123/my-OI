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

int n,a[maxn],b[maxn];
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
	const int gen=3,invg=ksm(3);
	int to[maxn];
	void ntt(int *a,int n,int flag){
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int k=2;k<=n;k<<=1){
			int bas=ksm(flag==1?gen:invg,(mod-1)/k),l=k>>1;
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
	int inv[maxn],w[maxn];
	void ni(int *f,int *ans,int n){
		inv[0]=ksm(f[0]);
		for(int k=2;k<=(n<<1);k<<=1){
			int l=k>>1;
			for(int i=0;i<l;i++)w[i]=inv[i];
			for(int i=0;i<l;i++)inv[i]=(inv[i]<<1)%mod;
			mul(w,w,w,l-1,l-1);mul(w,f,w,k-1,k-1);
			for(int i=0;i<k;i++)inv[i]+=mod-w[i],inv[i]%=mod;
//			for(int i=0;i<=n;i++)cout<<inv[i]<<" ";cout<<"\n";
		}
		for(int i=0;i<n;i++)ans[i]=inv[i];
		mems(inv,0);mems(w,0);
	}
}
using ploy::ni;
void work(){
	n=read()-1;
	for(int i=0;i<=n;i++)a[i]=read();
	ni(a,b,n+1);
	for(int i=0;i<=n;i++)printf("%lld ",b[i]);
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
