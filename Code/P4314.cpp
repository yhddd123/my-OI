#include<bits/stdc++.h>
#include <cstdio>
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
const int maxn=100010;
const int inf=1e9;

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],mn[maxn<<2],hmx[maxn<<2],tag[maxn<<2],htag[maxn<<2];
void up(int nd){
    mx[nd]=max(mx[ls],mx[rs]),mn[nd]=min(mn[ls],mn[rs]);
    hmx[nd]=max(hmx[nd],mx[nd]);
}
void build(int nd,int l,int r){
    if(l==r){mn[nd]=mx[nd]=hmx[nd]=a[l];return ;}
    build(ls,l,mid),build(rs,mid+1,r);
    up(nd);
}
void upd(int nd,int w,int hw){
    htag[nd]=max(htag[nd],tag[nd]+hw);
    hmx[nd]=max(hmx[nd],mx[nd]+hw);
    mx[nd]+=w,mn[nd]+=w,tag[nd]+=w;
}
void down(int nd){
    upd(ls,tag[nd],htag[nd]),upd(rs,tag[nd],htag[nd]),tag[nd]=htag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return upd(nd,w,w);
    down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    up(nd);
}
void cover(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr&&mn[nd]==mx[nd])return upd(nd,w-mx[nd],w-mx[nd]);
    down(nd);
    if(ql<=mid)cover(ls,l,mid,ql,qr,w);
    if(qr>mid)cover(rs,mid+1,r,ql,qr,w);
    up(nd);
}
int quemx(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mx[nd];
    down(nd);
    if(qr<=mid)return quemx(ls,l,mid,ql,qr);
    if(ql>mid)return quemx(rs,mid+1,r,ql,qr);
    return max(quemx(ls,l,mid,ql,qr),quemx(rs,mid+1,r,ql,qr));
}
int quehis(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return hmx[nd];
    down(nd);
    if(qr<=mid)return quehis(ls,l,mid,ql,qr);
    if(ql>mid)return quehis(rs,mid+1,r,ql,qr);
    return max(quehis(ls,l,mid,ql,qr),quehis(rs,mid+1,r,ql,qr));
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    build(1,1,n);
    q=read();
    while(q--){
        char ch=getchar();while(ch<'A'||ch>'Z')ch=getchar();
        if(ch=='Q'){
            int l=read(),r=read();
            printf("%d\n",quemx(1,1,n,l,r));
        }
        if(ch=='A'){
            int l=read(),r=read();
            printf("%d\n",quehis(1,1,n,l,r));
        }
        if(ch=='P'){
            int l=read(),r=read(),w=read();
            updata(1,1,n,l,r,w);
        }
        if(ch=='C'){
            int l=read(),r=read(),w=read();
            cover(1,1,n,l,r,w);
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