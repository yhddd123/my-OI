// Problem: P10778 BZOJ3569 DZY Loves Chinese II
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10778
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-14 08:01:32
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
const int maxn=500010;
const int inf=(1ll<<63)-1;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q;
pii a[maxn];int val[maxn];
bool vis[maxn];
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],ff[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);ff[u]^=ff[v];
	}
}
struct bas{
	int p[63],cnt;
	void insert(int x){
		for(int i=62;~i;i--)if(x&(1ll<<i)){
			if(!p[i]){p[i]=x,++cnt;return ;}
			x^=p[i];
		}
	}
	void clear(){
		cnt=0;for(int i=62;~i;i--)p[i]=0;
	}
}b;
mt19937 rnd(time(0));
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		a[i]={read(),read()};
		if(fd(a[i].fi)!=fd(a[i].se)){
			f[fd(a[i].fi)]=fd(a[i].se);
			add(a[i].fi,a[i].se),add(a[i].se,a[i].fi);
			vis[i]=1;
		}
	}
	for(int i=1;i<=m;i++)if(!vis[i]){
		val[i]=rnd()&inf;
		ff[a[i].fi]^=val[i],ff[a[i].se]^=val[i];
	}
	dfs(1,0);
	for(int i=1;i<=m;i++)if(vis[i]){
		if(dep[a[i].fi]<dep[a[i].se])swap(a[i].fi,a[i].se);
		val[i]=ff[a[i].fi];
	}
	// for(int i=1;i<=m;i++)cout<<val[i]<<" ";cout<<"\n";
	q=read();int cnt=0;
	while(q--){
		int k=read();b.clear();
		for(int i=1;i<=k;i++){
			int p=read()^cnt;
			b.insert(val[p]);
			// cout<<p<<" "<<val[p^cnt]<<"\n";
		}
		if(b.cnt==k)puts("Connected"),++cnt;
		else puts("Disconnected");
	}
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
