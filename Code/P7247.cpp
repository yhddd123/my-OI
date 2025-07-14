// Problem: P7247 教材运送
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7247
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int x,y,z;
int dis[maxn],sum[maxn],siz[maxn],sa[maxn],mul[maxn];
int inc(int u,int v){
	((u+=v)>=mod)&&(u-=mod);
	return u;
}
void dfs(int u,int fa){
	if(u!=1)(x+=dis[u]*a[u])%=mod,(y+=dis[u]*a[1])%=mod;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dis[v]=inc(dis[u],e[i].w);dfs(v,u);
		siz[u]+=siz[v],sum[u]=inc(sum[u],sum[v]),sa[u]=inc(sa[u],sa[v]),mul[u]=inc(mul[u],mul[v]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		(z+=(siz[u]-siz[v])*(mul[v]-dis[u]*sa[v]%mod+mod))%=mod;
		(z+=(sa[u]-sa[v]+mod)*(sum[v]-siz[v]*dis[u]%mod+mod))%=mod;
	}
	if(u!=1){
		(z+=a[u]*(sum[u]-siz[u]*dis[u]%mod+mod))%=mod;
		(z+=mul[u]-dis[u]*sa[u]%mod+mod)%=mod;
	}
	siz[u]++,sum[u]=inc(sum[u],dis[u]),sa[u]=inc(sa[u],a[u]),(mul[u]+=a[u]*dis[u])%=mod;
}
int dp[maxn][2];
int inv[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	inv[0]=inv[1]=1;for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	x=x*inv[n-1]%mod,y=y*inv[n-1]%mod,z=z*inv[n-1]%mod*inv[n-2]%mod;
	for(int i=1;i<n;i++){
		dp[i][0]=(dp[i-1][1]+((n-1)*(i+1)%mod*x+(n-i-1)*y+(n-i-1)*(n-2)%mod*z)%mod*inv[i]%mod*inv[n])%mod;
		dp[i][1]=(dp[i-1][1]+((n-1)*x+(n-1)*y+(n-1)*(n-2)%mod*z)%mod*inv[i]%mod*inv[n])%mod;
	}
	printf("%lld\n",dp[n-1][0]);
}

int T;
signed main(){	
	T=1;
	while(T--)work();
}
