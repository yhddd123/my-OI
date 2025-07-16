#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=200010;
const int inf=1e9;

int n,a[maxn];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1;siz[u]=1,son[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        dfs(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;
    if(!son[u])return ;
    dfs(son[u],lst);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
    }
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int val[maxn<<2],tag[maxn<<2],tree[maxn<<2];
void build(int nd,int l,int r){
    tree[nd]=tag[nd]=0;
    if(l==r){val[nd]=a[rnk[l]]-a[fa[rnk[l]]];return ;}
    build(ls,l,mid),build(rs,mid+1,r);
    val[nd]=val[ls]+val[rs];
}
void upd(int nd,int w){tree[nd]+=val[nd]*w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]);tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    tree[nd]=tree[ls]+tree[rs];
}
int query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void upd(int u){
    while(u){
        updata(1,1,n,dfn[tp[u]],dfn[u],1);
        u=fa[tp[u]];
    }
}
int que(int u){
    int res=0;
    while(u){
        res+=query(1,1,n,dfn[tp[u]],dfn[u]);
        u=fa[tp[u]];
    }
    return res;
}
void work(){
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)head[i]=0;tot=idx=0;
    for(int i=2;i<=n;i++){
        fa[i]=read();
        add(fa[i],i),add(i,fa[i]);
    }
    dfs(1),dfs(1,1);
    build(1,1,n);
    for(int i=2;i<=n;i++){
        upd(i-1);
        printf("%d\n",que(i));
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(~scanf("%d",&n))work();
}