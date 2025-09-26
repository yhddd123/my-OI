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
const int maxn=210;
const int inf=1e18;
bool mbe;

int n,m,q;
int c[maxn],w[maxn];
vector<int> e[maxn];
int f[maxn][maxn*maxn];
int g[maxn][maxn][maxn][2];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)c[i]=read(),w[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v);
	}
	for(int u=1;u<=n;u++){
		for(int i=c[u];i<maxn*maxn;i++)f[u][i]=max(f[u][i],f[u][i-c[u]]+w[u]);
		for(int v:e[u]){
			for(int i=0;i<maxn*maxn;i++)f[v][i]=max(f[v][i],f[u][i]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int u=1;u<=n;u++){
			for(int j=0;j<c[i];j++)g[i][u][j][1]=-inf;
		}
		if(i==1){
			for(int j=0;j<c[i];j++)g[i][1][j][1]=0;
		}
		for(int u=1;u<=n;u++)if(w[u]*c[i]<=w[i]*c[u]){
			int gg=__gcd(c[i],c[u]);
			for(int s=0;s<gg;s++){
				for(int j=s,t=0,jj;t<2;j=jj,t+=(j==s)){
					jj=(j+c[u])%c[i];
					g[i][u][jj][0]=max(g[i][u][jj][0],g[i][u][j][0]+w[u]-(j+c[u])/c[i]*w[i]);
					g[i][u][jj][1]=max(g[i][u][jj][1],g[i][u][j][1]+w[u]-(j+c[u])/c[i]*w[i]);
				}
			}
			for(int v:e[u])if(w[v]*c[i]<=w[i]*c[v]){
				for(int j=0;j<c[i];j++){
					g[i][v][j][i==v]=max(g[i][v][j][i==v],g[i][u][j][0]);
					g[i][v][j][1]=max(g[i][v][j][1],g[i][u][j][1]);
				}
			}
		}
	}
	q=read();
	while(q--){
		int u=read(),v=read();
		if(v<maxn*maxn)printf("%lld\n",f[u][v]);
		else{
			int ans=0;
			for(int i=1;i<=n;i++)if(w[u]*c[i]<=w[i]*c[u]){
				ans=max(ans,g[i][u][v%c[i]][1]+v/c[i]*w[i]);
			}
			printf("%lld\n",ans);
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