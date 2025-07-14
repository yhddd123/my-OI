#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
set<pii> s;
vector<int> e[maxn];
mt19937 rnd(time(0));
int id[maxn],tp;
bool vis[maxn];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(u>v)swap(u,v);
		s.insert({u,v});
	}
	while(k--){
		for(int i=1;i<=n;i++)vis[i]=0,e[i].clear();
		id[tp=1]=rnd()%n+1;vis[id[1]]=1;
		for(auto[x,y]:s)e[x].pb(y),e[y].pb(x);
		while(tp<n){
			if(rnd()&1)reverse(id+1,id+tp+1);
			int u=id[tp];bool fl=0;
			shuffle(e[u].begin(),e[u].end(),rnd);
			for(int v:e[u])if(!vis[v]){
				vis[v]=fl=1;id[++tp]=v;
				break;
			}
			if(fl)continue;
			for(int i=1;i<=tp;i++)if(id[i]==e[u].back()){
				reverse(id+i+1,id+tp+1);
				break;
			}
		}
		for(int i=1;i<=tp;i++)printf("%lld ",id[i]);puts("");
		for(int i=1;i<tp;i++)s.erase({min(id[i],id[i+1]),max(id[i],id[i+1])});
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
