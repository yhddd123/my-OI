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
const int maxn=310;
const int inf=1e12;
bool mbe;

int n,m;
int f[maxn][maxn*maxn];
vector<tuple<int,int,int>> e[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),a=read(),b=read();
		e[u].pb({v,a,b});
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=200*n;j++)f[i][j]=inf;
	}
	f[1][0]=0;
	for(int s=0;s<=200*n;s++){
		for(int u=1;u<=n;u++)if(f[u][s]<inf){
			for(auto[v,a,b]:e[u])if(s+a<=200*n){
				f[v][s+a]=min(f[v][s+a],f[u][s]+b);
			}
		}
	}
	int va=inf,vb=inf;
	for(int s=1;s<=200*n;s++)if(va*vb>s*f[n][s])va=s,vb=f[n][s];
	printf("%lld %lld\n",va,vb);
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