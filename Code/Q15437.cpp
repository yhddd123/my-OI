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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int op,n,m;
vector<int> e[maxn];
namespace sub1{
	int a[maxn];
	bool vis[maxn],bk[maxn];
	vector<pii> sovle(){
		vector<pii> edge,nw;
		for(int i=1;i<=m;i++){
			int u=read(),v=read();
			edge.pb({u,v});
		}
		int k=read();
		for(int i=1;i<=k;i++)a[i]=read(),vis[a[i]]=1;
		for(auto[u,v]:edge){
			if(!vis[u]&&!vis[v]){
				if(u>v)swap(u,v);
				nw.pb({u,v});
			}
			else if(vis[u]&&vis[v]){
				e[u].pb(v),e[v].pb(u);
			}
			else{
				if(!vis[u])swap(u,v);
				nw.pb({u,v});
			}
		}
		for(int i=1;i<=k;i++){
			int u=a[i];
			for(int v:e[u])if(vis[v]){
				if(i!=k&&v==a[i%k+1])nw.pb({u,v});
				else if(!bk[v])nw.pb({v,u});
			}
			bk[u]=1;
		}
		return nw;
	}
}
namespace sub2{
	int ff[maxn],hd[maxn];
	int fd(int x){
		if(ff[x]==x)return x;
		return x=fd(ff[x]);
	}
	list<int> a[maxn];
	set<int> e[maxn],g[maxn];
	int d[maxn];
	bool vis[maxn],bk[maxn];
	vector<int> sovle(vector<pii> edge){
		for(auto[u,v]:edge)d[u]++,e[u].insert(v),g[v].insert(u);
		queue<int> q;
		for(int i=1;i<=n;i++)if(!d[i])q.push(i);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v:g[u]){
				d[v]--;
				if(!d[v])q.push(v);
			}
		}
		for(int i=1;i<=n;i++)if(d[i])bk[i]=1;
		for(int u=1;u<=n;u++)if(bk[u]){
			set<int> ee;
			for(int v:e[u])if(bk[v])ee.insert(v);
			e[u]=ee;
			set<int> gg;
			for(int v:g[u])if(bk[v])gg.insert(v);
			g[u]=gg;
		}
		int p=0;for(int i=1;i<=n;i++)if(d[i]==1)q.push(i);
		for(int i=1;i<=n;i++)if(bk[i])a[i].pb(i);
		for(int i=1;i<=n;i++)ff[i]=hd[i]=i;
		int rt=0;
		while(q.size()){
			int u=q.front();q.pop();
			if(!e[u].size()){rt=u;break;}
			int v=fd(*e[u].begin()),vv=*e[u].begin();
			rt=v;ff[u]=v;hd[v]=hd[u];
			for(int w:g[v]){
				d[w]--;
				e[w].erase(vv);
				if(d[w]==1)q.push(w);
			}
			if(e[v].find(hd[u])!=e[v].end()){
				d[v]--;e[v].erase(hd[u]),g[u].erase(v);
				if(d[v]==1)q.push(v);
			}
			g[v].clear();swap(g[u],g[v]);
			a[u].splice(a[u].end(),a[v]),swap(a[u],a[v]);
		}
		vector<int> id;
		for(int u:a[rt])id.pb(u);
		return id;
	}
}
mt19937 rnd(0);
int id[maxn],rnk[maxn];
void work(){
	op=read();n=read();m=read();
	vector<pii> edge;
	if(op==1){
		edge=sub1::sovle();
		for(auto[u,v]:edge)printf("%d %d\n",u,v);
		// assert(edge.size()==m);
		// shuffle(edge.begin(),edge.end(),rnd);
		// for(int i=1;i<=n;i++)id[i]=i;
		// shuffle(id+1,id+n+1,rnd);
		// for(int i=1;i<=n;i++)rnk[id[i]]=i;
		// for(auto&[u,v]:edge)u=rnk[u],v=rnk[v];
		// // for(auto[u,v]:edge)printf("%d %d\n",u,v);
		// vector<int> a=sub2::sovle(edge);
		// // for(int u:a)printf("%d ",u);puts("");
		// for(int &u:a)u=id[u];
		// // for(int u:a)printf("%d ",u);puts("");
		// pii mn={a[0],0};
		// for(int i=1;i<a.size();i++)mn=min(mn,{a[i],i});
		// rotate(a.begin(),a.begin()+mn.se,a.end());
		// for(int u:a)printf("%d ",u);puts("");
	}
	else{
		for(int i=1;i<=m;i++){
			int u=read(),v=read();
			edge.pb({u,v});
		}
		vector<int> a=sub2::sovle(edge);
		for(int u:a)printf("%d ",u);puts("");
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