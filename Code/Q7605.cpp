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
const int inf=1e9;
bool mbe;

int n,k,a[maxn];
int s[maxn],f[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2];
void modif(int nd,int l,int r,int p,int w){
    if(l==r){mn[nd]=w;return ;}
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    mn[nd]=min(mn[ls],mn[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
    if(ql>qr)return inf;
    if(l>=ql&&r<=qr)return mn[nd];
    if(qr<=mid)return query(ls,l,mid-1,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return min(query(ls,l,mid-1,ql,qr),query(rs,mid+1,r,ql,qr));
}
int find(int nd,int l,int r,int v){
    if(l==r)return l;
    if(mn[ls]<v)return find(ls,l,mid,v);
    else return find(rs,mid+1,r,v);
}
#undef ls
#undef rs
#define ls lc[nd]
#define rs rc[nd]
struct line{
    int k,b;
    int val(int x){return k*x+b;}
}tree[maxn<<6];
int lc[maxn<<6],rc[maxn<<6],idx;
void updata(int &nd,int l,int r,line w){
    if(l==r){
        if(tree[nd].val(l)<w.val(l))tree[nd]=w;
        return ;
    }
    if(tree[nd].val(mid)<w.val(mid))swap(tree[nd],w);
    if(tree[nd].val(l)<w.val(l))updata(ls,l,mid,w);
    else updata(rs,mid+1,r,w);
}
int query(int nd,int l,int r,int p){
    if(!nd)return 0;
    if(p<=mid)return max(query(ls,l,mid,p),tree[nd].val(p));
    else return max(query(rs,mid+1,r,p),tree[nd].val(p));
}
#undef ls
#undef rs
#define ls nd<<1
#define rs nd<<1|1
struct sgt{
int pl,pr;
int rt[maxn<<2];
void updata(int nd,int l,int r,int p,line w){
    ::updata(rt[nd],pl,pr,w);
    if(l==r)return ;
    if(p<=mid)updata(ls,l,mid,p,w);
    else updata(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr,int x){
    if(l>=ql&&r<=qr)return ::query(rt[nd],pl,pr,x);
    if(qr<=mid)return query(ls,l,mid,ql,qr,x);
    if(ql>mid)return query(rs,mid+1,r,ql,qr,x);
    return max(query(ls,l,mid,ql,qr,x),query(rs,mid+1,r,ql,qr,x));
}
}t1,t2;
void work(){
    n=read();k=read();
    for(int i=1;i<=n;i++)a[i]=read(),s[i]=s[i-1]+a[i];
    t1.pl=0,t1.pr=s[n];t2.pl=0,t2.pr=n;
    for(int i=1;i<=n;i++){
        int pl=query(1,0,n,0,a[i])+1,pr=min(i,query(1,0,n,0,a[i]-1));
        modif(1,0,n,a[i],i);
        t1.updata(1,1,n,i,{-s[i-1],f[i-1]}),t2.updata(1,1,n,i,{0,f[i-1]});
        while(pl<pr){
            int mex=find(1,0,n,pr);
            int to=max(pl,query(1,0,n,0,mex)+1);
            int val=t1.query(1,1,n,to,pr,mex);
            t2.updata(1,1,n,to-1,{mex,val});pr=to-1;
        }
        f[i]=t2.query(1,1,n,max(0ll,i-k)+1,i,s[i]);
        int mex=find(1,0,n,max(0ll,i-k)+1);
        int to=min(query(1,0,n,0,mex),i);
        cout<<mex<<" "<<to<<endl;
        f[i]=max(f[i],s[i]*mex+t1.query(1,1,n,max(0ll,i-k)+1,to,mex));
        cout<<f[i]<<" "<<find(1,0,n,1)<<"\n";
    }
    printf("%lld\n",f[n]);
}

bool med;
int T;
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}