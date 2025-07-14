#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1004535809
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=320010;
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
using ploy::mul;
int n,m,x,s,rt;
int a[maxn],t[maxn];
int f[35][maxn],g[maxn];
int num[maxn],val[maxn];//num->对数,val->实际
void qpow(int *a,int b){
	for(int i=0;i<m-1;i++)a[i]=0;
	a[0]=1;
	for(int i=32;~i;i--)if(b&(1ll<<i)){
		mul(f[i],a,a,m-1,m-1,m-1);
	}
}
void work(){
	n=read();m=read();x=read();s=read();
	for(int i=1;i<=s;i++)a[i]=read();
	rt=ploy::getg(m);
	for(int i=0,mul=1;i<m-1;i++,mul=mul*rt%m){
		num[mul]=i,val[i]=mul;
	}
	for(int i=1;i<=s;i++){
		if(a[i])t[num[a[i]]]++;
	}
	for(int i=0;i<m;i++)f[0][i]=t[i];
	for(int i=1;i<=32;i++){
		mul(f[i-1],f[i-1],f[i],m-1,m-1,m-1);
	}
	qpow(g,n);
	printf("%lld\n",g[num[x]]);
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
