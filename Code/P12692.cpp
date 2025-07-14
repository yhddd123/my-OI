#include<bits/stdc++.h>
#include <cstdio>
#include <queue>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=200010;
const int inf=1e9;

int n,k;
int head[maxn],tot;
struct nd{
    int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int st[16][maxn],dfn[maxn],idx,dep[maxn];
void dfs(int u,int fa){
    st[0][dfn[u]=++idx]=fa;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dep[v]=dep[u]+e[i].w;dfs(v,u);
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
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
    int x,y,d;
    node(int u=0,int v=0){x=u,y=v,d=dis(u,v);}
    bool operator<(const node&tmp)const{return d<tmp.d;}
}tree[maxn<<2];
node up(node u,node v){
    return max({u,v,node(u.x,v.x),node(u.x,v.y),node(u.y,v.x),node(u.y,v.y)});
}
void build(int nd,int l,int r){
    if(l==r){tree[nd]=node(l,l);return ;}
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=up(tree[ls],tree[rs]);
}
node query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return up(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
priority_queue<tuple<int,int,int,int,int>> q;
pii calc(int u,node v){return max(mkp(dis(u,v.x),v.x),mkp(dis(u,v.y),v.y));}
void work(){
    n=read();k=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    dfs(1,0);
    for(int j=1;j<16;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    build(1,1,n);
    for(int i=1;i<n;i++){
        auto[w,j]=calc(i,query(1,1,n,i+1,n));
        q.push({w,i,j,i+1,n});
    }
    while(!q.empty()&&k--){
        auto[w,i,j,l,r]=q.top();q.pop();
        printf("%lld\n",w);
        if(l<j){
            auto[ww,jj]=calc(i,query(1,1,n,l,j-1));
            q.push({ww,i,jj,l,j-1});
        }
        if(j<r){
            auto[ww,jj]=calc(i,query(1,1,n,j+1,r));
            q.push({ww,i,jj,j+1,r});
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