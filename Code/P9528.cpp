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
const int maxn=500010;
const int inf=2e9;
bool mbe;

int q,k,sum;
int lsh[maxn],len;
tuple<int,int,int> que[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
    int a00,a01,a10,a11;
}tree[maxn<<2];
void build(int nd,int l,int r){
	tree[nd].a00=tree[nd].a01=tree[nd].a10=tree[nd].a11=0;
	if(r-l<=2*k)tree[nd].a10=-inf;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
int tag[maxn<<2],laz[maxn<<2];
node merge(node u,node v){
    node res;
    res.a00=max({u.a00,v.a00,u.a00+v.a10,u.a01+v.a00});
    res.a01=max({u.a01,v.a01,u.a00+v.a11,u.a01+v.a01});
    res.a10=max({u.a10,v.a10,u.a10+v.a10,u.a11+v.a00});
    res.a11=max({u.a11,v.a11,u.a10+v.a11,u.a11+v.a01});
    return res;
}
void updt(int nd,int w){
    tree[nd].a00+=w,tree[nd].a11-=w;tag[nd]+=w;
}
void updl(int nd,int w){
    tree[nd].a01+=w,tree[nd].a10+=w,tree[nd].a11+=w;laz[nd]+=w;
}
void down(int nd){
    if(tag[nd])updt(ls,tag[nd]),updt(rs,tag[nd]),tag[nd]=0;
    if(laz[nd])updl(ls,laz[nd]),updl(rs,laz[nd]),laz[nd]=0;
}
void updt(int nd,int l,int r,int ql,int qr,int w){
	// if(nd==1)cout<<ql<<" "<<qr<<" "<<w<<" t\n";
    if(l>=ql&&r<=qr)return updt(nd,w);
    down(nd);
    if(ql<=mid)updt(ls,l,mid,ql,qr,w);
    if(qr>mid)updt(rs,mid+1,r,ql,qr,w);
    tree[nd]=merge(tree[ls],tree[rs]);
    // cout<<l<<" "<<r<<" "<<tree[nd].a00<<" "<<tree/[nd].a01<<" "<<tree[nd].a11<<"\n";
}
void updl(int nd,int l,int r,int ql,int qr,int w){
	// if(nd==1)cout<<ql<<" "<<qr<<" "<<w<<" l\n";
    if(l>=ql&&r<=qr)return updl(nd,w);
    down(nd);
    if(ql<=mid)updl(ls,l,mid,ql,qr,w);
    if(qr>mid)updl(rs,mid+1,r,ql,qr,w);
    tree[nd]=merge(tree[ls],tree[rs]);
    // cout<<l<<" "<<r<<" "<<tree[nd].a00<<" "<<tree[nd].a01<<" "<<tree[nd].a11<<"\n";
}
void work(){
    q=read();k=read();
    for(int i=1;i<=q;i++){
        int op=read(),p=read(),w=read();
        que[i]={op,p,w};lsh[++len]=p;
    }
    sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
    build(1,1,len);
    for(int i=1;i<=q;i++){
        auto[op,p,w]=que[i];
        if(op==1){
            sum+=w;
            int pp=lower_bound(lsh+1,lsh+len+1,p)-lsh;
            updt(1,1,len,pp+1,len,-w);
            updl(1,1,len,pp,pp,w);
        }
        else{
            int pr=upper_bound(lsh+1,lsh+len+1,p+k)-lsh;
            updt(1,1,len,pr,len,w);
            int pl=lower_bound(lsh+1,lsh+len+1,p-k)-lsh;
            updl(1,1,len,pl,pr-1,-w);
        }
        // cout<<sum<<" "<<tree[1].a01<<"\n";
        printf("%lld\n",sum-max(0ll,tree[1].a01));
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