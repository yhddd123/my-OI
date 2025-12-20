#include<bits/stdc++.h>
// #define int long long
#define mod 1000000007ll
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
const int maxn=710;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn];
int C[maxn][maxn],fac[maxn];
vector<int> e[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
int coef[maxn][maxn<<1];
vector<vector<int>> f[maxn];
int g[maxn][maxn],siz[maxn];
int sum[maxn][maxn],tmp[maxn];
int val[maxn],ans[maxn][maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
// void dfs(int u,int fa){
	// int sz=1;for(int v:e[u])if(v!=fa){
		// dfs(v,u);sz+=siz[v];
	// }
	// f[u].resize(sz+1,vector<int>(sz+1));
	// siz[u]=0;
	// f[u][0][0]=1;
	// for(int v:e[u])if(v!=fa){
		// for(int j=0;j<=siz[u];j++){
			// for(int jj=0;jj<=siz[v];jj++){
				// for(int k=0;k<=siz[u];k++){
					// for(int kk=0;kk<=siz[v];kk++){
						// inc(g[j+jj][k+kk],1ll*f[u][j][k]*f[v][jj][kk]%mod*C[j+jj][j]%mod*C[siz[u]-j+siz[v]-jj][siz[u]-j]%mod);
					// }
				// }
			// }
		// }
		// siz[u]+=siz[v];
		// for(int j=0;j<=siz[u];j++){
			// for(int k=0;k<=siz[u];k++)f[u][j][k]=g[j][k],g[j][k]=0;
		// }
	// }
	// for(int j=0;j<=siz[u];j++){
		// for(int k=0;k<=siz[u];k++){
			// inc(val[j],1ll*f[u][j][k]*a[k+1]%mod);
		// }
	// }
	// for(int j=0;j<=siz[u];j++){
		// for(int jj=0;jj<=n-siz[u]-1;jj++)inc(ans[u][j+jj+1],1ll*val[j]*C[j+jj][j]%mod*C[n-j-jj-1][siz[u]-j]%mod*fac[n-siz[u]-1]%mod);
		// val[j]=0;
	// }
	// for(int j=0;j<=siz[u];j++){
		// for(int k=0;k<=siz[u];k++){
			// inc(g[j+1][k+1],1ll*f[u][j][k]*(j+1)%mod);
			// inc(g[j][0],1ll*f[u][j][k]*(siz[u]-j+1)%mod);
		// }
	// }
	// siz[u]++;
	// for(int j=0;j<=siz[u];j++){
		// for(int k=0;k<=siz[u];k++)f[u][j][k]=g[j][k],g[j][k]=0;
	// }
// }
void dfs(int u,int fa){
	int sz=1;for(int v:e[u])if(v!=fa){
		dfs(v,u);sz+=siz[v];
	}
	f[u].resize(sz+1,vector<int>(n+1));
	siz[u]=0;
	for(int x=0;x<=n;x++)f[u][0][x]=1;
	sum[u][0]=1;
	for(int v:e[u])if(v!=fa){
		for(int j=0;j<=siz[u];j++){
			for(int jj=0;jj<=siz[v];jj++){
				int coef=1ll*C[j+jj][j]*C[siz[u]-j+siz[v]-jj][siz[u]-j]%mod;
				inc(tmp[j+jj],1ll*sum[u][j]*sum[v][jj]%mod*coef%mod);
				for(int x=0;x<=n;x++){
					inc(g[j+jj][x],1ll*f[u][j][x]*f[v][jj][x]%mod*coef%mod);
				}
			}
		}
		siz[u]+=siz[v];
		for(int j=0;j<=siz[u];j++){
			sum[u][j]=tmp[j],tmp[j]=0;
			for(int x=0;x<=n;x++)f[u][j][x]=g[j][x],g[j][x]=0;
		}
	}
	for(int j=0;j<=siz[u];j++){
		for(int x=0;x<=n;x++){
			inc(val[j],1ll*f[u][j][x]*b[x]%mod);
		}
	}
	for(int j=0;j<=siz[u];j++){
		for(int jj=0;jj<=n-siz[u]-1;jj++)inc(ans[u][j+jj+1],1ll*val[j]*C[j+jj][j]%mod*C[n-j-jj-1][siz[u]-j]%mod*fac[n-siz[u]-1]%mod);
		val[j]=0;
	}
	for(int j=0;j<=siz[u];j++){
		int coef=1ll*sum[u][j]*(siz[u]-j+1)%mod;
		for(int x=0;x<=n;x++)inc(g[j][x],coef);
		for(int x=0;x<=n;x++)inc(g[j+1][x],1ll*f[u][j][x]*(j+1)*x%mod);
	}
	for(int j=0;j<=siz[u];j++){
		inc(tmp[j+1],1ll*sum[u][j]*(j+1)%mod);
		inc(tmp[j],1ll*sum[u][j]*(siz[u]-j+1)%mod);
	}
	siz[u]++;
	for(int j=0;j<=siz[u];j++){
		sum[u][j]=tmp[j],tmp[j]=0;
		for(int x=0;x<=n;x++)f[u][j][x]=g[j][x],g[j][x]=0;
	}
	// cout<<u<<" "<<siz[u]<<"\n";
	// for(int j=0;j<=siz[u];j++){
		// cout<<sum[u][j]<<"\n";
		// for(int x=0;x<=n;x++)cout<<f[u][j][x]<<" ";cout<<"\n";
	// }
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)inc(C[i][j]=C[i-1][j],C[i-1][j-1]);
	}
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=0;i<=n;i++){
		for(int j=0,pw=1;j<=n;j++,pw=1ll*pw*i%mod)coef[i][j]=pw;
		coef[i][i+n+1]=1;
	}
	for(int i=0;i<=n;i++){
		if(!coef[i][i]){
			for(int j=i+1;j<=n;j++)if(coef[j][i]){
				swap(coef[i],coef[j]);
				break;
			}
		}
		int inv=ksm(coef[i][i]);
		for(int j=0;j<=n;j++)if(i!=j){
			int d=1ll*coef[j][i]*inv%mod;
			for(int k=i;k<=(n<<1)+1;k++)inc(coef[j][k],mod-1ll*coef[i][k]*d%mod);
		}
		for(int j=i;j<=(n<<1)+1;j++)coef[i][j]=1ll*coef[i][j]*inv%mod;
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++)inc(b[j],1ll*a[i+1]*coef[i][j+n+1]%mod);
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)printf("%d ",ans[i][j]);puts("");
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