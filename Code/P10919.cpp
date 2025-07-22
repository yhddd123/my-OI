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

int n,m,a[maxn];
int x[maxn],y[maxn],ans[maxn];
int st[18][maxn],rt;
int mmin(int u,int v){return a[u]<a[v]?u:v;}
int que(int l,int r){
    int k=__lg(r-l+1);
    return mmin(st[k][l],st[k][r-(1<<k)+1]);
}
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int build(int l,int r){
    if(l>r)return 0;
    int u=que(l,r);
    int ls=build(l,u-1),rs=build(u+1,r);
    if(ls)add(u,ls),add(ls,u);
    if(rs)add(u,rs),add(rs,u);
    return u;
}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u;dfs(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u,tp[u]=lst;
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
pii mn[maxn<<2];int tag[maxn<<2];
int val[maxn<<2];
void build(int nd,int l,int r){
    mn[nd]={0,-r};val[nd]=inf;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){mn[nd].fi+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    mn[nd]=min(mn[ls],mn[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mn[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void modif(int nd,int l,int r,int p,int w){
    if(l==r){val[nd]=w;return ;}
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    val[nd]=min(val[ls],val[rs]);
}
int queval(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return val[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return queval(ls,l,mid,ql,qr);
    if(ql>mid)return queval(rs,mid+1,r,ql,qr);
    return min(queval(ls,l,mid,ql,qr),queval(rs,mid+1,r,ql,qr));
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=m;i++)x[i]=read();
    for(int i=1;i<=m;i++)y[i]=read();
    for(int i=1;i<=n;i++)st[0][i]=i;
    for(int j=1;j<18;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmin(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    rt=build(1,n);
    dfs(rt),dfs(rt,rt);
    build(1,1,n);
    // for(int i=1;i<=n;i++)cout<<rnk[i]<<" ";cout<<"\n";
    for(int i=1;i<=m;i++){
    	int u=x[i];
    	while(u){
    		updata(1,1,n,dfn[tp[u]],dfn[u],-1);
    		u=fa[tp[u]];
    	}
    }
    for(int i=1;i<=m;i++){
    	int u=y[i];
    	while(u){
    		updata(1,1,n,dfn[tp[u]],dfn[u],1);
    		u=fa[tp[u]];
    	}
    }
    for(int i=1;i<=m;i++)modif(1,1,n,dfn[x[i]],i);
    // cout<<mn[1].fi<<" "<<mn[1].se<<endl;
    for(int i=1;i<=m;i++){
        int u=y[i],v=inf;
        while(u){
            pii res=query(1,1,n,dfn[tp[u]],dfn[u]);
            if(res.fi==0){
                v=min(v,queval(1,1,n,-res.se,dfn[u]));
                break;
            }
            v=min(v,queval(1,1,n,dfn[tp[u]],dfn[u]));
            u=fa[tp[u]];
        }
        // cout<<u<<" "<<v<<endl;
        modif(1,1,n,dfn[x[v]],inf);
        u=y[i];
        while(tp[u]!=tp[x[v]]){
            updata(1,1,n,dfn[tp[u]],dfn[u],-1);
            u=fa[tp[u]];
        }
        updata(1,1,n,dfn[x[v]]+1,dfn[u],-1);
        ans[i]=v;
    }
    for(int i=1;i<=m;i++)printf("%d ",ans[i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}