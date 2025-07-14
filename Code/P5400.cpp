#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=5000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
int add(int x,int y){
	((x+=y)>=mod)&&(x-=mod);
	return x;
}
bool Mbe;

inline int ksm(int a,int b=mod-2,int p=mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int n,m,l,k,mn;
int f[maxn],g[maxn],ing[maxn];
void work(){
	n=read();m=read();l=read();k=read();mn=min({n,m,l});
	f[0]=ing[0]=1;
	for(int i=1;i<=mn;i++){
		f[i]=f[i-1]*(n-i+1)%mod*(m-i+1)%mod*(l-i+1)%mod;
		g[i]=add(n*m%mod*l%mod,mod-(n-i)*(m-i)%mod*(l-i)%mod);
		ing[i]=ing[i-1]*g[i]%mod;
	}
	ing[mn]=ksm(ing[mn]);
	for(int i=mn-1;i;i--)ing[i]=ing[i+1]*g[i+1]%mod;
	int ans=0;for(int i=k;i<=mn;i++){
		if((i-k)&1)ans=add(ans,mod-C(i,k)*f[i]%mod*ing[i]%mod);
		else ans=add(ans,C(i,k)*f[i]%mod*ing[i]%mod);
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	fac[0]=1;for(int i=1;i<=maxn-10;i++)fac[i]=fac[i-1]*i%mod;
	inv[maxn-10]=ksm(fac[maxn-10]);
	for(int i=maxn-11;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	T=read();
	while(T--)work();
}
