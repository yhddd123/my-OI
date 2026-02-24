// #pragma GCC optimize("Ofast,unroll-loops")
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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=300010;
const int inf=1e9;
bool mbe;

pii tmpp;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
struct Opt{
	int *x,*y,v;
	Opt(){}
	Opt(int *_x,int *_y,int _v){x=_x,y=_y,v=_v;}
};
Opt st[maxn];int top;
bool flag;
inline void add(int &x,int &y,int v=1){if(flag)st[++top].x=&x,st[top].y=&y,st[top].v=v;}
inline void cov(int &x,int &y,int v=1){if(flag)st[++top].x=&x,st[top].y=&y,st[top].v=-v;}
// inline void clr(int &x){if(flag)st[++top].x=&x,st[top].y=&x,st[top].v=-1;}
inline void addp(pii &u,pii &v){inc(u.fi,v.fi),add(u.se,v.se);}
inline void covp(pii &u,pii &v){u.fi=v.fi,cov(u.se,v.se);}
// inline void clrp(pii &u){u.fi=0,clr(u.se);}
inline void mulpa(pii &res,pii &u,pii &v){
	add(res.se,u.se,v.fi),add(res.se,v.se,u.fi);
}
inline void mulpc(pii &res,pii &u,pii &v){
	cov(res.se,u.se,v.fi),add(res.se,v.se,u.fi);
}

inline pii operator+(pii u,pii v){return {(u.fi+v.fi)%mod,(u.se+v.se)%mod};}
inline pii operator*(pii u,pii v){return {1ll*u.fi*v.fi%mod,(1ll*u.se*v.fi+1ll*u.fi*v.se)%mod};}

int n,a[maxn],id[maxn];
vector<int> e[maxn];
int pp[maxn];
int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0,dep[u]=dep[fa[u]]+1;
	for(int v:e[u]){
		fa[v]=u,dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	for(int i=0;i<e[u].size();i++)if(e[u][i]==son[u])swap(e[u][0],e[u][i]);
	for(int i=0;i<e[u].size();i++)pp[e[u][i]]=i;
}
int dfn[maxn],rnk[maxn],tim,tp[maxn],dw[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++tim]=u,tp[u]=lst;dw[u]=u;
	if(!son[u])return ;
	dfs(son[u],lst);dw[u]=dw[son[u]];
	for(int v:e[u])if(v!=son[u]){
		dfs(v,v);
	}
}
pii f[maxn][2];
pii g[maxn][2];
pii op[maxn];
void dfs1(int u){
	f[u][0]={1,0},f[u][1]=op[u];
	g[u][0]=g[u][1]={1,0};
	if(!son[u])return ;
	dfs1(son[u]);
	for(int v:e[u])if(v!=son[u]){
		dfs1(v);
		g[u][0]=g[u][0]*(f[v][0]+f[v][1]),g[u][1]=f[v][0];
	}
	f[u][0]=(f[son[u]][0]+f[son[u]][1])*g[u][0],f[u][1]=f[son[u]][0]*op[u]*g[u][1];
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct sgt1{
	pii t1[maxn<<1],t2[maxn<<1];
	int lc[maxn<<1],rc[maxn<<1],rt[maxn],idx;
	void build(int &nd,int l,int r){
		if(!nd)nd=++idx;
		t1[nd]=t2[nd]={1,0};
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void modif(int nd,int l,int r,int p,pii &w1,pii &w2){
		if(l==r){covp(t1[nd],w1),covp(t2[nd],w2);return ;}
		if(p<=mid)modif(ls,l,mid,p,w1,w2);
		else modif(rs,mid+1,r,p,w1,w2);
		t1[nd].fi=1ll*t1[ls].fi*t1[rs].fi%mod;t2[nd].fi=1ll*t2[ls].fi*t2[rs].fi%mod;
		mulpc(t1[nd],t1[ls],t1[rs]);mulpc(t2[nd],t2[ls],t2[rs]);
	}
}t;
struct mat{
	pii e00,e01,e10,e11;
};
inline void mulmat(mat &res,mat &u,mat &v){
	res.e00.fi=(1ll*u.e00.fi*v.e00.fi+1ll*u.e01.fi*v.e10.fi)%mod;
	res.e01.fi=(1ll*u.e00.fi*v.e01.fi+1ll*u.e01.fi*v.e11.fi)%mod;
	res.e10.fi=(1ll*u.e10.fi*v.e00.fi+1ll*u.e11.fi*v.e10.fi)%mod;
	res.e11.fi=(1ll*u.e10.fi*v.e01.fi+1ll*u.e11.fi*v.e11.fi)%mod;
	if(!flag)return ;
	mulpc(res.e00,u.e00,v.e00),mulpa(res.e00,u.e01,v.e10);
	mulpc(res.e01,u.e00,v.e01),mulpa(res.e01,u.e01,v.e11);
	mulpc(res.e10,u.e10,v.e00),mulpa(res.e10,u.e11,v.e10);
	mulpc(res.e11,u.e10,v.e01),mulpa(res.e11,u.e11,v.e11);
}
mat tree[maxn<<1];
int lc[maxn<<1],rc[maxn<<1],rt[maxn],idx;
void build(int &nd,int l,int r){
	if(!nd)nd=++idx;
    if(l==r){
        int u=rnk[l];
        tree[nd]={g[u][0],g[u][0],op[u]*g[u][1],{0,0}};
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    mulmat(tree[nd],tree[ls],tree[rs]);
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        int u=rnk[l];
        covp(tree[nd].e00,t.t1[t.rt[u]]);
        covp(tree[nd].e01,t.t1[t.rt[u]]);
        tree[nd].e10.fi=1ll*op[u].fi*t.t2[t.rt[u]].fi%mod;
        mulpc(tree[nd].e10,op[u],t.t2[t.rt[u]]);
        // clrp(tree[nd].e11);
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    mulmat(tree[nd],tree[ls],tree[rs]);
}
void upd(int u){
	modif(rt[tp[u]],dfn[tp[u]],dfn[dw[u]],dfn[u]);
}
int w[maxn],ans[maxn],lst,val;
// int Cnt;
void calc(){
	// Cnt+=top;
	// cerr<<top<<"\n";
	for(int i=top;i;i--){
		if(st[i].v==-1)inc(*st[i].y,*st[i].x),(*st[i].x)=0;
		else if(st[i].v<0)inc(*st[i].y,1ll*(*st[i].x)*(mod-st[i].v)%mod),(*st[i].x)=0;
		else inc(*st[i].y,1ll*(*st[i].x)*st[i].v%mod);
	}
}
void work(){
	n=read();
	for(int i=2;i<=n;i++)fa[i]=read(),e[fa[i]].pb(i);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	dfs(1),dfs(1,1);
	dfs1(1);
	for(int u=1;u<=n;u++){
		if(e[u].size()>1){
			t.build(t.rt[u],1,e[u].size()-1);
			for(int i=1;i<e[u].size();i++){
				int v=e[u][i];
				covp(tmpp,f[v][0]),addp(tmpp,f[v][1]);
				t.modif(t.rt[u],1,e[u].size()-1,i,tmpp,f[v][0]);
			}
		}
		else t.build(t.rt[u],1,1);
	}
	for(int u=1;u<=n;u++)if(u==tp[u])build(rt[u],dfn[u],dfn[dw[u]]);
	auto mdf=[&](int u,int ww){
		op[u].fi=ww;cov(op[u].se,w[u]);
		upd(u);
		int uu=u;
		u=tp[u];
		while(fa[u]){
			covp(tmpp,tree[rt[u]].e00),addp(tmpp,tree[rt[u]].e10);
			t.modif(t.rt[fa[u]],1,e[fa[u]].size()-1,pp[u],tmpp,tree[rt[u]].e00);
			upd(fa[u]);
			u=tp[fa[u]];
		}
		cov(val,tree[rt[1]].e00.se),add(val,tree[rt[u]].e10.se);
		cov(ans[uu],val),add(ans[uu],lst,mod-1);
		cov(lst,val);
	};
	for(int ii=1;ii<=n;ii++){
		int u=id[ii];
		mdf(u,1);
	}
	for(int i=1;i<=n;i++)ans[i]=a[i];
	for(int ii=n;ii;ii--){
		int u=id[ii];
		mdf(u,0);
		flag=1;
		mdf(u,1);
		calc();top=0;
		flag=0;
		mdf(u,0);
		// cout<<tree[rt[1]].e00.fi<<" "<<tree[rt[1]].e00.se<<" "<<tree[rt[1]].e10.fi<<" "<<tree[rt[1]].e10.se<<"\n";
	}
	// cerr<<Cnt<<"\n";
	for(int i=1;i<=n;i++)write(w[i]),putchar(' ');puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}