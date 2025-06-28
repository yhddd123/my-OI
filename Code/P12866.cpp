#include<bits/stdc++.h>
#include <cstdio>
#define ll long long
// #include "lottery.h"
using namespace std;
const int maxn=200010;
const int inf=2e9+1;

int n,q;
int a[maxn],b[maxn];
int st[18][maxn];
int quemn(int l,int r){
    int k=__lg(r-l+1);
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
struct seg{
    #define mid (((ll)l+r)>>1)
    #define ls lc[nd]
    #define rs rc[nd]
    int num[maxn<<6];ll sum[maxn<<6];
    int lc[maxn<<6],rc[maxn<<6],idx;
    int rt[maxn];
    void updata(int &nd,int l,int r,int p){
        int lst=nd;nd=++idx;
        num[nd]=num[lst]+1;sum[nd]=sum[lst]+p;ls=lc[lst];rs=rc[lst];
        if(l==r)return ;
        if(p<=mid)updata(ls,l,mid,p);
        else updata(rs,mid+1,r,p);
    }
    int query(int nd,int nd1,int l,int r,int len,ll val=0,int cnt=0){
        if(l==r)return l-1;
        // cout<<l<<" "<<r<<" "<<val+sum[ls]-sum[lc[nd1]]<<" "<<cnt+num[rs]-num[rc[nd1]]<<endl;
        if(1ll*len*mid/2<=val+sum[ls]-sum[lc[nd1]]+1ll*(cnt+num[rs]-num[rc[nd1]])*mid)return query(rs,rc[nd1],mid+1,r,len,val+sum[ls]-sum[lc[nd1]],cnt);
        else return query(ls,lc[nd1],l,mid,len,val,cnt+num[rs]-num[rc[nd1]]);
    }
}t1,t2;
void init(int N, int Q, vector<int> X, vector<int> Y) {
    n=N;q=Q;
    for(int i=1;i<=n;i++)a[i]=X[i-1];
    for(int i=1;i<=n;i++)b[i]=Y[i-1];
    for(int i=1;i<=n;i++)st[0][i]=a[i]+b[i];
    for(int i=1;i<=17;i++){
        for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    for(int i=1;i<=n;i++)t1.updata(t1.rt[i]=t1.rt[i-1],0,inf,a[i]),t2.updata(t2.rt[i]=t2.rt[i-1],0,inf,b[i]);
    return ;
}
int max_prize(int l, int r) {
    l++,r++;
    return min({t1.query(t1.rt[r],t1.rt[l-1],0,inf,r-l+1),t2.query(t2.rt[r],t2.rt[l-1],0,inf,r-l+1),quemn(l,r)});
}

// int main() {
//     freopen("P12866.in","r",stdin);

//   int N, Q;
//   assert(scanf("%d %d", &N, &Q) == 2);

//   std::vector<int> X(N), Y(N);
//   for (int i = 0; i < N; i++) { assert(scanf("%d", &X[i]) == 1); }
//   for (int i = 0; i < N; i++) { assert(scanf("%d", &Y[i]) == 1); }

//   init(N, Q, X, Y);

//   for (int k = 0; k < Q; k++) {
//     int L, R;
//     assert(scanf("%d %d", &L, &R) == 2);
//     printf("%d\n", max_prize(L, R));
//     fflush(stdout);
//   }
// }
