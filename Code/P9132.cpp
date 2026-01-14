// Problem: P9132 [USACO23FEB] Watching Cowflix P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9132
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-01-14 20:32:41
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,ans[maxn];
char s[maxn];
vector<int> e[maxn];
int dfn[maxn],rnk[maxn],idx;
void dfs(int u,int fa){
	rnk[dfn[u]=++idx]=u;
	sort(e[u].begin(),e[u].end());
	e[u].erase(lower_bound(e[u].begin(),e[u].end(),fa));
	for(int v:e[u])if(v!=fa)dfs(v,u);
}
int f[maxn][2];
int calc(int k){
	for(int i=n;i;i--){
		int u=rnk[i];
		f[u][0]=0,f[u][1]=k+1;
		for(int v:e[u]){
			f[u][1]=f[u][1]+min(f[v][0],f[v][1]-k);
			f[u][0]+=min(f[v][0],f[v][1]);
		}
		if(s[u]=='1')f[u][0]=inf;
		// cout<<k<<" "<<u<<" "<<f[u][0]<<" "<<f[u][1]<<"\n";
	}
	return min(f[1][0],f[1][1]);
}
void work(){
	n=read();
	scanf("%s",s+1);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	e[1].pb(0);
	dfs(1,0);
	int B=min(400,n);
	for(int i=1;i<=B;i++)ans[i]=calc(i);
	int p=B+1;
	while(p<=n){
		ans[p]=calc(p);
		int d=ans[p]-ans[p-1];
		// cout<<p<<" "<<ans[p]<<endl;
		int l=p+1,r=n,res=p;
		while(l<=r){
			int mid=l+r>>1;
			if(calc(mid)-calc(mid-1)==d)l=mid+1,res=mid;
			else r=mid-1;
		}
		for(int i=p+1;i<=res;i++)ans[i]=ans[i-1]+d;
		p=res+1;
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
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