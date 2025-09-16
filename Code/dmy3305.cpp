#include<bits/stdc++.h>
#include <utility>
#define int unsigned
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,q;
int head[maxn],tot;
struct nd{
    int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
array<int,3> g[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u;dfs(v),siz[u]+=siz[v];
        if(siz[v]>=siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;
    if(!son[u])return ;dfs(son[u],lst);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
    }
}
int lca(int u,int v){
    while(tp[u]!=tp[v]){
        if(dep[tp[u]]<dep[tp[v]])swap(u,v);
        u=fa[tp[u]];
    }
    if(dep[u]<dep[v])swap(u,v);
    return v;
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
    int sv,sd,dv,ddv,len;
    void upd(int w){
        ddv+=2*sv*sd*w+sv*len*w*w;
        dv+=sv*w;sd+=len*w;
    }
}tree[maxn<<2];
node operator+(node u,node v){return {u.sv+v.sv,u.sd+v.sd,u.dv+v.dv,u.ddv+v.dv,u.len+v.len};}
int tag[maxn<<2];
void upd(int nd,int w){tree[nd].upd(w),tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void build(int nd,int l,int r){
    tree[nd].len=r-l+1;
    if(l==r){
        int u=rnk[l];
        tree[nd].sv=siz[u]-siz[son[u]];
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]+tree[rs];
}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    tree[nd]=tree[ls]+tree[rs];
}
node query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void work(){
    n=read();q=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
        g[i]={u,v,w};
    }
    dfs(1),dfs(1,1);
    build(1,1,n);
    for(int i=1;i<n;i++){
        auto[u,v,w]=g[i];
        if(fa[v]==u)swap(g[i][0],g[i][1]),swap(u,v);
        updata(1,1,n,dfn[u],dfn[u]+siz[u]-1,w);
    }
    while(q--){
        int op=read(),u=read(),v=read();
        if(op==1){
            updata(1,1,n,dfn[g[u][0]],dfn[g[u][0]]+siz[g[u][0]],-g[u][2]);
            g[u][2]=v;
            updata(1,1,n,dfn[g[u][0]],dfn[g[u][0]]+siz[g[u][0]],g[u][2]);
        }
        else{
            int u=read(),v=read(),l=lca(u,v),ans=0;
            int du=query(1,1,n,dfn[u],dfn[u]).sd;
            int dv=query(1,1,n,dfn[v],dfn[v]).sd;
            int dl=query(1,1,n,dfn[l],dfn[l]).sd;
            int lst1=0,lst2=0;
            auto sovle=[&](int u,int v,int l,int &lst){
            int p=u;while(tp[p]!=tp[l]){
                if(p!=tp[p]){
                    node res=query(1,1,n,dfn[tp[p]],dfn[fa[p]]);
                    ans+=res.dv*(dv-2*dl);
                    ans+=res.ddv;
                    ans-=res.sv*du*(dv-2*dl);
                    ans-=res.dv*du;
                }
                p=tp[p];
                lst1=p;
                if(l!=fa[p]){
                    int dp=query(1,1,n,dfn[p],dfn[p]).sd;
                    ans+=(siz[fa[p]]-siz[p])*(du-dp)*(dp+dv-2*dl);
                    lst1=fa[p];
                }
                p=fa[p];
            }
            if(p!=l&&fa[p]!=l){
                node res=query(1,1,n,dfn[l]+1,dfn[fa[p]]);
                ans+=res.dv*(dv-2*dl);
                ans+=res.ddv;
                ans-=res.sv*du*(dv-2*dl);
                ans-=res.dv*du;
                lst1=rnk[dfn[l]+1];
            }
            };
            sovle(u,v,l,lst1),sovle(v,u,l,lst2);
            if(u!=l&&v!=l){
                ans+=(n-siz[lst1]-siz[lst2])*(du-dl)*(dv-dl);
            }
            printf("%u\n",ans);
        }
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}