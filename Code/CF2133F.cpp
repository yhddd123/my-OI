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
const int maxn=500010;
const int inf=1e9;

int n,a[maxn];
vector<int> pos[maxn];
#define all1 1,0,n
#define all2 1,1,n+1
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct sgt1{
    pii mn[maxn<<2];
    void build(int nd,int l,int r){
        mn[nd]={inf,0};
        if(l==r)return ;
        build(ls,l,mid),build(rs,mid+1,r);
    }
    void updata(int nd,int l,int r,int p,pii w){
        mn[nd]=min(mn[nd],w);
        if(l==r)return ;
        if(p<=mid)updata(ls,l,mid,p,w);
        else updata(rs,mid+1,r,p,w);
    }
    pii query(int nd,int l,int r,int ql,int qr){
        if(l>=ql&&r<=qr)return mn[nd];
        if(qr<=mid)return query(ls,l,mid,ql,qr);
        if(ql>mid)return query(rs,mid+1,r,ql,qr);
        return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
    }
}t1;
struct sgt2{
    pii mn[maxn<<2];
    void build(int nd,int l,int r){
        mn[nd]={inf,0};
        if(l==r)return ;
        build(ls,l,mid),build(rs,mid+1,r);
    }
    void updata(int nd,int l,int r,int ql,int qr,pii w){
        if(l>=ql&&r<=qr){mn[nd]=min(mn[nd],w);return ;}
        if(ql<=mid)updata(ls,l,mid,ql,qr,w);
        if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    }
    pii query(int nd,int l,int r,int p){
        if(l==r)return mn[nd];
        if(p<=mid)return min(mn[nd],query(ls,l,mid,p));
        else return min(mn[nd],query(rs,mid+1,r,p));
    }
}t2;
pii f[maxn];
int pre[maxn];
int st[maxn],tp;
int d[maxn];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;d[v]++;}
queue<int> q;
int ans[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)pos[i].clear();
    for(int i=1;i<=n;i++)if(a[i])pos[min(n,i+a[i]-1)].pb(i);
    t1.build(all1),t2.build(all2);
    f[0]={0,0};t1.updata(all1,0,f[0]),t2.updata(all2,1,1,f[0]);
    for(int i=1;i<=n;i++){
        f[i]={inf,0};
        for(int p:pos[i]){
            int j=max(1,p-a[p]+1);
            pii dp={inf,0};
            dp=min(dp,t1.query(all1,j-1,p-1));
            dp=min(dp,t2.query(all2,j));
            dp.fi++;
            // cout<<i<<" "<<j<<" "<<p<<" "<<dp.fi<<" "<<dp.se<<"\n";
            pre[p]=dp.se;
            f[i]=min(f[i],{dp.fi,p});
            t1.updata(all1,i,{dp.fi,p}),t2.updata(all2,p+1,i+1,{dp.fi,p});
        }
    }
    if(f[n].fi==inf){puts("-1");return ;}
    tp=0;for(int p=f[n].se;p;p=pre[p])st[++tp]=p;
    reverse(st+1,st+tp+1);
    for(int i=1;i<=tp;i++)head[i]=d[i]=0;tot=0;
    // for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
    for(int i=1;i<tp;i++){
        if(st[i]>=st[i+1]-a[st[i+1]]+1)add(i,i+1);
        else add(i+1,i);
    }
    for(int i=1;i<=tp;i++)if(!d[i])q.push(i);
    tp=0;while(!q.empty()){
        int u=q.front();q.pop();ans[++tp]=st[u];
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            --d[v];
            if(!d[v])q.push(v);
        }
    }
    printf("%d\n",tp);
    for(int i=1;i<=tp;i++)printf("%d ",ans[i]);puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=read();
    while(T--)work();
}