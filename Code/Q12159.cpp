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
const int inf=1e9;
bool mbe;

int n,m,a[maxn][maxn],b[maxn][maxn];
int ans[maxn][maxn];
int head[maxn<<1],tot;
vector<pii> e[maxn<<1];
int dis[maxn<<1],tim[maxn<<1];
bool vis[maxn<<1];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i][j]=read();
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++)b[i][j]=read();
	}
	for(int i=2;i<=n;i++){
		for(int j=2;j<=m;j++)ans[i][j]=b[i-1][j-1]-ans[i-1][j]-ans[i][j-1]-ans[i-1][j-1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)&1){
				e[j+n].pb({i,a[i][j]-ans[i][j]});
				e[i].pb({j+n,ans[i][j]});
			}
			else{
				e[i].pb({j+n,a[i][j]-ans[i][j]});
				e[j+n].pb({i,ans[i][j]});
			}
		}
	}
	queue<int> q;
	for(int i=1;i<=n+m;i++)q.push(i),vis[i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		++tim[u];if(tim[u]>n+m){puts("NIE");return ;}
		for(auto[v,w]:e[u]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
	puts("TAK");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)&1)printf("%lld ",ans[i][j]+dis[i]-dis[j+n]);
			else printf("%lld ",ans[i][j]-dis[i]+dis[j+n]);
		}
		puts("");
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