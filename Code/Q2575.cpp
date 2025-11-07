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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m,gg;
bool vis[maxn];
vector<int> e[maxn],g[maxn];
int a[maxn];
void dfs(int u){
	vis[u]=1;
	for(int v:e[u]){
		if(!a[v])a[v]=a[u]+1,dfs(v);
		else gg=__gcd(gg,abs(a[u]+1-a[v]));
	}
	for(int v:g[u]){
		if(!a[v])a[v]=a[u]-1,dfs(v);
		else gg=__gcd(gg,abs(a[u]-1-a[v]));
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v);g[v].pb(u);
	}
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
	vector<int> ans;
	for(int i=1;i<=n;i++)if(gg%i==0)ans.pb(i);
	printf("%d\n",ans.size());
	for(int u:ans)printf("%d " ,u);
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