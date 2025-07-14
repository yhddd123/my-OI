#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 20170408
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=210;
const int maxm=20000010;
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
	void times(int *f,int *g,int *ans,int n,int m,int p=mod){
		for(int i=0;i<=n;i++)a[i]=f[i];
		for(int i=0;i<=m;i++)b[i]=g[i];
		n+=m;
		for(int i=0;i<=n;i++)ans[i]=0;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i;j++)ans[i%p]+=a[j]*b[i-j]%mod;
			ans[i%p]%=mod;
		}
		for(int i=0;i<=n;i++)a[i]=b[i]=0;
	}
	
	int gcd(int a,int b){
		if(a%b==0)return b;
		return gcd(b,a%b);
	}
	bool check(int x,int n){
//		int m=phi[n];
		int m=n-1;
		for(int i=2;i*i<=m;i++)if(m%i==0){
			if(ksm(x,i,n)==1||ksm(x,m/i,n)==1)return false;
		}
		return true;
	}
	int getg(int n){
		if(n==2)return 1;
		for(int i=2;i<n;i++)if(gcd(i,n)==1&&check(i,n))return i;
		return -1;
	}
}
int pre[maxm],cnt;
bool vis[maxm];
void s(int n){
	vis[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0)break;
		}
	}
}
using ploy::times;
int n,m,p;
int f[33][maxn];
int dp[maxn],g[maxn];
void qpow(int *a,int b){
	a[0]=1;
	for(int i=32;~i;i--)if(b&(1ll<<i))times(a,f[i],a,p-1,p-1,p);
}
void work(){
	n=read();m=read();p=read();
	s(m);
	for(int i=1;i<=m;i++)f[0][i%p]++;
	for(int i=1;i<=32;i++)times(f[i-1],f[i-1],f[i],p-1,p-1,p);
	qpow(dp,n);
	mems(f,0);
	for(int i=1;i<=m;i++)if(vis[i])f[0][i%p]++;
	for(int i=1;i<=32;i++)times(f[i-1],f[i-1],f[i],p-1,p-1,p);
	qpow(g,n);
	printf("%lld\n",(dp[0]-g[0]+mod)%mod);
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
