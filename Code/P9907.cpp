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
const int maxn=100010;
const int maxm=300010;
const int inf=1e9;
bool mbe;

int n,m;
bool ans[maxm];
vector<pii> e[maxn],g[maxn],h[maxn];
int dep[maxn];
bool vis[maxn];
void dfs(int u){
	vis[u]=1;
	for(auto[v,id]:e[u]){
		if(vis[v]){
			if(dep[v]<dep[u]-1)h[u].pb({v,id});
		}
		else dep[v]=dep[u]+1,g[u].pb({v,id}),dfs(v);
	}
}
int v1[maxn],v2[maxn];
void dfs(int u,int o){
	v1[u]=n,v2[u]=0;
	for(auto[v,id]:h[u]){
		if(o&&v==1)continue;
		v1[u]=min(v1[u],dep[v]);
	}
	for(auto[v,id]:g[u]){
		dfs(v,o);
		v2[u]=max(v2[u],v1[v]);
		v1[u]=min(v1[u],v1[v]);
	}
}
set<int> s[maxn];
#define lb(x) (x&(-x))
struct bit{
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
void upd(int l,int r,int w){
	if(l>r)return ;
	upd(l,w),upd(r+1,-w);}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
}t1,t2;
void dfs1(int u){
	multiset<int> ss;ss.insert(0);
	for(auto[v,id]:g[u])ss.insert(v1[v]);
	int mn=n;for(auto[v,id]:h[u])mn=min(mn,dep[v]);
	t2.upd(mn+1,dep[u]-1,1);
	// cout<<u<<" "<<mn+1<<" "<<dep[u]-1<<" u2\n";
	for(auto[v,id]:g[u]){
		// cout<<u<<" "<<v<<"\n";
		ss.erase(ss.find(v1[v]));
		int lst=-1;
		if(u!=1&&v2[v]<dep[u]&&(*--ss.end())<dep[u])ans[id]=0;
		if(ss.size()>1){
			int mn=*++ss.begin();
			t2.upd(mn+1,dep[u]-1,1);lst=mn;
			// cout<<mn+1<<" "<<dep[u]-1<<" u2\n";
		}
		ss.insert(v1[v]);
		dfs1(v);
		if(lst!=-1)t2.upd(lst+1,dep[u]-1,-1);
	}
	t2.upd(mn+1,dep[u]-1,-1);
	map<int,bool> ban;
	for(auto[v,id]:g[u]){
		if(s[v].size()==1)ban[*s[v].begin()]=1;
	}
	if(v2[u]<dep[u]){
		for(auto[v,id]:h[u])if(ans[id]){
			if(v==1)continue;
			if(ban.find(dep[v])==ban.end()&&v2[v]<dep[v]&&t2.que(dep[v]))ans[id]=0;
			// cout<<u<<" "<<v<<" "<<ans[id]<<"\n";
		}
	}
	if(v2[u]<dep[u]){
		for(auto[v,id]:g[u]){
			int pl=*s[v].begin(),pr=*--s[v].end();
			t1.upd(pl+1,pr-1,1);
		}
		for(auto[v,id]:h[u]){
			if(v==1)continue;
			if(ban.find(dep[v])==ban.end()&&v2[v]<dep[v]&&t1.que(dep[v]))ans[id]=0;
		}
		for(auto[v,id]:g[u]){
			int pl=*s[v].begin(),pr=*--s[v].end();
			t1.upd(pl+1,pr-1,-1);
		}
	}
	for(auto[v,id]:g[u]){
		if(s[u].size()<s[v].size())swap(s[u],s[v]);
		for(int p:s[v])s[u].insert(p);
	}
	for(auto[v,id]:h[u])s[u].insert(dep[v]);
	while(s[u].size()&&(*--s[u].end())>=dep[u]-1)s[u].erase(--s[u].end());
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();ans[i]=1;
		e[u].pb({v,i}),e[v].pb({u,i});
	}
	dfs(1);
	if(g[1].size()>1){
		if(g[1].size()==2){
			for(auto[v,id]:g[1])if(!g[v].size())ans[id]=0;
		}
	}
	else{
		dfs(1,1);
		for(auto[v,id]:e[1]){
			if(v==g[1][0].fi){
				if(g[v].size()==1)ans[id]=0;
			}
			else{
				if(v2[v]<dep[v])ans[id]=0;
			}
		}
	}
	dfs(1,0);
	// for(int i=1;i<=n;i++)cout<<v1[i]<<" "<<v2[i]<<" "<<dep[i]<<"\n";
	dfs1(1);
	int res=0;for(int i=1;i<=m;i++)res+=ans[i];
	// for(int i=1;i<=m;i++)cout<<ans[i];cout<<"\n";
	printf("%lld\n",res);
}

bool med;
int T;
signed main(){
	// freopen("bridge.in","r",stdin);
	// freopen("bridge.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}