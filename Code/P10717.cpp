// Problem: P10717 【MX-X1-T5】「KDOI-05」简单的树上问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10717
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-27 15:11:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=110;
const int maxk=8;
const int inf=1e9;
bool mbe;

int n,k,ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int p[maxn][maxk],a[maxn][1<<maxk];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int f[maxn][1<<maxk*2],dp[1<<maxk*2];
tuple<int,int,int> st[1679617];int tp;
void dfs(int d,int x,int y,int z){
	if(d==k){
		st[++tp]={x,y,z};
		return ;
	}
	dfs(d+1,x,y,z);
	dfs(d+1,x,y|(1<<2*d),z|(1<<2*d));
	dfs(d+1,x|(1<<2*d),y,z|(1<<2*d));
	dfs(d+1,x,y|(2<<2*d),z|(2<<2*d));
	dfs(d+1,x|(2<<2*d),y,z|(2<<2*d));
	dfs(d+1,x|(3<<2*d),y|(3<<2*d),z|(3<<2*d));
}
void fmt(int *a,int w=1){
	for(int j=0;j<k;j++){
		for(int s=0;s<(1<<2*k);s++){
			int c=(s>>2*j)&3;
			if(c==0||c==2)inc(a[s|(3<<2*j)],1ll*a[s]*w%mod);
		}
	}
}
void dfs(int u,int fa){
	f[u][0]=1;
	fmt(f[u],1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		fmt(f[v],1);
		for(int j=1;j<=tp;j++){
			auto[x,y,z]=st[j];
			inc(dp[z],1ll*f[u][x]*f[v][y]%mod);
		}
		for(int s=0;s<(1<<2*k);s++)f[u][s]=dp[s],dp[s]=0;
	}
	fmt(f[u],mod-1);
	// cout<<u<<"\n";
	// for(int s=0;s<(1<<2*k);s++)cout<<f[u][s]<<" ";cout<<"\n";
	for(int j=0;j<k;j++){
		for(int s=0;s<(1<<2*k);s++){
			int c=(s>>2*j)&3;
			if(c==0||c==2||c==3)inc(dp[s|(3<<2*j)],1ll*f[u][s]*p[u][j]%mod);
			inc(dp[s],1ll*f[u][s]*(1+mod-p[u][j])%mod);
		}
		for(int s=0;s<(1<<2*k);s++)f[u][s]=dp[s],dp[s]=0;
	}
	for(int s=0;s<(1<<2*k);s++){
		int t=0;for(int j=0;j<k;j++){
			int c=(s>>2*j)&3;
			if(c==2||c==3)t|=1<<j;
		}
		f[u][s]=1ll*f[u][s]*a[u][t]%mod;
	}
	// cout<<u<<"\n";
	// for(int s=0;s<(1<<2*k);s++)cout<<f[u][s]<<" ";cout<<"\n";
	for(int j=0;j<k;j++){
		for(int s=0;s<(1<<2*k);s++){
			int c=(s>>2*j)&3;
			if(c==1||c==2)inc(f[u][s],f[u][s|(3<<2*j)]);
			if(c==3)f[u][s]=0;
		}
	}
	// cout<<u<<"\n";
	// for(int s=0;s<(1<<2*k);s++)cout<<f[u][s]<<" ";cout<<"\n";
}
void work(){
	n=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int j=0;j<k;j++){
		for(int i=1;i<=n;i++)p[i][j]=read();
	}
	for(int i=1;i<=n;i++){
		for(int s=0;s<(1<<k);s++)a[i][s]=read();
	}
	dfs(0,0,0,0);
	dfs(1,0);
	for(int s=0;s<(1<<2*k);s++){
		bool fl=1;
		for(int j=0;j<k;j++){
			int c=(s>>2*j)&3;
			if(c==2)fl=0;
		}
		if(fl)inc(ans,f[1][s]);
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("expectation.in","r",stdin);
	// freopen("expectation.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}