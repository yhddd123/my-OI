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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,a[maxn][maxn];
int id[maxn],rnk[maxn];
int fr[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int scc[maxn],scct;
int dp[maxn];
vector<int> pos[maxn];
int val[maxn][maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
	}
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return !a[v][u];});
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		int u=id[i];fr[i]=i;
		for(int j=1;j<=i;j++)if(a[u][id[j]]){fr[i]=j;break;}
		f[fd(i)]=fd(fr[i]);
	}
	scct=0;for(int i=1;i<=n;i++)if(f[i]==i)scc[++scct]=i;
	for(int i=1;i<=n;i++)pos[fd(i)].pb(i);
	for(int i=1;i<=scct;i++){
		for(int j=i+1;j<=scct;j++)
	}
	priority_queue<pii> q;
	for(int i=1;i<=scct;i++)dp[i]=inf;dp[scct]=0;q.push({0,scct});
	for(int i=scct-1;i;i--){
		dp[i]=inf;
		for(int j=i+1;j<=scct;j++)
	}
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