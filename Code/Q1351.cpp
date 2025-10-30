#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
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
const int maxn=250010;
const int inf=1e9;
bool mbe;

int n,m,ans;
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
vector<pii> edge;
vector<int> e[maxn];
mt19937_64 rnd(time(0));
ull f[maxn];
void dfs(int u,int fa){
	for(int v:e[u])if(v!=fa){
		dfs(v,u);f[u]^=f[v];
	}
}
map<ull,int> mp;
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)ff[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(fd(u)==fd(v))edge.pb({u,v});
		else ff[fd(u)]=fd(v),e[u].pb(v),e[v].pb(u);
	}
	ull x=0;
	for(auto[u,v]:edge){
		ull w=rnd();
		f[u]^=w,f[v]^=w;
		mp[w]++;x^=w;
	}
	dfs(1,0);
	for(int i=2;i<=n;i++)x^=f[i];
	for(int i=2;i<=n;i++)mp[f[i]]++;
	// cout<<x<<" "<<mp[x]<<"\n";
	// for(int i=2;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	if(!x){puts("1");return ;}
	if(mp[x]){printf("%lld\n",mp[x]);return ;}
	for(auto[y,v]:mp)if(v){
		ull z=x^y;
		if(mp.find(z)!=mp.end()&&y<z)ans+=mp[y]*mp[z];
	}
	printf("%lld\n",ans);
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