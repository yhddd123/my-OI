#include<bits/stdc++.h>
#include <cstdio>
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
const int maxn=250010;
const int inf=1e9;

int n,q,a[maxn];
int pl[maxn],pr[maxn],ans[maxn];
int mxl[18][maxn],mxr[18][maxn];
int mmaxl(int u,int v){return a[u]>=a[v]?u:v;}
int mmaxr(int u,int v){return a[v]>=a[u]?v:u;}
int quel(int l,int r){
    int k=__lg(r-l+1);
    return mmaxl(mxl[k][l],mxl[k][r-(1<<k)+1]);
}
int quer(int l,int r){
    int k=__lg(r-l+1);
    return mmaxr(mxr[k][l],mxr[k][r-(1<<k)+1]);
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2],tag[maxn<<2];
void upd(int nd,int w){tree[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    tree[nd]=min(tree[ls],tree[rs]);
}
void modif(int nd,int l,int r,int p,int w){
    if(l==r){tree[nd]=w;return ;}
    if(tag[nd])down(nd);
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    tree[nd]=min(tree[ls],tree[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
    if(ql>qr)return inf;
    if(l>=ql&&r<=qr)return tree[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int st[maxn],tp;
vector<int> que[maxn];
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)mxl[0][i]=mxr[0][i]=i;
    for(int j=1;j<18;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            mxl[j][i]=mmaxl(mxl[j-1][i],mxl[j-1][i+(1<<j-1)]);
            mxr[j][i]=mmaxr(mxr[j-1][i],mxr[j-1][i+(1<<j-1)]);
        }
    }
    for(int i=1;i<=q;i++){
        pl[i]=read(),pr[i]=read();
        ans[i]=a[quel(pl[i]+1,pr[i]-1)]+a[pl[i]]+a[pr[i]];
    }
    for(int i=1;i<=q;i++)que[pr[i]].pb(i);
    for(int i=1;i<=n;i++){
        while(tp&&a[i]>a[st[tp]]){
            updata(1,0,n,st[tp-1],st[tp]-1,-a[st[tp]]);
            tp--;
        }
        st[++tp]=i;
        modif(1,0,n,i-1,a[i-1]);
        updata(1,0,n,st[tp-1],st[tp]-1,a[i]);
        for(int j:que[i]){
            int p=quel(pl[j],i);
            ans[j]=min(ans[j],a[p]+query(1,0,n,p+1,i-1));
        }
    }
    for(int i=1;i<=n;i++)que[i].clear();
    for(int i=1;i<=q;i++)que[pl[i]].pb(i);
    st[tp=0]=n+1;for(int i=n;i;i--){
        while(tp&&a[i]>a[st[tp]]){
            updata(1,1,n+1,st[tp]+1,st[tp-1],-a[st[tp]]);
            tp--;
        }
        st[++tp]=i;
        modif(1,1,n+1,i+1,a[i+1]);
        updata(1,1,n+1,st[tp]+1,st[tp-1],a[i]);
        for(int j:que[i]){
            int p=quer(i,pr[j]);
            ans[j]=min(ans[j],a[p]+query(1,1,n+1,i+1,p-1));
        }
    }
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}