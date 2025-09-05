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
const int B=1000;
bool mbe;

int n,m,q;
int a[maxn];
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int get(int u,int v){return (u-1)*m+v;}
vector<int> e[maxn];
map<int,vector<int>> g[maxn/B+5];
bitset<maxn/B+5> ee[maxn];
int id[maxn],idx;
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	if(siz[u]<siz[v])swap(u,v);
	f[v]=u;
	if(siz[u]>B){
		for(auto p:e[v]){
			p=fd(p);
			if(p!=u&&p!=v){
				g[id[u]][a[p]].pb(p),e[u].pb(p);
				if(id[p])ee[u][id[p]]=1;ee[p][id[u]]=1;
			}
		}
		siz[u]+=siz[v];
	}
	else{
		for(auto p:e[v]){
			p=fd(p);
			if(p!=u&&p!=v){
				e[u].pb(p);
				if(id[p])ee[u][id[p]]=1;
			}
		}
		siz[u]+=siz[v];
		if(siz[u]>B){
			id[u]=++idx;
			for(int p:e[u]){
				p=fd(p);
				g[id[u]][a[p]].pb(p);
				ee[p][id[u]]=1;
			}
		}
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[get(i,j)]=read();
	}
	for(int i=1;i<=n*m;i++)f[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i>1)e[get(i,j)].pb(get(i-1,j));
			if(i<n)e[get(i,j)].pb(get(i+1,j));
			if(j>1)e[get(i,j)].pb(get(i,j-1));
			if(j<m)e[get(i,j)].pb(get(i,j+1));
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i<n&&a[get(i,j)]==a[get(i+1,j)])merge(get(i,j),get(i+1,j));
			if(j<m&&a[get(i,j)]==a[get(i,j+1)])merge(get(i,j),get(i,j+1));
		}
	}
	q=read();
	while(q--){
		int u=read(),v=read();u=fd(get(u,v)),v=read();
		if(a[u]==v)continue;a[u]=v;
		for(int i=1;i<=idx;i++)if(ee[u][i])g[i][a[u]].pb(u);
		if(siz[u]<=B){
			vector<int> tmp=e[u];
			for(int v:tmp)if(a[u]==a[fd(v)])merge(u,fd(v));
		}
		else{
			vector<int> tmp=g[id[u]][a[u]];g[id[u]][a[u]].clear();
			for(int v:tmp)if(a[u]==a[fd(v)])merge(u,v);
		}
		// cout<<u<<" "<<fd(u)<<" "<<a[fd(u)]<<"\n";
		// for(int v:e[fd(u)])cout<<v<<" ";cout<<"\n";
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)printf("%d ",a[fd(get(i,j))]);puts("");
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