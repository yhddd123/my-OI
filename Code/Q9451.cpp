#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=2000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans;
int mod,b[maxn],A,B;
int f[maxn];
int fac[maxn],inv[maxn],ni[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int cat(int n){return C(n,n/2)*ni[n/2+1]%mod;}
void work(){
	n=read();mod=read();b[0]=read();A=read();B=read();
	for(int i=1;i<=2*n;i++){
		b[i]=(A*b[i-1]+B)%mod;
		a[i]=(a[i-1]+b[i]+1)%mod;
	}
	fac[0]=1;for(int i=1;i<=2*n;i++)fac[i]=fac[i-1]*i%mod;
	inv[2*n]=ksm(fac[2*n]);for(int i=2*n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=2*n;i++)ni[i]=inv[i]*fac[i-1]%mod;
	for(int i=1;i<=2*n;i+=2){
		f[i+1]=f[i]=(f[i-1]+cat(i-1)*cat(2*n-i-1))%mod;
	}
	int val=cat(2*n);
	// for(int i=1;i<=2*n;i++)cout<<a[i]<<" ";cout<<"\n";
	ans=0;
	for(int i=1;i<=2*n;i++){
		// cout<<i<<" "<<f[2*n-i]<<" "<<val<<"\n";
		(ans+=(mod-a[i])*f[2*n-i]+a[i]*(val+mod-f[2*n-i]))%=mod;
	}
	ans=ans*ksm(val)%mod;
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
	
	T=read();
	while(T--)work();
}
