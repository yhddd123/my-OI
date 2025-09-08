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
const int maxn=150010;
const int inf=1e9;
bool mbe;

int n,q,p,k,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<pii> tree[maxn<<2];
int tag[maxn<<2],len[maxn<<2];
vector<pii> merge(vector<pii> u,vector<pii> v){
    // for(auto p:u)cout<<p.fi<<" "<<p.se<<" a\n";
    // for(auto p:v)cout<<p.fi<<" "<<p.se<<" b\n";
    vector<pii> res=v;
    for(int i=0;i<res.size();i++){
        for(int j=0;j<u.size();j++)if(res[i].fi==u[j].fi){
            res[i].se+=u[j].se;u[j]=u.back();u.pop_back();
            break;
        }
    }
    while(res.size()<k&&u.size())res.pb(u.back()),u.pop_back();
    while(u.size()){
        pii p=u.back();u.pop_back();
        int mn=p.se;for(int j=0;j<k;j++)mn=min(mn,res[j].se);
        for(int j=0;j<k;j++)res[j].se-=mn;p.se-=mn;
        for(int j=0;j<res.size();j++)if(!res[j].se)res[j]=res.back(),res.pop_back(),j--;
        if(p.se)res.pb(p);
        while(res.size()<k&&u.size())res.pb(u.back()),u.pop_back();
    }
    // for(auto p:res)cout<<p.fi<<" "<<p.se<<" c\n";
    return res;
}
void build(int nd,int l,int r){
    len[nd]=r-l+1;
    if(l==r){tree[nd]={{a[l],1}};return ;}
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=merge(tree[ls],tree[rs]);
    // cout<<l<<" "<<r<<" "<<tree[nd].size()<<"\n";
}
void upd(int nd,int w){tree[nd]={{w,len[nd]}},tag[nd]=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    tree[nd]=merge(tree[ls],tree[rs]);
}
vector<pii> query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
    n=read();q=read();p=read();k=100/p;
    for(int i=1;i<=n;i++)a[i]=read();
    build(1,1,n);
    while(q--){
        int op=read();
        if(op==1){
            int l=read(),r=read(),id=read();
            updata(1,1,n,l,r,id);
        }
        else{
            int l=read(),r=read();
            vector<pii> res=query(1,1,n,l,r);
            printf("%d ",res.size());
            for(pii p:res)printf("%d ",p.fi);puts("");
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