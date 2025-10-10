#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=5010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int n,k,d;
int C[maxn][maxn];
// int dp[maxn][maxn];
int f[maxn],g[maxn];
int pw[maxn];
void work(){
	n=read();k=read();d=read();
	if(n==1&&k==1){puts("1");return ;}
	if(n==k){puts("0");return ;}
	// dp[0][0]=1;
	// for(int i=1;i<=k;i++){
		// for(int j=i;j<=k;j++){
			// dp[i][j]=0;
			// for(int l=1;l<=j-i+1&&l<=d;l++){
				// (dp[i][j]+=dp[i-1][j-l]*C[j-1][l-1]%mod*ksm(l,l-1)%mod*(n-k))%=mod;
			// }
		// }
	// }
	for(int i=1;i<=d&&i<=k;i++)pw[i]=ksm(i,i-1);
	f[0]=1;
	for(int j=1;j<=k;j++){
		f[j]=g[j]=0;
		for(int l=1;l<=j&&l<=d;l++){
			(f[j]+=f[j-l]*C[j-1][l-1]%mod*pw[l]%mod*(n-k))%=mod;
			(g[j]+=g[j-l]*C[j-1][l-1]%mod*pw[l]%mod*(n-k))%=mod;
		}
		(g[j]+=f[j])%=mod;
	}
	printf("%lld\n",g[k]*ksm(n-k)%mod*ksm(n,n-k-1)%mod*ksm(ksm(n,n-2))%mod);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	for(int i=0;i<=maxn-10;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	T=read();
	while(T--)work();
}