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

int n,m;
mt19937 rnd(time(0));
char s[maxn];
vector<int> e[maxn];
int col[maxn];
vector<int> id[2];
void dfs(int u,int fa){
	col[u]=col[fa]^1;
	if(e[u].size()>1)id[col[u]].pb(u);
	for(int v:e[u])if(v!=fa)dfs(v,u);
}
void work(){
	n=rnd()%15+1,m=n-1;
	cout<<n<<" "<<m<<"\n";
	vector<pii> edge;
	for(int i=2;i<=n;i++)edge.pb({rnd()%(i-1)+1,i});
	shuffle(edge.begin(),edge.end(),rnd);
	for(int i=0;i<m;i++){
		auto[u,v]=edge[i];
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	int k1=rnd()%(id[0].size()+1),k2=rnd()%(id[1].size()+1);
	shuffle(id[0].begin(),id[0].end(),rnd);
	shuffle(id[1].begin(),id[1].end(),rnd);
	for(int i=1;i<=n;i++)s[i]='0';
	for(int i=0;i<k1;i++)s[id[0][i]]='1';
	for(int i=0;i<k2;i++)s[id[1][i]]='1';
	for(int i=1;i<=n;i++)cout<<s[i];cout<<"\n";
	shuffle(id[0].begin(),id[0].end(),rnd);
	shuffle(id[1].begin(),id[1].end(),rnd);
	for(int i=1;i<=n;i++)s[i]='0';
	for(int i=0;i<k1;i++)s[id[0][i]]='1';
	for(int i=0;i<k2;i++)s[id[1][i]]='1';
	for(int i=1;i<=n;i++)cout<<s[i];cout<<"\n";
	for(auto[u,v]:edge)cout<<u<<" "<<v<<"\n";
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	cout<<T<<"\n";
	while(T--)work();
}