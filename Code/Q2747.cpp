#include<bits/stdc++.h>
#include "meetings.h"

using namespace std;
namespace my{
#define int long long
#define pii pair<int,int>
const int maxn=750010;
const int inf=1e18;
namespace sgt{
    #define ls nd<<1
    #define rs nd<<1|1
    #define mid ((l+r)>>1)
    struct nd{
        int typ;
        int k,b;//tag
        int vall,valr;
    }tree[maxn<<2];
    void build(int nd,int l,int r){
        tree[nd]={0,0,0,inf,inf};
        if(l==r)return ;
        build(ls,l,mid),build(rs,mid+1,r);
    }
    void up(int nd){tree[nd].vall=tree[ls].vall,tree[nd].valr=tree[rs].valr;}
    void modif(int nd,int l,int r,int k,int b){
        tree[nd]={1,k,b,k*l+b,k*r+b};
    }
    void add(int nd,int l,int r,int k,int b){
        tree[nd].typ=(tree[nd].typ?tree[nd].typ:2);
        tree[nd].k+=k,tree[nd].b+=b;
        tree[nd].vall+=k*l+b;
        tree[nd].valr+=k*r+b;
    }
    void push(int nd,int l,int r){
        if(!tree[nd].typ)return ;
        if(tree[nd].typ==1){
            modif(ls,l,mid,tree[nd].k,tree[nd].b);
            modif(rs,mid+1,r,tree[nd].k,tree[nd].b);
        }
        else{
            add(ls,l,mid,tree[nd].k,tree[nd].b);
            add(rs,mid+1,r,tree[nd].k,tree[nd].b);
        }
        tree[nd].typ=tree[nd].k=tree[nd].b=0;
    }
    void modif(int nd,int l,int r,int p,int k,int b){
        if(l==r){modif(nd,l,r,k,b);return ;}
        push(nd,l,r);
        if(p<=mid)modif(ls,l,mid,p,k,b);
        else modif(rs,mid+1,r,p,k,b);
        up(nd);
    }
    void updata(int nd,int l,int r,int ql,int qr,int k,int b,int v){
        if(l>=ql&&r<=qr){
            if(l*k+b>=tree[nd].vall+v)return add(nd,l,r,0,v);
            if(r*k+b<=tree[nd].valr+v)return modif(nd,l,r,k,b);
        }
        push(nd,l,r);
        if(ql<=mid)updata(ls,l,mid,ql,qr,k,b,v);
        if(qr>mid)updata(rs,mid+1,r,ql,qr,k,b,v);
        up(nd);
    }
    int query(int nd,int l,int r,int p){
        if(l==r)return tree[nd].vall;
        push(nd,l,r);
        if(p<=mid)return query(ls,l,mid,p);
        else return query(rs,mid+1,r,p);
    }
    #undef ls
    #undef rs
    #undef mid
}
int n,q,a[maxn];
pii st[20][maxn];
void init(){
    for(int i=1;i<20;i++){
        for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i-1)]);
    }
}
int query(int l,int r){
    int k=log2(r-l+1);
    return abs(max(st[k][l],st[k][r-(1<<k)+1]).second);
}
vector<pii> que[maxn];
pii p1[maxn],p2[maxn];
int ans1[maxn],ans2[maxn],ans[maxn];
namespace tree{
    #define ls lc[mid]
    #define rs rc[mid]
    int lc[maxn],rc[maxn],rt;
    int build(int l,int r){
        if(l>r)return 0;
        int mid=query(l,r);
        ls=build(l,mid-1),rs=build(mid+1,r);
        return mid;
    }
    void dfs(int mid,int l,int r,bool fl){
        int val=a[mid];
        if(ls)dfs(ls,l,mid-1,0),val+=sgt::query(1,1,n,mid-1);
        if(rs)dfs(rs,mid+1,r,1);
        sgt::modif(1,1,n,mid,0,val);
        if(mid<r)sgt::updata(1,1,n,mid+1,r,a[mid],val-a[mid]*mid,a[mid]*(mid-l+1));
        if(fl)for(auto [r,id]:que[l])ans[id]=sgt::query(1,1,n,r);
    }
}
int ql[maxn],qr[maxn];
vector<int> work(){
    for(int i=1;i<=n;i++)st[0][i]={a[i],i};init();
    for(int i=1;i<=q;i++){
        int l=ql[i],r=qr[i],p=query(l,r);
        p1[i]={p+1,r};ans1[i]=(p-l+1)*a[p];
        p2[i]={l,p-1};ans2[i]=(r-p+1)*a[p];
    }
    for(int i=1;i<=q;i++)if(p1[i].first<=p1[i].second)que[p1[i].first].push_back({p1[i].second,i});
    sgt::build(1,1,n);tree::rt=tree::build(1,n);tree::dfs(tree::rt,1,n,1);
    // cout<<tree::rt<<"\n";
    for(int i=1;i<=q;i++)ans1[i]+=ans[i],ans[i]=0;
    reverse(a+1,a+n+1);
    for(int i=1;i<=n;i++)st[0][i]={a[i],-i};init();
    for(int i=1;i<=n;i++)que[i].clear();
    for(int i=1;i<=q;i++)if(p2[i].first<=p2[i].second)que[n-p2[i].second+1].push_back({n-p2[i].first+1,i});
    sgt::build(1,1,n);tree::rt=tree::build(1,n);tree::dfs(tree::rt,1,n,1);
    for(int i=1;i<=q;i++)ans2[i]+=ans[i];
    vector<int> res(q);
    for(int i=1;i<=q;i++)res[i-1]=min(ans1[i],ans2[i]);
    return res;
}
#undef int
}
vector<long long> minimum_costs(vector<int> A,vector<int> Ql,vector<int> Qr){
    my::n=A.size();my::q=Ql.size();
    for(int i=1;i<=my::n;i++)my::a[i]=A[i-1];
    for(int i=1;i<=my::q;i++)my::ql[i]=Ql[i-1]+1,my::qr[i]=Qr[i-1]+1;
    return my::work();
}

// namespace {

// int read_int() {
//   int x;
//   if (scanf("%d", &x) != 1) {
//     fprintf(stderr, "Error while reading input\n");
//     exit(1);
//   }
//   return x;
// }

// }  // namespace

// int main() {
//   int N = read_int();
//   int Q = read_int();
//   std::vector<int> H(N);
//   for (int i = 0; i < N; ++i) {
//     H[i] = read_int();
//   }
//   std::vector<int> L(Q), R(Q);
//   for (int j = 0; j < Q; ++j) {
//     L[j] = read_int();
//     R[j] = read_int();
//   }

//   std::vector<long long> C = minimum_costs(H, L, R);
//   for (size_t j = 0; j < C.size(); ++j) {
//     printf("%lld\n", C[j]);
//   }
//   return 0;
// }
