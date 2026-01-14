#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<ll,int>
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

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int n;ll ans;
vector<pii> edge;
namespace sub1{
vector<int> e[maxn],g[maxn];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,u.se+v.se};}
pii operator+(pii u,pii v){
	if(u.se<v.se)return u;
	if(u.se>v.se)return v;
	int val=(u.fi+v.fi)%mod;
	if(!val)return {1ll,u.se+1};
	return {val,u.se};}
pii operator/(pii u,pii v){return {u.fi*ksm(v.fi)%mod,u.se-v.se};}
int calc(pii u){return u.se?0:u.fi;}
pii f[maxn];int fa[maxn],to[maxn];
void dfs(int u,int _fa){
	fa[u]=_fa;
	f[u]={1ll,0};
	for(int v:g[u]){
		dfs(v,u);
		int w=to[v];
		for(int p=fd(w);p!=v;p=fd(p)){
			f[v]=f[v]/(f[p]+make_pair(1ll,0))*f[p];
			ff[p]=fd(fa[p]);
		}
		f[u]=f[u]*(f[v]+make_pair(1ll,0));
	}
	(ans+=calc(f[u]))%=mod;
}
void sovle(){
	for(auto[u,v]:edge)e[u].pb(v),e[v].pb(u);
	for(int i=1;i<=n;i++)ff[i]=i;
	for(int u=1;u<=n;u++){
		for(int v:e[u])if(v<u){
			to[fd(v)]=v;
			v=fd(v);
			g[u].pb(v);
			ff[v]=u;
		}
	}
	for(int i=1;i<=n;i++)ff[i]=i;
	dfs(n,0);
	printf("%lld\n",ans);
}
}
namespace sub2{
vector<int> e[maxn],g[maxn],h[maxn];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int fa1[maxn],fa2[maxn];
int vis[maxn];
struct Lca{
	int dfn[maxn],st[18][maxn],idx;
	void dfs(int u,int fa){
		st[0][dfn[u]=++idx]=fa;
		for(int v:g[u])dfs(v,u);
	}
	int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
	int lca(int u,int v){
		if(u==v)return u;
		u=dfn[u],v=dfn[v];
		if(u>v)swap(u,v);u++;
		int k=__lg(v-u+1);
		return mmax(st[k][u],st[k][v-(1<<k)+1]);
	}
	void init(int rt){
		dfs(rt,0);
		for(int j=1;j<18;j++){
			for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
		}
	}
}t1,t2;
int siz[maxn],son[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0;
	for(int v:h[u]){
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],tim,tp[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++tim]=u;tp[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int v:h[u])if(v!=son[u])dfs(v,v);
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
const int maxm=maxn<<6;
pii mn[maxm];int tag[maxm];
int lc[maxm],rc[maxm],rt[maxn],idx;
int st[maxm],top;
int newnode(){int nw=top?st[top--]:++idx;mn[nw]={inf,1};return nw;}
void del(int nd){st[++top]=nd;tag[nd]=lc[nd]=rc[nd]=0;}
void upd(int nd,int w){mn[nd].fi+=w,tag[nd]+=w;}
void down(int nd){
	if(!ls)ls=newnode();
	if(!rs)rs=newnode();
	upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
pii operator+(pii u,pii v){return {min(u.fi,v.fi),(u.fi<=v.fi)*u.se+(u.fi>=v.fi)*v.se};}
void updata(int &nd,int l,int r,int ql,int qr,int w){
	if(!nd)nd=newnode();
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=mn[ls]+mn[rs];
}
void modif(int &nd,int l,int r,int p){
	if(!nd)nd=newnode();
	if(l==r){mn[nd]={0,1};return ;}
	if(tag[nd])down(nd);
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	mn[nd]=mn[ls]+mn[rs];
}
int merge(int u,int v,int l,int r){
	// cout<<u<<" "<<v<<" "<<mn[u].fi<<" "<<tag[u]<<" "<<mn[v].fi<<" "<<l<<" "<<r<<"\n";
	if(!u||!v)return u|v;
	if(!lc[u]&&!lc[v]&&!rc[u]&&!rc[v]){
		if(mn[u].fi>=inf)swap(u,v);
		upd(u,tag[v]);
		del(v);return u;
	}
	if(!lc[u]&&!rc[u]){
		upd(v,tag[u]);
		del(u);return v;
	}
	if(!lc[v]&&!rc[v]){
		upd(u,tag[v]);
		del(v);return u;
	}
	if(tag[u])down(u);
	if(tag[v])down(v);
	lc[u]=merge(lc[u],lc[v],l,mid),rc[u]=merge(rc[u],rc[v],mid+1,r);
	mn[u]=mn[lc[u]]+mn[rc[u]];
	del(v);return u;
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){return mn[nd];}
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void updpath(int &rt,int u,int w){
	while(u){
		updata(rt,1,n,dfn[tp[u]],dfn[u],w);
		u=fa2[tp[u]];
	}
}
pii quepath(int &rt,int u){
	pii res={inf,0};
	while(u){
		res=res+query(rt,1,n,dfn[tp[u]],dfn[u]);
		u=fa2[tp[u]];
	}
	return res;
}
vector<int> mdf[maxn];
void dfs1(int u){
	for(int v:g[u]){
		dfs1(v);
		rt[u]=merge(rt[u],rt[v],1,n);
		// cout<<u<<" "<<v<<" e\n";
		// for(int i=1;i<=n;i++)cout<<query(rt[u],1,n,dfn[i],dfn[i]).fi<<" ";cout<<"\n";
	}
	modif(rt[u],1,n,dfn[u]);
	updpath(rt[u],u,2);
	// for(int v:mdf[u])cout<<u<<" "<<v<<" m\n";
	for(int v:mdf[u])updpath(rt[u],v,-1);
	pii res=quepath(rt[u],u);
	if(res.fi==2)ans+=res.se;
	// cout<<u<<" "<<res.fi<<" "<<res.se<<" "<<ans<<" 	d\n";
	// for(int i=1;i<=n;i++)cout<<query(rt[u],1,n,dfn[i],dfn[i]).fi<<" ";cout<<"\n";
}
void sovle(){
	for(auto[u,v]:edge)e[u].pb(v),e[v].pb(u);
	for(int i=1;i<=n;i++)ff[i]=i;
	for(int u=1;u<=n;u++){
		for(int v:e[u])if(v<u){
			v=fd(v);
			g[u].pb(v);fa1[v]=u;
			ff[v]=u;
		}
	}
	for(int i=1;i<=n;i++)ff[i]=i;
	for(int u=n;u;u--){
		for(int v:e[u])if(v>u){
			v=fd(v);
			h[u].pb(v);fa2[v]=u;
			ff[v]=u;
		}
	}
	t1.init(n);
	swap(g,h);
	t2.init(1);
	swap(g,h);
	for(int u=1;u<=n;u++){
		for(int v:g[u])mdf[u].pb(t2.lca(u,v));
		// for(int v:g[u])cout<<u<<" "<<v<<" "<<t2.lca(u,v)<<" a\n";
		for(int v:h[u])mdf[t1.lca(u,v)].pb(u);
		// for(int v:h[u])cout<<u<<" "<<v<<" "<<t1.lca(u,v)<<" b\n";
	}
	dfs(1),dfs(1,1);
	mn[0]={2*inf,0};
	dfs1(n);
	ans%=mod;
	printf("%lld\n",ans);
}
}
void work(){
	int op=read();
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		edge.pb({u,v});
	}
	if(op==1)return sub1::sovle();
	else return sub2::sovle();
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