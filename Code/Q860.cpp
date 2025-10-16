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
const int maxn=1510;
const int inf=1e9;
bool mbe;

int n,m,k,a[maxn];
vector<int> id[maxn];
int e[maxn][maxn];
bool vis[maxn];
int ans[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int k=read();id[i].resize(k);
		for(int j=0;j<k;j++)id[i][j]=read();
	}
	for(int i=1;i<=m;i++)vis[i]=0;
	k=read();
	for(int i=1;i<=k;i++)a[i]=read(),vis[a[i]]=1;
	vector<int> p;
	for(int i=1;i<=n;i++)p.pb(i);
	for(int i=1;i<=m;i++)if(!vis[i])p.pb(i+n);
	for(int i=1;i<=n+m;i++){
		for(int j=1;j<=n+m;j++)e[i][j]=inf;
		e[i][i]=0;
	}
	int mx=0;
	for(int i=1;i<=m;i++)if(!vis[i]){
		for(int v:id[i])e[i+n][v]=1,e[v][i+n]=0;
	}
	for(int j:p){
		for(int i:p){
			for(int k:p){
				e[i][k]=min(e[i][k],e[i][j]+e[j][k]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(e[i][j]!=inf)mx=max(mx,e[i][j]);
	}
	ans[k]=mx-1;
	for(int ii=k;ii;ii--){
		for(int v:id[a[ii]])e[a[ii]+n][v]=1,e[v][a[ii]+n]=0;
		p.pb(a[ii]+n);
		for(int j:p){
			for(int i:p)e[i][a[ii]+n]=min(e[i][a[ii]+n],e[i][j]+e[j][a[ii]+n]);
			for(int i:p)e[a[ii]+n][i]=min(e[a[ii]+n][i],e[a[ii]+n][j]+e[j][i]);
		}
		for(int i:p){
			for(int k:p){
				e[i][k]=min(e[i][k],e[i][a[ii]+n]+e[a[ii]+n][k]);
			}
		}
		int mx=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++)if(e[i][j]!=inf)mx=max(mx,e[i][j]);
		}
		// cout<<a[ii]<<"\n";
		// for(int i=1;i<=n;i++){
			// for(int j=1;j<=n;j++)if(i!=j&&e[i][j]!=inf)cout<<i<<" "<<j<<" "<<e[i][j]<<"\n";
		// }
		ans[ii-1]=mx-1;
	}
	for(int i=0;i<=k;i++)printf("%d\n",max(0,ans[i]));
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