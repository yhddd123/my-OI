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
inline int readc(){
    char ch=getchar();
    while(ch<'A'||ch>'Z')ch=getchar();
    return ch;
}
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,q,h;
int op[maxn],w[maxn];
#define mid ((l+r)>>1)
#define ls (nd<<1)
#define rs (nd<<1|1)
struct node{
    int a,b,c;
    int calc(int h){
        if(h<=a)return 0;
        if(h<=b)return c;
        return h-b+c;
    }
}tree[maxn<<2];
node operator*(node u,node v){
    node res;
    if(u.c<=v.a)return {v.a-u.c+u.b,v.a-u.c+u.b,v.c};
    if(u.c<=v.b)return {u.a,v.b-u.c+u.b,v.c};
    return {u.a,u.b,u.c-v.b+v.c};
}
int pl[maxn<<2],pr[maxn<<2],pos[maxn];
void build(int nd,int l,int r){
    pl[nd]=l,pr[nd]=r;
    if(l==r){
        pos[l]=nd;
        if(op[l]==1)tree[nd]={w[l],w[l],0};
        if(op[l]==2)tree[nd]={w[l]-1,inf,w[l]};
        if(op[l]==3)tree[nd]={0,w[l],w[l]};
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]*tree[rs];
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        if(op[l]==1)tree[nd]={w[l],w[l],0};
        if(op[l]==2)tree[nd]={w[l]-1,inf,w[l]};
        if(op[l]==3)tree[nd]={0,w[l],w[l]};
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    tree[nd]=tree[ls]*tree[rs];
}
int query(int p,int w){
    int nd=pos[p];
    if(tree[nd].calc(w)==0)return p-1;
    w=tree[nd].calc(w);
    while(nd!=1){
        int lst=nd;nd<<=1;
        if(lst==ls){
            if(tree[rs].calc(w)==0){nd=rs;break;}
            w=tree[rs].calc(w);
        }
    }
    if(nd==1)return n+1;
    int l=pl[nd],r=pr[nd];
    while(l!=r){
        if(tree[ls].calc(w)==0)nd=ls,r=mid;
        else w=tree[ls].calc(w),nd=rs,l=mid+1;
    }
    return l;
}
void work(){
    n=read();q=read();h=read();
    for(int i=1;i<=n;i++){
        char ch=readc();
        if(ch=='B')op[i]=1;
        if(ch=='K')op[i]=2;
        if(ch=='C')op[i]=3;
        w[i]=read();
    }
    build(1,1,n);
    while(q--){
        char opt=readc();
        if(opt=='Z'){
            int i=read();
            char ch=readc();
            if(ch=='B')op[i]=1;
            if(ch=='K')op[i]=2;
            if(ch=='C')op[i]=3;
            w[i]=read();
            modif(1,1,n,i);
        }
        else{
            int p=read();
            int res=query(p,h);
            if(res==p-1)res=-1;
            else res--;
            printf("%lld\n",res);
        }
    }
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