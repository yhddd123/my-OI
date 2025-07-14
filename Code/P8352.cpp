#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,k;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],f[maxn][maxn*5][6],g[maxn*5][6];
void dfs(int u,int fa){
	siz[u]=1;
	for(int i=1;i<=k;i++)f[u][0][i]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
		memset(g,0,sizeof(g));
		for(int i=0;i<=k*siz[u];i++){
			for(int j=0;j<=k;j++){
				if(!f[u][i][j])continue;
				for(int p=0;p<=k*siz[v];p++){
					for(int q=0;q<=k;q++){
						if(!f[v][p][q])continue;
						g[i+p+q][max(0ll,j-q)]+=f[u][i][j]*f[v][p][q]%mod;
						g[i+p+q][max(0ll,j-q)]%=mod;
					}
				}
			}
		}
		siz[u]+=siz[v];
		for(int i=0;i<=k*siz[u];i++){
			for(int j=0;j<=k;j++)f[u][i][j]=g[i][j];
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=k*n;i++){
		int ans=0;
		for(int j=0;j<=min(i,k);j++)ans+=f[1][i-j][j],ans%=mod;
		printf("%lld\n",ans);
	}
}
