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
int n,a[maxn];
vector<int> e[maxn];
int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0,dep[u]=dep[fa[u]]+1;
	for(int v:e[u]){
		fa[v]=u,dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
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
vector<int> id[maxn];
pii operator+(pii u,pii v){return {(u.fi+v.fi)%mod,(u.se+v.se)%mod};}
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,(u.se*v.fi+u.fi*v.se)%mod};}
pii operator*(pii u,int v){return {u.fi*v%mod,u.se*v%mod};}
pii operator/(pii u,pii v){
	int ni=ksm(v.fi);
	int c=u.fi*ni%mod;
	int d=(u.se+mod-u.se*c%mod)*ni%mod;
	return {c,d};
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
		g[u][0]=g[u][0]*(f[v][0]+f[v][1]),g[u][1]=g[u][1]*f[v][0];
	}
	f[u][0]=(f[son[u]][0]+f[son[u]][1])*g[u][0],f[u][1]=f[son[u]][0]*op[u]*g[u][1];
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct mat{
	pii e[2][2];
	mat(pii e00={0,0},pii e01={0,0},pii e10={0,0},pii e11={0,0}){e[0][0]=e00,e[0][1]=e01,e[1][0]=e10,e[1][1]=e11;}
}tree[maxn<<1];
mat operator*(mat u,mat v){
	mat res;
	for(int i=0;i<2;i++){
		for(int k=0;k<2;k++){
			for(int j=0;j<2;j++)res.e[i][j]=res.e[i][j]+u.e[i][k]*v.e[k][j];
		}
	}
	return res;
}
int lc[maxn<<1],rc[maxn<<1],rt[maxn],idx;
void build(int &nd,int l,int r){
	if(!nd)nd=++idx;
    if(l==r){
        int u=rnk[l];
        tree[nd]={g[u][0],g[u][0],op[u]*g[u][1],{0,0}};
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]*tree[rs];
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        int u=rnk[l];
        tree[nd]={g[u][0],g[u][0],op[u]*g[u][1],{0,0}};
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    tree[nd]=tree[ls]*tree[rs];
}
mat query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return query(ls,l,mid,ql,qr)*query(rs,mid+1,r,ql,qr);
}
void que(int u){
    mat res=tree[rt[u]];
    f[u][0]=res.e[0][0],f[u][1]=res.e[1][0];
}
void upd(int u){
	modif(rt[tp[u]],dfn[tp[u]],dfn[dw[u]],dfn[u]);
}
void work(){
	n=read();
	for(int i=2;i<=n;i++)fa[i]=read(),e[fa[i]].pb(i);
	for(int i=1;i<=n;i++){
		int v=read();
		id[v].pb(i);
	}
	dfs(1),dfs(1,1);
	for(int i=1;i<=n;i++)a[i]=read();
	dfs1(1);
	for(int u=1;u<=n;u++)if(u==tp[u])build(rt[u],dfn[u],dfn[dw[u]]);
	for(int i=1,lst=0;i<=n;i++){
		for(int u:id[i]){
			op[u]={1,a[u]};
			upd(u);
			u=tp[u];
			while(fa[u]){
				g[fa[u]][0]=g[fa[u]][0]/(f[u][0]+f[u][1]),g[fa[u]][1]=g[fa[u]][1]/f[u][0];
				que(u);
				g[fa[u]][0]=g[fa[u]][0]*(f[u][0]+f[u][1]),g[fa[u]][1]=g[fa[u]][1]*f[u][0];
				upd(fa[u]);
				u=tp[fa[u]];
			}
		}
		que(1);
		int val=f[1][0].se+f[1][1].se;
		printf("%lld\n",val-lst);
		lst=val;
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