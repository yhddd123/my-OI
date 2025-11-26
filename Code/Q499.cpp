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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n;
mt19937 rnd(time(0));
int bas,pw[maxn];
struct graph{
	vector<int> e[maxn];
	void clr(){
		for(int i=1;i<=n;i++)e[i].clear();
	}
	int siz[maxn],dep[maxn];
	int dfs(int u,int fa){
		dep[u]=dep[fa]+1;
		int hsh=dep[u]*pw[1]%mod;
		siz[u]=1;
		vector<pii> son;
		for(int v:e[u])if(v!=fa){
			int hv=dfs(v,u);
			son.pb({hv,siz[v]});
		}
		sort(son.begin(),son.end());
		for(auto[h,s]:son)hsh=(hsh+h*pw[s])%mod,siz[u]+=s;
		return hsh;
	}
	int hsh(){return dfs(1,0);}
}g1,g2;
void work(){
	n=read();
	bas=rnd();pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	g1.clr(),g2.clr();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		g1.e[u].pb(v),g1.e[v].pb(u);
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		g2.e[u].pb(v),g2.e[v].pb(u);
	}
	puts(g1.hsh()==g2.hsh()?"Isomorphism":"No");
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