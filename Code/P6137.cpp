#include<bits/stdc++.h>
#define int long long
#define mod 1000000000
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,ans;
pii a[maxn];
vector<int> e[maxn];
int id[maxn],siz[maxn];
void dfs(int u,int fa){
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		siz[u]+=siz[v];
	}
	(ans+=siz[u]*(n-siz[u]))%=inf;
}
void sovle(){
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)e[i].clear(),siz[i]=0;
	map<pii,int> mp;
	for(int i=1,lst=0;i<=n;i++){
		if(a[i].fi!=a[i-1].fi||a[i].se!=a[i-1].se+1)lst=i;
		mp[a[i]]=lst;
		id[i]=lst,siz[lst]++;
	}
	map<pii,bool> edge;
	for(int i=1;i<=n;i++){
		if(mp.find({a[i].fi+1,a[i].se})!=mp.end()){
			int to=id[mp[{a[i].fi+1,a[i].se}]];
			if(!edge[{id[i],to}])edge[{id[i],to}]=1,e[id[i]].pb(to),e[to].pb(id[i]);
		}
	}
	dfs(1,0);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sovle();
	for(int i=1;i<=n;i++)swap(a[i].fi,a[i].se);
	sovle();
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("game.in","r",stdin);
	// freopen("game.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<" MB\n";
	
	T=1;
	while(T--)work();
}