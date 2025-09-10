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
const int inf=2e9;
bool mbe;

int n,q,ans;
int a[maxn],b[maxn];
int lst[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
namespace sgt1{
pii mn[maxn<<2];int tag[maxn<<2];
void build(int nd,int l,int r){
    mn[nd]={l,l};
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){mn[nd].fi+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    mn[nd]=min(mn[ls],mn[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mn[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
}
namespace sgt2{
multiset<int> val[maxn];
pii mn[maxn<<2];
void build(int nd,int l,int r){
    mn[nd]={inf,l};
    if(l==r){val[l].insert(inf);return ;}
    build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p,int w,int op){
    if(l==r){
        // cout<<p<<" "<<w<<" "<<op<<" "<<(val[l].find(w)==val[l].end())<<endl;
        if(op==1)val[l].insert(w);
        else val[l].erase(val[l].find(w));
        mn[nd]={*val[l].begin(),l};
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p,w,op);
    else modif(rs,mid+1,r,p,w,op);
    mn[nd]=min(mn[ls],mn[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mn[nd];
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
}
vector<pii> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,pii w){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr){tree[nd].pb(w);return ;}
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void sovle(int nd,int l,int r){
    vector<pii> add,del;
    // cout<<l<<" "<<r<<"\n";
    auto upd=[&](pii p,int op,bool fl=1){
        // cout<<p.fi<<" "<<p.se<<" "<<op<<"\n";
        ans+=p.se*op;
        sgt1::updata(1,1,n,p.fi,n,-op);
        sgt2::modif(1,1,n,p.fi,p.se,op);
        if(fl){
            if(op==1)add.pb(p);
            else del.pb(p);
        }
    };
    for(pii p:tree[nd]){
        pii res=sgt1::query(1,1,n,p.fi,n);
        // cout<<p.fi<<" "<<p.se<<" "<<res.fi<<" "<<res.se<<"\n";
        if(res.fi>0)upd(p,1);
        else{
            res=sgt2::query(1,1,n,1,res.se);
            if(res.fi<=p.se)upd({res.se,res.fi},-1),upd(p,1);
        }
    }
    // cout<<l<<" "<<r<<" "<<ans<<" "<<add.size()<<" "<<del.size()<<" s\n";
    if(l==r){
        printf("%lld\n",ans);
    }
    else sovle(ls,l,mid),sovle(rs,mid+1,r);
    // cout<<l<<" "<<r<<" "<<ans<<"\n";
    for(pii p:del)upd(p,1,0);
    for(pii p:add)upd(p,-1,0);
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)b[i]=read();
    for(int i=1;i<=n;i++)lst[i]=1;
    for(int i=1;i<=q;i++){
        int p=read(),u=read(),v=read();
        updata(1,1,q,lst[p],i-1,{a[p],b[p]});
        a[p]=u,b[p]=v,lst[p]=i;
    }
    for(int i=1;i<=n;i++)updata(1,1,q,lst[i],q,{a[i],b[i]});
    sgt1::build(1,1,n),sgt2::build(1,1,n);
    sovle(1,1,q);
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