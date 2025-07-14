#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=10010;
const int maxm=1010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define vi vector<int>
#define pb push_back

int n,a[maxn];
vi e[maxn];
bool cmp(int u,int v){return a[u]<a[v];}
bitset<maxm> f[maxn],g[maxn];
void dfs(int u,int fa){
	f[u].set(a[u]);g[u].set(a[u]);
	for(int v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
	}
	for(int v:e[u]){
		if(a[v]>a[u]&&((g[u]<<1)&f[v]).any())g[u]|=g[v];
	}
	reverse(e[u].begin(),e[u].end());
	for(int v:e[u]){
		if(a[v]<a[u]&&((f[u]>>1)&g[v]).any())f[u]|=f[v];
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v);e[v].pb(u);
	}
	for(int i=1;i<=n;i++)sort(e[i].begin(),e[i].end(),cmp);
	dfs(1,0);
	printf("%lld\n",f[1].count()*g[1].count());
}
