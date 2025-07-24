#include<bits/stdc++.h>
#define int long long
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
const int maxn=100010;
const int inf=1e9;

int n,q,num,sum;
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
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2],mx[maxn<<2],tag[maxn<<2],pl[maxn<<2],pr[maxn<<2];
void build(int nd,int l,int r){
    pl[nd]=l,pr[nd]=r;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void updt(int nd,int w){tree[nd]+=w*(pr[nd]-pl[nd]+1),mx[nd]+=w,tag[nd]+=w;}
void down(int nd){updt(ls,tag[nd]),updt(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return updt(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    tree[nd]=tree[ls]+tree[rs];
    mx[nd]=max(mx[ls],mx[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int query(int nd,int l,int r){
    if(l==r)return rnk[l];
    if(tag[nd])down(nd);
    if(mx[rs]>=(num+1)/2)return query(rs,mid+1,r);
    else return query(ls,l,mid);
}
void upd(int u,int w){
    while(u){
        updata(1,1,n,dfn[tp[u]],dfn[u],w);
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
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1),dfs(1,1);
    build(1,1,n);
    // for(int i=1;i<=n;i++)cout<<rnk[i]<<" ";cout<<"\n";
    q=read();
    while(q--){
        char ch=getchar();while(ch!='+'&&ch!='-')ch=getchar();
        int u=read(),w=(ch=='+')*2-1;num+=w;sum+=w*dep[u];
        upd(u,w);
        int p=query(1,1,n);
        printf("%lld\n",num*dep[p]+sum-2*que(p));
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}