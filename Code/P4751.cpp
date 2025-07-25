#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;

int n,q,a[maxn],ans;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1;siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u;dfs(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],tim,tp[maxn],dw[maxn];
int f[maxn][2],g[maxn][2];
void dfs(int u,int lst){
    rnk[dfn[u]=++tim]=u;tp[u]=lst;dw[u]=u;
    f[u][0]=g[u][0]=0,f[u][1]=g[u][1]=a[u];
    if(!son[u])return ;
    dfs(son[u],lst);dw[u]=dw[son[u]];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
        g[u][0]+=max(f[v][0],f[v][1]),g[u][1]+=f[v][0];
    }
    f[u][0]=max(f[son[u]][0],f[son[u]][1])+g[u][0],f[u][1]=f[son[u]][0]+g[u][1];
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct mat{
    int a00,a01,a10,a11;
}tree[maxn<<2];
int lc[maxn<<2],rc[maxn<<2];
int rt[maxn],idx;
mat operator*(mat u,mat v){
    mat res;
    res.a00=max(u.a00+v.a00,u.a01+v.a10);
    res.a01=max(u.a00+v.a01,u.a01+v.a11);
    res.a10=max(u.a10+v.a00,u.a11+v.a10);
    res.a11=max(u.a10+v.a01,u.a11+v.a11);
    return res;
}
void build(int &nd,int l,int r){
	if(!nd)nd=++idx;
    if(l==r){
        int u=rnk[l];
        tree[nd]={g[u][0],g[u][0],g[u][1],-inf};
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]*tree[rs];
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        int u=rnk[l];
        tree[nd]={g[u][0],g[u][0],g[u][1],-inf};
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
    f[u][0]=res.a00,f[u][1]=res.a10;
}
void upd(int u){
	modif(rt[tp[u]],dfn[tp[u]],dfn[dw[u]],dfn[u]);
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1),dfs(1,1);
    for(int u=1;u<=n;u++)if(tp[u]==u)build(rt[u],dfn[u],dfn[dw[u]]);
    while(q--){
        int u=read()^ans,v=read();
        // cout<<u<<" "<<v<<" "<<ans<<endl;
        g[u][1]-=a[u],a[u]=v,g[u][1]+=a[u];
        upd(u);
        u=tp[u];
        while(fa[u]){
            g[fa[u]][0]-=max(f[u][0],f[u][1]),g[fa[u]][1]-=f[u][0];
            que(u);
            g[fa[u]][0]+=max(f[u][0],f[u][1]),g[fa[u]][1]+=f[u][0];
            upd(fa[u]);
            u=tp[fa[u]];
        }
        que(1);
        write(ans=max(f[1][0],f[1][1]));puts("");
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}