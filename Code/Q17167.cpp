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
const int inf=1e9;
bool mbe;

int n,q;
char s[maxn];
vector<int> e[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
	for(int v:e[u]){
		if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	for(int j=0;j<e[u].size();j++)if(e[u][j]==fa[u])e[u][j]=e[u].back(),e[u].pop_back();
	for(int j=0;j<e[u].size();j++)if(e[u][j]==son[u])swap(e[u][0],e[u][j]);
}
int dfn[maxn],rnk[maxn],idx,tp[maxn],ed[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u,tp[u]=lst;
	if(!son[u])return ;
	dfs(son[u],lst);
	for(int v:e[u])if(v!=son[u])dfs(v,v);
}
inline pii operator+(pii u,int v){return {u.fi+v,u.se};}
inline pii operator-(pii u,int v){return {u.fi-v,u.se};}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii val[maxn];
struct worker{
	int get(int u,int v){
		if(!v)return 0;
		int p=upper_bound(e[u].begin(),e[u].end(),v,[&](int x,int y){return dfn[x]<dfn[y];})-e[u].begin()-1;
		return e[u][p];
	}
	char op;
	struct sgt{
		pii mn[maxn<<2];
		void build(int nd,int l,int r){
			if(l==r){mn[nd]=val[l];return ;}
			build(ls,l,mid),build(rs,mid+1,r);
			mn[nd]=min(mn[ls],mn[rs]);
		}
		void modif(int nd,int l,int r,int p,pii w){
			if(l==r){mn[nd]=w;return ;}
			if(p<=mid)modif(ls,l,mid,p,w);
			else modif(rs,mid+1,r,p,w);
			mn[nd]=min(mn[ls],mn[rs]);
		}
		pii query(int nd,int l,int r,int ql,int qr){
			if(ql>qr)return {inf,0};
			if(l>=ql&&r<=qr)return mn[nd];
			if(qr<=mid)return query(ls,l,mid,ql,qr);
			if(ql>mid)return query(rs,mid+1,r,ql,qr);
			return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
		}
	}t1,t2;
	pii calc(int u){
		return min(make_pair(d[u],u),t1.query(1,1,n,dfn[son[u]]+siz[son[u]],dfn[u]+siz[u]-1))-2*dep[u];
	}
	int d[maxn];
	void init(char _o){
		op=_o;
		for(int i=1;i<=n;i++){
			if(s[i]==op)d[i]=dep[i];
			else d[i]=inf;
		}
		for(int i=1;i<=n;i++)val[dfn[i]]={d[i],i};
		t1.build(1,1,n);
		for(int i=1;i<=n;i++)val[dfn[i]]=calc(i);
		t2.build(1,1,n);
	}
	void mdf(int u,int w){
		d[u]=w;
		t1.modif(1,1,n,dfn[u],{d[u],u});
		t2.modif(1,1,n,dfn[u],calc(u));
		while(u){
			u=tp[u];
			if(fa[u])t2.modif(1,1,n,dfn[fa[u]],calc(fa[u]));
			u=fa[u];
		}
	}
	pair<pii,pii> get(int u){
		pii mn={inf,0},se={inf,0};
		pii res=t1.query(1,1,n,dfn[u]+1,dfn[u]+siz[u]-1)-dep[u];
		if(res.fi<=n){
			res.se=get(u,res.se);
			if(mn>res)se=mn,mn=res;
			else if(se>res)se=res;
			int p=res.se;
			res=min(t1.query(1,1,n,dfn[u]+1,dfn[p]-1),t1.query(1,1,n,dfn[p]+siz[p],dfn[u]+siz[u]-1))-dep[u];
			res.se=get(u,res.se);
			if(mn>res)se=mn,mn=res;
			else if(se>res)se=res;
		}
		if(fa[u]){
			res={inf,0};
			int uu=u;
			while(u){
				res=min(res,t2.query(1,1,n,dfn[tp[u]],dfn[u]-1)+dep[uu]);
				u=tp[u];
				if(fa[u]){
					res=min(res,min(t1.query(1,1,n,dfn[fa[u]],dfn[u]-1),t1.query(1,1,n,dfn[u]+siz[u],dfn[fa[u]]+siz[fa[u]]-1))-2*dep[fa[u]]+dep[uu]);
				}
				u=fa[u];
			}
			u=uu;
			res.se=fa[u];
			if(mn>res)se=mn,mn=res;
			else if(se>res)se=res;
		}
		// cout<<mn.fi<<" "<<mn.se<<" "<<se.fi<<" "<<se.se<<"\n";
		return {mn,se};
	}
}c1,c2;
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfn[0]=n+1,idx=0;dfs(1),dfs(1,1);
	scanf("%s",s+1);
	c1.init('R');c2.init('G');
	while(q--){
		int o=read();
		if(o==1){
			int u=read();char ch=getchar();
			while(ch<'A'||ch>'Z')ch=getchar();
			if(s[u]=='R')c1.mdf(u,inf);
			if(s[u]=='G')c2.mdf(u,inf);
			s[u]=ch;
			if(s[u]=='R')c1.mdf(u,dep[u]);
			if(s[u]=='G')c2.mdf(u,dep[u]);
		}
		else{
			int u=read();
			auto[p1,p2]=c1.get(u);
			auto[p3,p4]=c2.get(u);
			int ans=(p1.se!=p3.se)?p1.fi+p3.fi:min(p2.fi+p3.fi,p1.fi+p4.fi);
			if(ans>n)ans=-1;
			printf("%d\n",ans);
		}
	}
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