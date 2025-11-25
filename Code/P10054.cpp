#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline ll read(){
	ll x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=2e9;
bool mbe;

int n,m1,m2,ans=inf;ll k;
struct ds{
	int t1[maxn<<1],t2[maxn<<1];ll ans;
	unordered_map<ll,int> mp;
	void ins(int u,int v){
		ans+=t1[u]+t2[v]-mp[1ll*u*2*n+v];
		t1[u]++,t2[v]++,mp[1ll*u*2*n+v]++;
		// cout<<u<<" "<<v<<" "<<ans<<" ins\n";
	}
	void del(int u,int v){
		t1[u]--,t2[v]--,mp[1ll*u*2*n+v]--;
		ans-=t1[u]+t2[v]-mp[1ll*u*2*n+v];
		// cout<<u<<" "<<v<<" "<<ans<<" del\n";
	}
}a;
int fa[2][maxn];
struct graph{
	int op;
	int lsh[maxn],len;
	vector<pii> pos[maxn];
	vector<tuple<int,int,int>> edge;
	void add(int u,int v,int w){
		edge.pb({w,u,v});
		lsh[++len]=w;
	}
	set<int> e[maxn],id[maxn<<1];
	int idx;
	struct node{
		int u,fa;
		set<int>::iterator it;
	};
	void add(int u,int v){
		e[u].insert(v),e[v].insert(u);
		int uu=fa[op][u],vv=fa[op][v];
		if(id[uu].size()<id[vv].size())swap(u,v),swap(uu,vv);
		for(int i:id[vv]){
			a.del(fa[0][i],fa[1][i]);
			fa[op][i]=uu,id[uu].insert(i);
			a.ins(fa[0][i],fa[1][i]);
		}
		id[vv].clear();
	}
	void del(int u,int v){
		e[u].erase(v),e[v].erase(u);
		vector<int> pos[2];
		queue<node> que[2];
		pos[0].pb(u),pos[1].pb(v);
		if(e[u].size())que[0].push({u,0,e[u].begin()});
		if(e[v].size())que[1].push({v,0,e[v].begin()});
		while(que[0].size()&&que[1].size()){
			int o=pos[1].size()<pos[0].size();
			auto[u,fa,it]=que[o].front();que[o].pop();
			int v=(*it);
			if(v!=fa){
				pos[o].pb(v);
				if(e[v].size())que[o].push({v,u,e[v].begin()});
			}
			it++;
			if(it==e[u].end())continue;
			if((*it)==fa)it++;
			if(it==e[u].end())continue;
			que[o].push({u,fa,it});
		}
		if(!que[0].size()&&(que[1].size()||pos[0].size()<pos[1].size())){
			swap(u,v),swap(pos[0],pos[1]);
		}
		++idx;
		for(int i:pos[1]){
			a.del(fa[0][i],fa[1][i]);
			id[fa[op][u]].erase(i),id[idx].insert(i),fa[op][i]=idx;
			a.ins(fa[0][i],fa[1][i]);
		}
	}
	int ff[maxn];
	int fd(int x){
		if(ff[x]==x)return x;
		return ff[x]=fd(ff[x]);
	}
	void init(int _o){
		op=_o;
		sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
		sort(edge.begin(),edge.end());
		for(int i=1;i<=n;i++)ff[i]=i;
		for(auto[w,u,v]:edge){
			w=lower_bound(lsh+1,lsh+len+1,w)-lsh;
			if(fd(u)==fd(v))continue;
			ff[fd(u)]=fd(v);
			pos[w].pb({u,v});
			// cout<<u<<" "<<v<<" "<<w<<" "<<lsh[w]<<"\n";
		}
		idx=n;
		for(int i=1;i<=n;i++)fa[op][i]=i,id[i].insert(i);
	}
}g1,g2;
void work(){
	n=read();m1=read();m2=read();k=read();
	if(!k){puts("0");return ;}
	vector<tuple<int,int,int>> edge1,edge2;
	for(int i=1;i<=m1;i++){
		int u=read(),v=read(),w=read();
		g1.add(u,v,w);
	}
	for(int i=1;i<=m2;i++){
		int u=read(),v=read(),w=read();
		g2.add(u,v,w);
	}
	g1.init(0),g2.init(1);
	for(int i=1;i<=n;i++)a.ins(fa[0][i],fa[1][i]);
	for(int i=1;i<=g2.len;i++){
		for(auto[u,v]:g2.pos[i])g2.add(u,v);
		if(a.ans>=k){ans=min(ans,g2.lsh[i]);break;}
	}
	for(int i=1,j=g2.len;i<=g1.len;i++){
		for(auto[u,v]:g1.pos[i])g1.add(u,v);
		while(a.ans>=k){
			ans=min(ans,g1.lsh[i]+g2.lsh[j]);
			if(!j)break;
			for(auto[u,v]:g2.pos[j])g2.del(u,v);j--;
		}
	}
	if(ans==inf)ans=-1;
	printf("%d\n",ans);
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