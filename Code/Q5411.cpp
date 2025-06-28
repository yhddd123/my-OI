#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,m,s,t,q;
int e[maxn+2][maxn+2];
int id(int u){
	if(u==s)return n-1;
	if(u==t)return n-2;
	if(u<min(s,t))return u-1;
	if(u<max(s,t))return u-2;
	return u-3;
}
int dp[1<<maxn][maxn+1],f[1<<maxn],g[1<<maxn];
void fwt(int *a,int n,int w){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)(a[j+k]+=a[j]*w)%=mod;
		}
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1],ni[maxn+1];
void xorexp(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)gg[i]=0;
		for(int i=0;i<=n;i++){
			if(i<n)gg[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(gg[i]+=ff[j][s]*j%mod*gg[i-j]%mod*ni[i-j+1])%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=gg[i-1]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,mod-1);
	b[0]=1;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();m=read();s=read();t=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();u=id(u),v=id(v);
		e[u][v]++;
	}
	dp[0][n-2]=1;
	for(int s=0;s<(1<<n-2);s++){
		for(int i=0;i<n-1;i++)if(dp[s][i]){
			for(int j=0;j<n-2;j++)if(!(s&(1<<j)))(dp[s|(1<<j)][j]+=dp[s][i]*e[j][i])%=mod;
		}
	}
	for(int s=0;s<(1<<n-2);s++){
		for(int i=0;i<n-2;i++)(f[s]+=e[n-1][i]*dp[s][i])%=mod;
	}
	ni[0]=ni[1]=1;for(int i=2;i<=n-2;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	xorexp(f,g,n-2);
	for(int i=0;i<n-2;i++){
		for(int s=0;s<(1<<n-2);s++)if(s&(1<<i))(g[s]+=g[s^(1<<i)])%=mod;
	}
	// for(int s=0;s<(1<<n-2);s++)cout<<g[s]<<" ";cout<<"\n";
	int pw=1;for(int i=1;i<=e[n-1][n-2];i++)pw=pw*2%mod;
	q=read();
	while(q--){
		int u=read();u=id(u);
		if(u==n-2)printf("%lld\n",g[(1<<n-2)-1]*(pw-1)%mod);
		else{
			int ans=0;for(int s=0;s<(1<<n-2);s++)if(s&(1<<u))(ans+=e[n-1][u]*dp[s][u]%mod*g[((1<<n-2)-1)^s])%=mod;
			printf("%lld\n",ans*pw%mod);
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}