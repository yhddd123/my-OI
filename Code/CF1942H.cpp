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

int n,q;
int a[maxn],b[maxn],c[maxn];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1;siz[u]=1;son[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        dfs(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],tim,tp[maxn],dw[maxn];
int f[maxn][2],sf1[maxn],sf2[maxn],sf3[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++tim]=u;tp[u]=lst;dw[u]=u;
    if(!son[u])return ;
    dfs(son[u],lst);dw[u]=dw[son[u]];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==son[u])continue;
        dfs(v,v);
    }
}
void dfs1(int u){
    f[u][0]=f[u][1]=0;
    sf1[u]=sf2[u]=sf3[u]=0;
    if(son[u])dfs1(son[u]);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==son[u])continue;
        dfs1(v);
        sf1[u]+=min(0ll,f[v][0]),sf2[u]+=f[v][0],sf3[u]+=f[v][1];
    }
    sf1[u]+=a[u],sf2[u]+=a[u]-b[u],sf3[u]+=a[u]-b[u]-c[u];
    f[u][0]=min({sf1[u]+min(0ll,f[son[u]][0]),sf2[u]+f[son[u]][0],sf3[u]+f[son[u]][1]}),f[u][1]=sf3[u]+f[son[u]][1];
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct mat{
    int a00,a01,a02,a11,a22;
}tree[maxn<<2];
int lc[maxn<<2],rc[maxn<<2];
int rt[maxn],idx;
mat operator*(const mat &u,const mat &v){
    mat res;
    res.a00 = u.a00 + v.a00;
    res.a01 = min({u.a00 + v.a01, u.a01 + v.a11});
    res.a02 = min({u.a00 + v.a02, u.a02 + v.a22});
    res.a11 = u.a11 + v.a11;
    res.a22 = u.a22 + v.a22;
    return res;
}
void build(int &nd,int l,int r){
	if(!nd)nd=++idx;
    if(l==r){
        int u=rnk[l];
        tree[nd]={min(sf1[u],sf2[u]),sf3[u],sf1[u],sf3[u],0};
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]*tree[rs];
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        int u=rnk[l];
        tree[nd]={min(sf1[u],sf2[u]),sf3[u],sf1[u],sf3[u],0};
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
    f[u][0]=min({res.a00,res.a01,res.a02}),f[u][1]=res.a11;
}
void upd(int u){
	modif(rt[tp[u]],dfn[tp[u]],dfn[dw[u]],dfn[u]);
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)head[i]=0;tot=0;
    for(int i=2;i<=n;i++)add(fa[i]=read(),i);
    for(int i=1;i<=n;i++)b[i]=read(),a[i]=c[i]=0;
    tim=0;dfs(1),dfs(1,1);dfs1(1);
    while(idx)lc[idx]=rc[idx]=0,idx--;
    for(int i=1;i<=n;i++)rt[i]=0;
    for(int u=1;u<=n;u++)if(tp[u]==u)build(rt[u],dfn[u],dfn[dw[u]]);
    // for(int u=1;u<=n;u++){
    	// cout<<f[u][0]<<" "<<f[u][1]<<"\n";
    	// que(u);
    	// cout<<f[u][0]<<" "<<f[u][1]<<"\n";
    // }
    while(q--){
        int op=read(),u=read(),v=read();
        sf1[u]-=a[u],sf2[u]-=a[u]-b[u],sf3[u]-=a[u]-b[u]-c[u];
        if(op==1)a[u]+=v;
        else c[u]+=v;
        sf1[u]+=a[u],sf2[u]+=a[u]-b[u],sf3[u]+=a[u]-b[u]-c[u];
        upd(u);
        u=tp[u];
        while(fa[u]){
            sf1[fa[u]]-=min(0ll,f[u][0]),sf2[fa[u]]-=f[u][0],sf3[fa[u]]-=f[u][1];
            que(u);
            sf1[fa[u]]+=min(0ll,f[u][0]),sf2[fa[u]]+=f[u][0],sf3[fa[u]]+=f[u][1];
            upd(fa[u]);
            u=tp[fa[u]];
        }
        que(1);
    	// dfs1(1);
        puts(min(f[1][0],f[1][1])>=0?"YES":"NO");
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