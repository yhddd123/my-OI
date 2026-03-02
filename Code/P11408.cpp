// Problem: P11408 [RMI 2020] 树咖 / Arboras
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11408
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-03-02 18:30:20
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int inf=1e18;
bool mbe;

int n,q,ans;
vector<int> e[maxn],g[maxn];
int fa[maxn],dep[maxn],dis[maxn],siz[maxn],son[maxn];
int pp[maxn],pmx[maxn],pse[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i],w=g[u][i];
		dep[v]=dep[u]+1,dis[v]=dis[u]+w;
		dfs(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	for(int i=1;i<e[u].size();i++)if(e[u][i]==son[u])swap(e[u][0],e[u][i]);
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];pp[v]=i;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn],ed[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u,tp[u]=lst;ed[u]=u;
	if(!son[u])return ;dfs(son[u],lst);ed[u]=ed[son[u]];
	for(int v:e[u])if(v!=son[u])dfs(v,v);
}
int get(int u,int v){return lower_bound(e[u].begin(),e[u].end(),v,[&](int x,int y){return dfn[x]<dfn[y];})-e[u].begin();}
#define lb(x) (x&(-x))
struct bit{
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void udis(int u,int w){upd(dfn[u],w),upd(dfn[u]+siz[u],-w);}
int qdis(int u){return que(dfn[u]);}
}t;
#define mid ((l+r)>>1)
namespace sgt1{
#define ls nd<<1
#define rs nd<<1|1
pii mx[maxn<<2];int tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mx[nd]={dis[rnk[l]],rnk[l]};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mx[nd]=max(mx[ls],mx[rs]);
}
void upd(int nd,int w){mx[nd].fi+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {0,0};
	if(l>=ql&&r<=qr)return mx[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
#undef ls
#undef rs
}
int rt[maxn];
#define all(u) rt[u],0,e[u].size()-1
namespace sgt2{
#define ls lc[nd]
#define rs rc[nd]
pii mx[maxn<<1];
int lc[maxn<<1],rc[maxn<<1],idx;
void build(int &nd,int l,int r){
	nd=++idx;mx[nd]={0,0};
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p,pii w={0,0}){
	if(l==r){mx[nd]=w;return ;}
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {0,0};
	if(l>=ql&&r<=qr)return mx[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
}
pii operator-(pii u,int w){return {u.fi-w,u.se};}
pii que(int u){return sgt1::query(1,1,n,dfn[u],dfn[u]+siz[u]-1);}
void mdf(int u,int v){sgt2::modif(all(u),pp[v],{que(v).fi-t.qdis(u),pp[v]});}
struct node{
	int l,r;
};
bool operator<(node u,node v){return u.l>v.r;}
set<node> s[maxn];
void work(){
	n=read();
	for(int i=2;i<=n;i++)e[fa[i]=read()+1].pb(i);
	for(int i=2;i<=n;i++)g[fa[i]].pb(read());
	dfs(1),dfs(1,1);
	for(int i=1;i<=n;i++)t.upd(i,dis[rnk[i]]-dis[rnk[i-1]]);
	sgt1::build(1,1,n);
	for(int u=1;u<=n;u++)if(e[u].size()){
		sgt2::build(all(u));
		for(int v:e[u])mdf(u,v);
		int val=sgt2::mx[rt[u]].fi;
		pmx[u]=sgt2::mx[rt[u]].se;
		sgt2::modif(all(u),pmx[u]);
		pse[u]=sgt2::mx[rt[u]].se;
		val+=sgt2::mx[rt[u]].fi;
		(ans+=val)%=mod;
	}
	for(int u=1;u<=n;u++)if(tp[u]==u){
		for(int l=dfn[u],r;l<=dfn[ed[u]];l=r+1){
			r=l;
			while(r<dfn[ed[u]]&&!pmx[rnk[r]])r++;
			s[u].insert({l,r});
		}
	}
	printf("%lld\n",ans);
	q=read();
	while(q--){
		int u=read()+1,w=read();t.udis(u,w);sgt1::updata(1,1,n,dfn[u],dfn[u]+siz[u]-1,w);
		auto chk=[&](int u){
			if(u==1)return 0;
			int v=u;u=fa[u];
			if(e[u][pmx[u]]==v)(ans+=w)%=mod;
			else{
				pii d1=que(e[u][pmx[u]]),d2=que(v);
				int lst=sgt2::mx[rt[u]].fi;
				if(d2>d1){
					(ans+=d2.fi-d1.fi)%=mod;
					w=d2.fi-d1.fi;
					mdf(u,e[u][pmx[u]]);
					pmx[u]=pp[v];sgt2::modif(all(u),pmx[u]);
				}
				else mdf(u,v);
				pse[u]=sgt2::mx[rt[u]].se;
				(ans+=sgt2::mx[rt[u]].fi-lst)%=mod;
				if(d1>d2)return 0;
			}
			return 1;
		};
		while(fa[u]){
			if(u!=tp[u]){
				auto it=s[tp[u]].find({dfn[u],dfn[u]});
				bool fl=1;
				auto[l,r]=*it;it=s[tp[u]].erase(it);
				int p=rnk[r];
				(ans+=(dep[u]-dep[rnk[l]])*w)%=mod;u=rnk[l];
				while(u!=tp[u]){
					if(!chk(u)){fl=0;break;}
					u=fa[u];
					auto[l,r]=*it;it=s[tp[u]].erase(it);
					(ans+=(dep[u]-dep[rnk[l]])*w)%=mod;u=rnk[l];
				}
				s[tp[u]].insert({dfn[u],dfn[p]});
				if(!fl)break;
			}
			if(!chk(u))break;
			u=fa[u];
			if(pmx[u]){
				auto it=s[tp[u]].find({dfn[u],dfn[u]});
				auto[l,r]=*it;
				if(dfn[u]<r){
					s[tp[u]].erase(it);
					s[tp[u]].insert({l,dfn[u]});
					s[tp[u]].insert({dfn[u]+1,r});
				}
			}
		}
		printf("%lld\n",ans);fflush(stdout);
	}
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}