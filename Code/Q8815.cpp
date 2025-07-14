#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=110;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],sum;
int f[maxn][maxn*maxn*2],ans;
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
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),sum+=a[i];
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i;j;j--){
			for(int k=sum;k>=a[i];k--){
				(f[j][k]+=f[j-1][k-a[i]])%=mod;
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<=sum;j++)if(f[i][j]){
			int val=m;
			if(m*(n-i)>sum-j)val=(sum-j)*ksm(n-i)%mod;
			(ans+=f[i][j]*ksm(C(n,i))%mod*val)%=mod;
		}
	}
	printf("%lld\n",ans);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
