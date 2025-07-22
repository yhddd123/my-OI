#include <algorithm>
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
const int maxm=500010;
const int inf=1e9;

int n,q;
int a[maxn],b[maxn],c[maxn];
int lshx[maxn],lenx,lshy[maxn],leny;
int idx[maxn],idy[maxn];
vector<int> upd[maxn];
void sovle(int l,int r){
    if(l==r)return ;
    int mid=l+r>>1;
    sovle(l,mid),sovle(mid+1,r);
    int p=-1,q=-1;
    for(int i=l;i<=mid;i++)if(idy[i]<=n&&(p==-1||c[idy[i]]>c[p]))p=idy[i];
    for(int i=mid+1;i<=r;i++)if(idy[i]>n&&(q==-1||c[idy[i]]>c[q]))q=idy[i];
    if(p!=-1){
        for(int i=mid+1;i<=r;i++)if(idy[i]>n)upd[idy[i]].pb(p);
    }
    if(q!=-1){
        for(int i=l;i<=mid;i++)if(idy[i]<=n)upd[q].pb(idy[i]);
    }
}
int pl[maxm],pr[maxm],ans[maxm];
vector<int> que[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2];
void build(int nd,int l,int r){
    mx[nd]=-1;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int p,int w){
    mx[nd]=max(mx[nd],w);
    if(l==r)return ;
    if(p<=mid)updata(ls,l,mid,p,w);
    else updata(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr){
    if(ql>qr)return -1;
    if(l>=ql&&r<=qr)return mx[nd];
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
    n=read();
    for(int i=1;i<=2*n;i++)a[i]=read(),b[i]=read(),c[i]=read();
    for(int i=1;i<=2*n;i++)lshx[++lenx]=a[i],lshy[++leny]=b[i];
    sort(lshx+1,lshx+lenx+1),lenx=unique(lshx+1,lshx+lenx+1)-lshx-1;
    sort(lshy+1,lshy+leny+1),leny=unique(lshy+1,lshy+leny+1)-lshy-1;
    for(int i=1;i<=2*n;i++){
        a[i]=lower_bound(lshx+1,lshx+lenx+1,a[i])-lshx;
        b[i]=lower_bound(lshy+1,lshy+leny+1,b[i])-lshy;
        idx[a[i]]=i,idy[b[i]]=i;
    }
    sovle(1,2*n);
    q=read();
    for(int i=1;i<=q;i++)pl[i]=read(),pr[i]=read(),ans[i]=-1;
    for(int i=1;i<=q;i++){
        int p=lower_bound(lshx+1,lshx+lenx+1,pr[i])-lshx;
        que[p].pb(i);
    }
    build(1,1,n);
    for(int i=2*n;i>n;i--){
        for(int j:upd[idx[i]])updata(1,1,n,a[j],c[j]+c[idx[i]]);
        for(int j:que[i]){
            int p=upper_bound(lshx+1,lshx+lenx+1,pl[j])-lshx-1;
            ans[j]=max(ans[j],query(1,1,n,1,p));
        }
    }
    for(int i=n+1;i<=2*n;i++)que[i].clear();
    for(int i=1;i<=q;i++){
        int p=upper_bound(lshx+1,lshx+lenx+1,pr[i])-lshx-1;
        que[p].pb(i);
    }
    build(1,1,n);
    for(int i=n+1;i<=2*n;i++){
        for(int j:upd[idx[i]])updata(1,1,n,a[j],c[j]+c[idx[i]]);
        for(int j:que[i]){
            int p=lower_bound(lshx+1,lshx+lenx+1,pl[j])-lshx;
            ans[j]=max(ans[j],query(1,1,n,p,n));
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