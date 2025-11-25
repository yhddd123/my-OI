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
const int maxn=100010;
const int maxk=31;
const int inf=1e9;
bool mbe;

int n,k,ans;
int f[maxn][maxk],g[maxn][maxk];
int tmp[maxk][maxk][2],nw[maxk][maxk][2],mx[maxk][maxk][2];
vector<int> e[maxn];
void dfs(int u,int fa){
	for(int v:e[u])if(v!=fa)dfs(v,u);
	for(int v:e[u])if(v!=fa){
		for(int i=0;i<=k;i++){
			for(int o=0;o<2;o++){
				mx[i][0][o]=tmp[i][0][o];for(int j=1;j<=i;j++)mx[i][j][o]=max(mx[i][j-1][o],tmp[i][j][0]);
			}
		}
		for(int w=1;w<=k;w++){
			for(int i=0;i<=min(w-1,k-w);i++)nw[w][i][0]=max(nw[w][i][0],mx[i][i][0]+f[v][w]);
			for(int i=w;i<=k-w;i++){
				for(int o=0;o<2;o++){
					nw[i][w][o]=max(nw[i][w][o],mx[i][w][o]+f[v][w]);
					for(int j=w+1;j<=k;j++)nw[i][j][o]=max(nw[i][j][o],tmp[i][j][o]+f[v][w]);
				}
			}
			for(int i=0;i<=min(w,k-w);i++){
				nw[w][i][1]=max(nw[w][i][1],mx[i][i][0]+g[v][w]+(!!w));
			}
			for(int i=1;i<=w;i++){
				for(int j=0;j<=k-w&&j<=i;j++)nw[w][j][1]=max(nw[w][j][1],tmp[i][j][1]+g[v][w]);
			}
			for(int i=w+1;i<=k;i++){
				for(int j=0;j<=k-w&&j<=i;j++)nw[i][j][1]=max(nw[i][j][1],tmp[i][j][1]+g[v][w]);
			}
		}
		for(int i=0;i<=k;i++){
			for(int j=0;j<=i;j++){
				tmp[i][j][0]=max(tmp[i][j][0],nw[i][j][0]),nw[i][j][0]=0;
				tmp[i][j][1]=max(tmp[i][j][1],nw[i][j][1]),nw[i][j][1]=0;
			}
		}
		// if(u==1){
			// cout<<u<<" "<<v<<" e\n";
			// for(int i=0;i<=k;i++){
				// for(int j=0;j<=i;j++)cout<<max(tmp[i][j][0],tmp[i][j][1])<<" ";cout<<"\n";
			// }
		// }
	}
	if(u==1){
		for(int i=0;i<=k;i++){
			for(int j=0;j<=i;j++)ans=max({ans,tmp[i][j][0],tmp[i][j][1]});
		}
	}
	for(int i=0;i<=k;i++){
		for(int j=0;j<=i;j++){
			for(int o=0;o<2;o++){
				if(i<k)f[u][i+1]=max(f[u][i+1],tmp[i][j][o]+1);
				if(j<k)f[u][j+1]=max(f[u][j+1],tmp[i][j][o]);
				if(i<k)g[u][i+1]=max(g[u][i+1],tmp[i][j][o]);
				if(j<k)g[u][j+1]=max(g[u][j+1],tmp[i][j][o]-1);
			}
		}
	}
	// cout<<u<<" d\n";
	// for(int i=0;i<=k;i++)cout<<f[u][i]<<" ";cout<<"\n";
	// for(int i=0;i<=k;i++){
		// for(int j=0;j<=i;j++)cout<<tmp[i][j]<<" ";cout<<"\n";
	// }
	for(int i=0;i<=k;i++){
		for(int j=0;j<=i;j++)tmp[i][j][0]=tmp[i][j][1]=0;
	}
}
void work(){
	n=read();k=read()-1;
	if(!k){puts("0");return ;}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("tree.in","r",stdin);
	// freopen("tree.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}