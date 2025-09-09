#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int maxm=100010;
bool mbe;

int n,m,ans;
int fa[maxn],siz[maxn],sz[maxn],d[maxn];
int dp[maxn][maxn],f[maxn];
int fac[maxm],inv[maxm];
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
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)siz[i]=1,sz[i]=d[i]=0;
	for(int i=2;i<=n;i++)fa[i]=read(),d[fa[i]]++;
	for(int i=1;i<=n;i++){
		dp[i][0]=1;for(int j=1;j<=n;j++)dp[i][j]=0;
	}
	for(int u=n;u;u--){
        siz[fa[u]]+=siz[u];
        sz[fa[u]]+=sz[u]+(!sz[u]);
        if(!sz[u])continue;
        for(int i=siz[u];i;i--)dp[u][i]=(dp[u][i-1]*(siz[u]-1)+dp[u][i]*(sz[u]+i))%mod;
        dp[u][0]=dp[u][0]*sz[u]%mod;
        if(u==1)break;
		for(int i=0;i<=siz[fa[u]]-siz[u];i++){
			for(int j=0;j<=siz[u];j++)(f[i+j]+=dp[fa[u]][i]*dp[u][j])%=mod;
		}
		for(int i=0;i<=siz[fa[u]];i++)dp[fa[u]][i]=f[i],f[i]=0;
		// cout<<u<<"\n";
		// for(int i=0;i<=siz[u];i++)cout<<dp[u][i]<<" ";cout<<"\n";
	}
    int ans=0;for(int i=0;i<=n&&i<=m;i++)(ans+=C(m,i)*fac[i]%mod*ksm(n-1,m-i)%mod*dp[1][i])%=mod;
    // cout<<ans<<"\n";
	printf("%lld\n",ans*ksm(ksm(n-1,m))%mod);
}

bool med;
int T;
signed main(){
	T=read();m=read();
	fac[0]=1;for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
	inv[m]=ksm(fac[m]);for(int i=m-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	
	while(T--)work();
}