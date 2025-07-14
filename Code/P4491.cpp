#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1004535809
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=400010;
const int maxm=10000010;
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

int n,m,s,lim,ans;
int fac[maxm],inv[maxm];
inline int ksm(int a,int b=mod-2,int p=mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int f[maxn],g[maxn];
int a[maxn],b[maxn];
namespace ploy{
	int g=3,invg=ksm(g);
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
		if(flag==-1)for(int i=0;i<n;i++)a[i]=a[i]*invn%mod;
	}
	int a[maxn],b[maxn];
	void mul(int *f,int *g,int *ans,int n,int m){
		for(int i=0;i<=n;i++)a[i]=f[i];
		for(int i=0;i<=m;i++)b[i]=g[i];
		m+=n,n=1;while(n<=m)n<<=1;
		for(int i=0;i<n;i++)to[i]=(to[i>>1]>>1)|(i&1?n>>1:0);
		ntt(a,n,1);ntt(b,n,1);
		for(int i=0;i<n;i++)a[i]=a[i]*b[i]%mod;
		ntt(a,n,-1);
		for(int i=0;i<n;i++)ans[i]=0;
		for(int i=0;i<n;i++)ans[i]=a[i];
		for(int i=0;i<n;i++)a[i]=b[i]=0;
	}
}
using ploy::mul;
void work(){
	n=read();m=read();s=read();lim=min(m,n/s);
	fac[0]=1;for(int i=1;i<=max(n,m);i++)fac[i]=fac[i-1]*i%mod;
	inv[max(n,m)]=ksm(fac[max(n,m)]);
	for(int i=max(n,m)-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=0;i<=lim;i++)f[i]=C(m,i)*fac[n]%mod*ksm(inv[s],i)%mod*inv[n-s*i]%mod*ksm(m-i,n-s*i)%mod;
	for(int i=0;i<=lim;i++)a[i]=f[i]*fac[i]%mod,b[i]=((i&1)?(mod-inv[i]):inv[i]);
	reverse(b,b+lim+1);
	mul(a,b,g,lim,lim);
	for(int i=0;i<=lim;i++){
		int w=read();
		ans+=g[i+lim]*inv[i]%mod*w%mod,ans%=mod;
	}
	printf("%lld\n",ans);
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
