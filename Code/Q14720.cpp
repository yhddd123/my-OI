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
const int maxm=1000010;
const int inf=1e9;
bool mbe;

int n,qq;
vector<int> e[maxn];
int dep[maxn];
int ddfn[maxn],out[maxn],bfn[maxn],rnk[maxn],tim;
vector<int> pos[maxn];
void dfs(int u){
	pos[dep[u]].pb(u);
	ddfn[u]=++tim;out[u]=u;
	for(int v:e[u])dep[v]=dep[u]+1,dfs(v),out[u]=out[v];
}
vector<int> g[maxm];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int idx,rt1,rt2;
struct sgt1{
	int lc[maxm],rc[maxm];
	void build(int &nd,int l,int r){
		if(l==r){
			nd=rnk[l]+n;
			return ;
		}
		nd=++idx;
		build(ls,l,mid),build(rs,mid+1,r);
		g[nd].pb(ls),g[nd].pb(rs);
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		// cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<w<<endl;
		if(l>=ql&&r<=qr){
			g[w].pb(nd);
			return ;
		}
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	}
}t1;
struct sgt2{
	int lc[maxm],rc[maxm];
	void build(int &nd,int l,int r){
		if(l==r){
			nd=rnk[l];
			return ;
		}
		nd=++idx;
		build(ls,l,mid),build(rs,mid+1,r);
		g[ls].pb(nd),g[rs].pb(nd);
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){
			g[nd].pb(w);
			return ;
		}
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	}
}t2;
int dfn[maxm],lw[maxm],iidx;
int st[maxm],tp;
int scc[maxm],scct;
void tar(int u){
	dfn[u]=lw[u]=++iidx;st[++tp]=u;
	for(int v:g[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		++scct;scc[st[tp]]=scct;
		while(st[tp--]!=u)scc[st[tp]]=scct;
	}
}
vector<int> h[maxm];int d[maxm];
int topu[maxm],tpidx;
void work(){
	n=read();
	for(int i=1;i<=n;i++)e[i].clear(),pos[i].clear();
	for(int i=2;i<=n;i++)e[read()].pb(i);
	tim=0;dfs(1);
	queue<int> q;q.push(1);
	tim=0;while(!q.empty()){
		int u=q.front();q.pop();
		bfn[u]=++tim,rnk[tim]=u;
		for(int v:e[u])q.push(v);
	}
	for(int i=1;i<=idx;i++)g[i].clear();
	idx=2*n;
	for(int u=1;u<=n;u++){
		for(int v:e[u])g[u+n].pb(v),g[v+n].pb(u);
	}
	t1.build(rt1,1,n);
	t2.build(rt2,1,n);
	qq=read();
	vector<pii> ask;
	while(qq--){
		int u=read(),d=dep[u]+read();
		if(d>n)continue;
		ask.pb({u,d});
		int pl=lower_bound(pos[d].begin(),pos[d].end(),u,[&](int u,int v){return ddfn[u]<ddfn[v];})-pos[d].begin();
		int pr=upper_bound(pos[d].begin(),pos[d].end(),out[u],[&](int u,int v){return ddfn[u]<ddfn[v];})-pos[d].begin()-1;
		if(pl>pr)continue;
		// cout<<u<<" "<<pos[d][pl]<<" "<<pos[d][pr]<<"\n";
		t1.updata(rt1,1,n,bfn[pos[d][pl]],bfn[pos[d][pr]],u);
		t2.updata(rt2,1,n,bfn[pos[d][pl]],bfn[pos[d][pr]],u+n);
	}
	for(int i=1;i<=idx;i++)dfn[i]=scc[i]=0;iidx=scct=0;
	for(int i=1;i<=idx;i++)if(!dfn[i])tar(i);
	for(int i=1;i<=n;i++)if(scc[i]==scc[i+n]){puts("No");return ;}
	for(int i=1;i<=scct;i++)h[i].clear(),d[i]=0;
	for(int u=1;u<=idx;u++){
		for(int v:g[u])if(scc[u]!=scc[v])h[scc[u]].pb(scc[v]),d[scc[v]]++;
	}
	for(int i=1;i<=scct;i++)if(!d[i])q.push(i);
	tpidx=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		topu[u]=++tpidx;
		for(int v:h[u]){
			d[v]--;
			if(!d[v])q.push(v);
		}
	}
	vector<int> ans;
	for(int i=1;i<=n;i++)if(topu[scc[i]]>topu[scc[i+n]])ans.pb(i);
	puts("Yes");
	printf("%d\n",ans.size());
	for(int u:ans)printf("%d ",u);puts("");
	// vector<bool> vis(n+1);
	// for(int v:ans)vis[v]=1;
	// for(int u=1;u<=n;u++){
		// for(int v:e[u]){
			// if(!vis[u]&&!vis[v]){
				// cerr<<"Wa\n";
				// assert(0);
			// }
		// }
	// }
	// for(auto[u,d]:ask){
		// for(int v=1;v<=n;v++)if(ddfn[u]<=ddfn[v]&&ddfn[v]<=ddfn[out[u]]&&dep[v]==d){
			// if(vis[u]&&vis[v]){
				// cerr<<"Wa\n";
				// assert(0);
			// }
		// }
	// }
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