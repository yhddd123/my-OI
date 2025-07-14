#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=2000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,ans;
int in[maxn];
set<int> e[maxn],g[maxn];
void add(int u,int v){e[u].insert(v),g[v].insert(u);}
set<int> s;
vector<int> a[maxn];
int pos[maxn],idx;
bool vis[maxn];
void dfs(int u){
	if(vis[u])return ;vis[u]=1;
	for(int v:e[u]){
		g[v].erase(u);
		dfs(v);
	}
	for(int v:a[u])if(pos[v]==u){
		if(s.find(v)!=s.end())s.erase(s.find(v));
	}
	for(int v:g[u]){
		e[v].erase(u);
		if(!e[v].size())dfs(v);
	}
}
void work(){
	n=read();q=read();ans=0;idx=n;s.clear();
	for(int i=1;i<=n;i++){
		s.insert(i);pos[i]=i;vis[i]=0;
		a[i].clear(),a[i].push_back(i);
		e[i].clear(),g[i].clear();
	}
	while(q--){
		char op[3];scanf("%s",op+1);
		if(op[1]=='K'){
			int k=read();++idx;vis[idx]=0;
			e[idx].clear(),g[idx].clear();
			a[idx].clear();
			for(int i=1;i<=k;i++){
				int p=(read()-1+ans)%n+1;
				a[idx].push_back(p);
				if(!vis[pos[p]])add(idx,pos[p]);
				pos[p]=idx;
			}
			if(!e[idx].size())vis[idx]=1;
			else for(int i:a[idx])s.insert(i);
		}
		if(op[1]=='N'){
			int p=(read()-1+ans)%n+1;
			dfs(pos[p]);
		}
		if(op[1]=='P'){
			int p=(read()-1+ans)%n+1;
			if(s.find(p)!=s.end())s.erase(s.find(p));
		}
		if(op[1]=='Q'){
			int p=(read()-1+ans)%n+1;
			if(!s.size())printf("TAK\n"),ans=0;
			else printf("NIE %lld\n",ans=(s.lower_bound(p)!=s.end()?(*s.lower_bound(p)):(*s.begin())));
		}
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
	
	T=read();
	while(T--)work();
}
