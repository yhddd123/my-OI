// Problem: P5333 [JSOI2019] 神经网络
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5333
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-10-22 11:42:37
// 
// Powered by CP Editor (https://cpeditor.org)

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
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int k,n,m,ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dp[maxn][maxn][3],f[maxn][3],siz[maxn];
void dfs(int u,int fa){
	siz[u]=1;dp[u][1][0]=1;dp[u][1][1]=dp[u][1][2]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		for(int j=1;j<=siz[u];j++){
			for(int k=1;k<=siz[v];k++){
				int val=(dp[v][k][0]+2*dp[v][k][1]+dp[v][k][2])%mod;
				for(int o=0;o<=2;o++)(f[j+k][o]+=dp[u][j][o]*val)%=mod;
				(f[j+k-1][1]+=dp[u][j][0]*(dp[v][k][0]+dp[v][k][1]))%=mod;
				(f[j+k-1][2]+=2*dp[u][j][1]*(dp[v][k][0]+dp[v][k][1]))%=mod;
			}
		}
		siz[u]+=siz[v];
		for(int j=1;j<=siz[u];j++){
			for(int o=0;o<=2;o++)dp[u][j][o]=f[j][o],f[j][o]=0;
		}
	}
}
int val[maxn],g[maxn],h[maxn];
void work(){
	k=read();init(5000);
	g[0]=1;
	while(k--){
		n=read();
		for(int i=1;i<=n;i++)head[i]=0;tot=0;
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		dfs(1,0);
		for(int i=1;i<=n;i++)val[i]=(dp[1][i][0]+2*dp[1][i][1]+dp[1][i][2])%mod;
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				(val[j]+=(((i-j)&1)?mod-1:1)*fac[i]%mod*inv[j]%mod*C(i-1,j-1)%mod*val[i])%=mod;
			}
			// val[i]=fac[i]*inv[i]%mod*val[i]%mod;
		}
		// for(int i=1;i<=n;i++)cout<<val[i]<<" ";cout<<"\n";
		for(int i=0;i<=m;i++){
			for(int j=1;j<=n;j++)(h[i+j]+=g[i]*val[j])%=mod;
		}
		m+=n;for(int i=0;i<=m;i++)g[i]=h[i],h[i]=0;
	}
	for(int i=1;i<=m;i++)(ans+=g[i]*fac[i-1])%=mod;
	printf("%lld\n",ans);
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