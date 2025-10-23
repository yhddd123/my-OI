// Problem: P5405 [CTS2019] 氪金手游
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5405
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-10-22 14:53:56
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
const int maxn=1010;
const int maxm=3000010;
const int inf=1e9;
bool mbe;

int n,a[maxn][3];
int ni[maxm];
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int f[maxn][3*maxn],g[3*maxn],siz[maxn];
void dfs(int u,int fa){
	siz[u]=1;f[u][1]=a[u][0],f[u][2]=a[u][1]*2%mod,f[u][3]=a[u][2]*3%mod;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		for(int j=1;j<=3*siz[u];j++){
			for(int k=1;k<=3*siz[v];k++){
				int val=f[u][j]*f[v][k]%mod;
				if(e[i].w)(g[j+k]+=val)%=mod;
				else (g[j+k]+=mod-val)%=mod,(g[j]+=val)%=mod;
			}
		}
		siz[u]+=siz[v];
		for(int j=1;j<=3*siz[u];j++)f[u][j]=g[j],g[j]=0;
	}
	for(int i=1;i<=3*siz[u];i++)f[u][i]=f[u][i]*ni[i]%mod;
}
void work(){
	n=read();
	ni[0]=ni[1]=1;for(int i=2;i<=3000000;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	for(int i=1;i<=n;i++){
		a[i][0]=read(),a[i][1]=read(),a[i][2]=read();
		int s=a[i][0]+a[i][1]+a[i][2];
		a[i][0]=a[i][0]*ni[s]%mod,a[i][1]=a[i][1]*ni[s]%mod,a[i][2]=a[i][2]*ni[s]%mod;
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v,1),add(v,u,0);
	}
	dfs(1,0);
	int ans=0;for(int i=1;i<=3*n;i++)(ans+=f[1][i])%=mod;
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