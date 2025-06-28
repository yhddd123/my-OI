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
const int maxn=200010;

int n,ans;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int st[18][maxn],dfn[maxn],idx;
int to[maxn][18],dep[maxn];
void dfs(int u,int fa){
    st[0][dfn[u]=++idx]=fa;
    dep[u]=dep[fa]+1;to[u][0]=fa;
    for(int i=1;i<18;i++)to[u][i]=to[to[u][i-1]][i-1];
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
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
int kth(int u,int k){
    for(int i=17;i>=0;i--)if(k&(1<<i))u=to[u][i];
    return u;
}
int mov(int u,int v,int k){
    int tp=lca(u,v);
    if(dep[u]-dep[tp]>=k)return kth(u,k);
    return kth(v,dep[u]+dep[v]-2*dep[tp]-k);
}
bool in(pii u,pii v){
    return u.se+dis(u.fi,v.fi)<=v.se;
}
pii merge(pii u,pii v){
    int d=dis(u.fi,v.fi);
    if(u.se>=d+v.se)return u;
    if(v.se>=d+u.se)return v;
    int p=mov(u.fi,v.fi,(d-u.se+v.se)/2);
    return {p,(u.se+v.se+d)/2};
}
int siz[maxn],w[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
    siz[u]=1,w[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa||vis[v])continue;
        getrt(v,u);siz[u]+=siz[v],w[u]=max(w[u],siz[v]);
    }
    w[u]=max(w[u],sum-siz[u]);
    if(w[u]<=sum/2)rt=u;
}
int fa[maxn];
void sovle(int u){
    vis[u]=1;getrt(u,0);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(vis[v])continue;
        sum=siz[v];getrt(v,u);
        fa[rt]=u;sovle(rt);
    }
}
int sf[maxn],nf[maxn],sg[maxn],ng[maxn];
pii a[maxn];
int pre[maxn];
vector<pii> que[maxn];
void sovle(int l,int r){
    if(l==r)return;
    int mid=(l+r)>>1;
    sovle(l,mid);sovle(mid+1,r);
    a[mid]={mid,0},a[mid+1]={mid+1,0};
    for(int i=mid-1;i>=l;i--)a[i]=merge({i,0},a[i+1]);
    for(int i=mid+2;i<=r;i++)a[i]=merge({i,0},a[i-1]);
    // cout<<l<<" "<<r<<" s"<<endl;
    pre[mid]=0;for(int i=mid+1;i<=r;i++)pre[i]=pre[i-1]+a[i].se;
    for(int i=mid;i<=r;i++)que[i].clear();
    auto upd=[&](int x,int op){
        int u=x;
        while(u){
            nf[u]+=op,sf[u]+=op*dis(u,x);
            if(fa[u])ng[u]+=op,sg[u]+=op*dis(fa[u],x);
            u=fa[u];
        }
    };
    auto calc=[&](int x){
        int res=0,u=x;
        while(u){
            res+=nf[u]*dis(u,x)+sf[u];
            if(fa[u])res-=ng[u]*dis(fa[u],x)+sg[u];
            u=fa[u];
        }
        return res;
    };
    for(int i=mid,p1=mid,p2=mid;i>=l;i--){
        while(p1+1<=r&&in(a[p1+1],a[i]))p1++,upd(a[p1].fi,-1);
        while(p2+1<=r&&!in(a[i],a[p2+1]))p2++,upd(a[p2].fi,1);
        while(p2<p1)p2++,upd(a[p2].fi,1);
        ans+=2*a[i].se*(p1-mid);
        ans+=2*(pre[r]-pre[p2]);
        if(p1<p2){
            ans+=(p2-p1)*a[i].se+pre[p2]-pre[p1]+calc(a[i].fi);
        }
        if(i==l){
            while(p1+1<=p2)p1++,upd(a[p1].fi,-1);
        }
    }
    // cout<<ans<<endl;
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,n+i),add(n+i,u);
        add(v,n+i),add(n+i,v);
    }
    dfs(1,0);
    for(int j=1;j<18;j++){
        for(int i=1;i+(1<<j)-1<=2*n-1;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<(j-1))]);
    }
    sum=n;getrt(1,0);sovle(rt);
    sovle(1,n);
    printf("%lld\n",ans/2);
}

int T;
signed main(){
    // freopen("CF1458F.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}