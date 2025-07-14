// Problem: P6134 [JSOI2015] 最小表示
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6134
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-25 15:22:00
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=30010;
const int maxm=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans;
vector<int> e1[maxn],e2[maxn];
bitset<maxn> f[maxn],g[maxn];
int d1[maxn],d2[maxn];
queue<int> q;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e1[u].push_back(v),d1[v]++;
		e2[v].push_back(u),d2[u]++;
	}
	for(int i=1;i<=n;i++)if(!d1[i])q.push(i);
	// for(int i=1;i<=n;i++)f[i][i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e1[u]){
			f[v]|=f[u];f[v].set(u);
			d1[v]--;if(!d1[v])q.push(v);
		}
	}
	for(int i=1;i<=n;i++)if(!d2[i])q.push(i);
	// for(int i=1;i<=n;i++)g[i][i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e2[u]){
			g[v]|=g[u];g[v].set(u);
			// cout<<u<<" "<<v<<"\n";
			d2[v]--;if(!d2[v])q.push(v);
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)cout<<f[i][j];cout<<"\n";
		// for(int j=1;j<=n;j++)cout<<g[i][j];cout<<"\n";
		// cout<<"\n";
	// }
	for(int u=1;u<=n;u++){
		for(int v:e1[u]){
			// cout<<u<<" "<<v<<" "<<g[u]<<" "<<f[v]<<"\n";
			ans+=((g[u]&f[v]).count()>0);
		}
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
