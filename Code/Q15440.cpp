#include<bits/stdc++.h>
#define int long long
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
const int maxn=510;
const int inf=1e9;
bool mbe;

int n,m,a[maxn][maxn],rnk[maxn];
bool fl[maxn][maxn],vis[maxn][maxn];
int mn[maxn][maxn],mx[maxn][maxn];
int f[maxn][maxn],g[maxn][maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
	}
	for(int i=1;i<=n;i++)rnk[a[1][i]]=i;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)a[i][j]=rnk[a[i][j]];
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)fl[i][j]=1;
	}
	for(int i=2;i<=m;i++){
		for(int j=1;j<=n;j++){
			mn[j][j]=mx[j][j]=a[i][j];
			for(int k=j+1;k<=n;k++){
				mn[j][k]=min(mn[j][k-1],a[i][k]);
				mx[j][k]=max(mx[j][k-1],a[i][k]);
				if(mn[j][k]==a[i][j]&&mx[j][k]==a[i][j]+k-j)vis[a[i][j]][a[i][j]+k-j]=1;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				if(!vis[i][j])fl[i][j]=0;
				else vis[i][j]=0;
			}
		}
	}
	for(int i=1;i<=n;i++)f[i][i]=1;
	for(int i=n;i;i--){
		for(int j=i+1;j<=n;j++)if(fl[i][j])f[i][j]=g[i+1][j];
		for(int j=i;j<=n;j++){
			g[i][j]=f[i][j];
			for(int k=i;k<j;k++)(g[i][j]+=f[i][k]*g[k+1][j])%=mod;
		}
	}
	printf("%lld\n",f[1][n]);
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