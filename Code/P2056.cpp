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

int n,q;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],st[17][maxn],dfn[maxn],idx;
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;st[0][dfn[u]=++idx]=fa;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);
    }
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
    if(u==v)return u;
    u=dfn[u],v=dfn[v];
    if(u>v)swap(u,v);u++;
    int k=__lg(v-u+1);
    return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int dis(int u,int v){
    if(u==-1||v==-1)return -1;
    return dep[u]+dep[v]-2*dep[lca(u,v)];}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
    int u,v,d;
    node(int _u=-1,int _v=-1){u=_u,v=_v,d=dis(u,v);}
    bool operator<(const node&tmp)const{return d<tmp.d;}
}tree[maxn<<2];
node merge(node x,node y){
    return max({x,y,node(x.u,y.u),node(x.v,y.u),node(x.u,y.v),node(x.v,y.v)});
}
void build(int nd,int l,int r){
    if(l==r){tree[nd]=node(l,l);return ;}
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=merge(tree[ls],tree[rs]);
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        if(tree[nd].d==-1)tree[nd]=node(l,l);
        else tree[nd]=node();
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    tree[nd]=merge(tree[ls],tree[rs]);
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1,0);
    for(int j=1;j<=16;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<(j-1))]);
    }
    build(1,1,n);
    q=read();
    while(q--){
        char ch=getchar();while(ch!='C'&&ch!='G')ch=getchar();
        if(ch=='C'){
            int u=read();
            modif(1,1,n,u);
        }
        else{
            // cout<<tree[1].u<<" "<<tree[1].v<<"\n";
            printf("%lld\n",tree[1].d);
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}