#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct mat{
    int a01,a02,a11,a12;
}I={0,0,1,0},H={1,0,1,0},tag[maxn<<2];
inline mat operator*(mat &u,mat &v){
    mat res;
    res.a01 = v.a01 + u.a01 * v.a11;
    res.a02 = v.a02 + u.a01 * v.a12 + u.a02;
    res.a11 = u.a11 * v.a11;
    res.a12 = u.a11 * v.a12 + u.a12;
    return res;
}
struct vec{
    int a00,a10,a20;
}tree[maxn<<2];
inline vec operator*(mat &u,vec &v){
    vec res;
    res.a00 = v.a00 + u.a01 * v.a10 + u.a02 * v.a20;
    res.a10 = u.a11 * v.a10 + u.a12 * v.a20;
    res.a20 = v.a20;
    return res;
}
inline vec operator*(vec &u,vec &v){
    return {u.a00+v.a00,u.a10+v.a10,u.a20+v.a20};
}
void build(int nd,int l,int r){
    tree[nd]={0,0,r-l+1};tag[nd]=I;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]*tree[rs];
}
void upd(int nd,mat &w){
    tree[nd]=w*tree[nd];tag[nd]=w*tag[nd];
}
void down(int nd){
    upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=I;
}
int ql,qr;mat w;
void updata(int nd,int l,int r){
    if(l>=ql&&r<=qr)return upd(nd,w);
    down(nd);
    if(ql<=mid)updata(ls,l,mid);
    if(qr>mid)updata(rs,mid+1,r);
    tree[nd]=tree[ls]*tree[rs];
}
int query(int nd,int l,int r){
    if(l>=ql&&r<=qr)return tree[nd].a00;
    down(nd);
    if(qr<=mid)return query(ls,l,mid);
    if(ql>mid)return query(rs,mid+1,r);
    return query(ls,l,mid)+query(rs,mid+1,r);
}
set<int> s;
int lst[maxn];
vector<tuple<int,int,int,int>> que[maxn];
int ans[maxn];
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    s.insert(0);
    for(int i=1;i<=q;i++){
        int l=read(),r=read(),x=read(),y=read();
        que[x-1].pb({l,r,i,-1}),que[y].pb({l,r,i,1});
    }
    build(1,1,n);
    for(int i=1;i<=n;i++){
        int p=*--s.end();s.insert(i);
        ql=p+1,qr=i,w={0,0,0,i};
        updata(1,1,n);
        if(lst[a[i]]){
            int p=*--s.lower_bound(lst[a[i]]);
            int q=*s.upper_bound(lst[a[i]]);
            ql=p+1,qr=lst[a[i]],w={0,0,0,q};
            updata(1,1,n);
            s.erase(lst[a[i]]);
        }
        lst[a[i]]=i;
        upd(1,H);
        for(auto[l,r,id,op]:que[i]){
            ql=l,qr=r;
            ans[id]+=op*query(1,1,n);
        }
    }
    for(int i=1;i<=q;i++)write(ans[i]),puts("");
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}