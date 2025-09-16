#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=4000010;
const int inf=1e9;
bool mbe;

int n,k,ans;
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
inline int C(int m,int n){
	if(m<n||m<0||n<0)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int f(int i,int j){return fac[i]*fac[i-j+n-2]%mod*(n-1)%mod*inv[i-j]%mod*inv[i+n-1]%mod;}
void work(){
	n=read();k=read();ans=0;
	fac[0]=1;for(int i=1;i<=n+k;i++)fac[i]=fac[i-1]*i%mod;
	inv[n+k]=ksm(fac[n+k]);for(int i=n+k-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1,s1=0,s2=0,j=0;i<=k;i++){
		int p=i-(n+i-1)/2;
		while(j<=p){
			(s1+=C(j+n-2,n-2))%=mod,(s2+=C(j+n-2,n-2)*j)%=mod;
			j++;
		}
		int res=0;
		(res+=s1*(i+2-n)+mod-s2*2%mod)%=mod;
		// for(int j=0;j<=i-(n+i-1)/2;j++)(res+=C(j+n-2,n-2)*(i+2-2*j-n))%=mod;
		res=res*fac[i]%mod*fac[n-1]%mod*inv[i+n-1]%mod;
		res=res*n%mod;
		ans^=res*i;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}