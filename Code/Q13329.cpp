#include<bits/stdc++.h>
// #define int long long
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
const int maxn=18;
const int inf=1e9;
bool mbe;

inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void fmt(int *a,int n){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))inc(a[s],a[s^(1<<i)]);
	}
}
void ifmt(int *a,int n){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))inc(a[s],mod-a[s^(1<<i)]);
	}
}
int ff[maxn+1][1<<maxn],hh[1<<maxn],ni[maxn+1];
void xorexp(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			hh[i]=1ll*ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)inc(hh[i],1ll*ff[j][s]*j%mod*hh[i-j]%mod*ni[i-j+1]%mod);
		}
		for(int i=1;i<=n;i++)ff[i][s]=1ll*hh[i-1]*ni[i]%mod;
	}
	for(int i=1;i<=n;i++)ifmt(ff[i],n);
	b[0]=1;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
int n,m;
bool e[maxn][maxn];
int dp[1<<maxn][maxn],f[1<<maxn],g[1<<maxn];
void work(){
	n=read();m=read();
	if(n==1){puts("1");return ;}
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u][v]=e[v][u]=1;
	}
	for(int i=0;i<n;i++){
		dp[1<<i][i]=1;
		for(int s=0;s<(1<<n);s++)if(__lg(s)==i){
			for(int j=0;j<=i;j++)if((s&(1<<j))&&dp[s][j]){
				if(e[j][i])inc(f[s],dp[s][j]);
				for(int k=0;k<=i;k++)if(!(s&(1<<k))&&e[j][k]){
					inc(dp[s|(1<<k)][k],dp[s][j]);
				}
			}
		}
	}
	for(int s=1;s<(1<<n);s++)if(__builtin_popcount(s)>2)f[s]=f[s]*(mod+1)/2%mod;
	// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
	for(int i=0;i<n;i++){
		for(int s1=0;s1<(1<<i);s1++){
			for(int s2=0;s2<(1<<n-i-1);s2++)g[s1|(s2<<i)]=f[s1|(1<<i)|(s2<<i+1)];
		}
		xorexp(g,g,n-1);g[0]=0;
		for(int s1=0;s1<(1<<i);s1++){
			for(int s2=0;s2<(1<<n-i-1);s2++)f[s1|(1<<i)|(s2<<i+1)]=g[s1|(s2<<i)];
		}
		// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	}
	printf("%d\n",f[(1<<n)-1]);
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