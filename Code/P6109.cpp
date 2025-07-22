#include<bits/stdc++.h>
#include <cstdio>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxd=16;
const int maxn=50010;
const int maxm=500010;
const int inf=1e9;

int n,m,q;
vector<tuple<int,int,int,int,int>> upd[maxn<<2],que[maxn<<2];
ll ans[maxm];
int dep;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
ll mx[maxn<<2],hmx[maxn<<2],tag[maxn<<2],htag[maxn<<2];
ll _mx[maxd][maxn<<2],_hmx[maxd][maxn<<2],_tag[maxd][maxn<<2],_htag[maxd][maxn<<2];
bool vis[maxd][maxn<<2];
void up(int nd){
    mx[nd]=max(mx[ls],mx[rs]);
    hmx[nd]=max(hmx[nd],mx[nd]);
}
void updt(int nd,ll w,ll hw){
    htag[nd]=max(htag[nd],tag[nd]+hw);
    hmx[nd]=max(hmx[nd],mx[nd]+hw);
    mx[nd]+=w,tag[nd]+=w;
}
void down(int nd){
    updt(ls,tag[nd],htag[nd]),updt(rs,tag[nd],htag[nd]),tag[nd]=htag[nd]=0;
}
void init(int nd){
    if(!vis[dep][nd]){
        vis[dep][nd]=1;
        _mx[dep][nd]=mx[nd],_hmx[dep][nd]=hmx[nd],_tag[dep][nd]=tag[nd],_htag[dep][nd]=htag[nd];
    }
}
void updata(int nd,int l,int r,int ql,int qr,int w){
    init(nd);
    if(l>=ql&&r<=qr)return updt(nd,w,w);
    init(ls),init(rs);down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    up(nd);
}
ll quehis(int nd,int l,int r,int ql,int qr){
    init(nd);
    if(l>=ql&&r<=qr)return hmx[nd];
    init(ls),init(rs);down(nd);
    if(qr<=mid)return quehis(ls,l,mid,ql,qr);
    if(ql>mid)return quehis(rs,mid+1,r,ql,qr);
    return max(quehis(ls,l,mid,ql,qr),quehis(rs,mid+1,r,ql,qr));
}
void redo(int nd){
    vis[dep][nd]=0;
    mx[nd]=_mx[dep][nd],hmx[nd]=_hmx[dep][nd],tag[nd]=_tag[dep][nd],htag[nd]=_htag[dep][nd];
}
void clear(int nd,int l,int r){
    if(!vis[dep][nd])return ;
    redo(nd);
    clear(ls,l,mid),clear(rs,mid+1,r);
}
vector<tuple<int,int,int>> add[maxn],ask[maxn];
void sovle(int nd,int l,int r){
    if(l>r||!que[nd].size())return ;
    for(auto[xl,xr,yl,yr,w]:upd[nd]){
        if(xr<mid){
            upd[ls].pb({xl,xr,yl,yr,w});
            add[xr].pb({yl,yr,w});
            if(l<xl)add[xl-1].pb({yl,yr,-w});
        }
        else if(xl>mid){
            upd[rs].pb({xl,xr,yl,yr,w});
            add[xl].pb({yl,yr,w});
            if(xr<r)add[xr+1].pb({yl,yr,-w});
        }
        else{
            add[mid].pb({yl,yr,w});
            if(xr<r)add[xr+1].pb({yl,yr,-w});
            if(l<xl)add[xl-1].pb({yl,yr,-w});
        }
    }
    for(auto[xl,xr,yl,yr,id]:que[nd]){
        if(xr<mid)que[ls].pb({xl,xr,yl,yr,id});
        else if(xl>mid)que[rs].pb({xl,xr,yl,yr,id});
        else ask[xl].pb({yl,yr,id}),ask[xr].pb({yl,yr,id});
    }
    for(int i=mid;i>=l;i--){
        sort(add[i].begin(),add[i].end(),[&](auto u,auto v){return get<2>(u)<get<2>(v);});
        for(auto[pl,pr,w]:add[i])updata(1,1,n,pl,pr,w);
        for(auto[pl,pr,id]:ask[i])ans[id]=max(ans[id],quehis(1,1,n,pl,pr));
    }
    clear(1,1,n);
    for(int i=mid;i<=r;i++){
        sort(add[i].begin(),add[i].end(),[&](auto u,auto v){return get<2>(u)<get<2>(v);});
        for(auto[pl,pr,w]:add[i])updata(1,1,n,pl,pr,w);
        for(auto[pl,pr,id]:ask[i])ans[id]=max(ans[id],quehis(1,1,n,pl,pr));
    }
    clear(1,1,n);
    for(int i=l;i<=r;i++)add[i].clear(),ask[i].clear();
    for(auto[xl,xr,yl,yr,w]:upd[nd]){
        if(xl<mid&&xr>=mid){
            if(xl<=l)updata(1,1,n,yl,yr,w);
            else upd[ls].pb({xl,mid-1,yl,yr,w});
        }
    }
    dep++;sovle(ls,l,mid-1);dep--;clear(1,1,n);
    for(auto[xl,xr,yl,yr,w]:upd[nd]){
        if(xl<=mid&&xr>mid){
            if(xr>=r)updata(1,1,n,yl,yr,w);
            else upd[rs].pb({mid+1,xr,yl,yr,w});
        }
    }
    dep++;sovle(rs,mid+1,r);dep--;clear(1,1,n);
}
void work(){
    n=read();m=read();q=read();
    for(int i=1;i<=m;i++){
        int l1=read(),l2=read(),r1=read(),r2=read(),w=read();
        upd[1].pb({l1,r1,l2,r2,w});
    }
    for(int i=1;i<=q;i++){
        int l1=read(),l2=read(),r1=read(),r2=read();
        que[1].pb({l1,r1,l2,r2,i});
    }
    sovle(1,1,n);
    for(int i=1;i<=q;i++)write(ans[i]),puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}