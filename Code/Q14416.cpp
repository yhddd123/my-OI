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
const int maxn=510;
const int inf=1e18;
bool mbe;

int n,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int f[maxn][maxn][maxn],siz[maxn],g[maxn][maxn];
void dfs(int u,int fa){
	siz[u]=1;
	for(int k=1;k<=n;k++)f[u][1][k]=a[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		for(int j1=1;j1<=siz[u];j1++){
			for(int k=j1;k<=n;k++){
				for(int j2=1;j2<=siz[v];j2++){
					g[j1+j2][k]=min(g[j1+j2][k],f[u][j1][k]+f[v][j2][j2]+a[u]*j2);
					if(j2+k<=n)g[j1][k]=min(g[j1][k],f[u][j1][k]+f[v][j2][j2+k]);
				}
			}
		}
		siz[u]+=siz[v];
		for(int j=1;j<=siz[u];j++){
			for(int k=j;k<=n;k++)f[u][j][k]=g[j][k],g[j][k]=inf;
		}
	}
	for(int j=1;j<=siz[u];j++){
		for(int k=j;k<=n;k++)f[u][j][k]+=(k-j)*a[u];
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++)f[i][j][k]=inf;
		}
	}
	for(int j=1;j<=n;j++){
		for(int k=1;k<=n;k++)g[j][k]=inf;
	}
	dfs(1,0);
	int ans=inf;for(int i=1;i<=n;i++)ans=min(ans,f[1][i][i]);
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