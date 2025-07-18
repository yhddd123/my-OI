#include<bits/stdc++.h>
// #include "fish.h"
using namespace std;

namespace my{
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
const int maxn=100010;
const int inf=1e18;

int n,m;
vector<pii> a[maxn];
unordered_map<int,int> f[maxn][2];
#define lb(x) (x&(-x))
int tree[maxn<<2];
void updt(int x,int w){
    while(x<=n)tree[x]+=w,x+=lb(x);
}
int quet(int x){
    int res=0;
    while(x)res+=tree[x],x-=lb(x);
    return res;
}
void clrt(int x){
    while(x<=n)tree[x]=0,x+=lb(x);
}
int pre[maxn],suf[maxn];
void updp(int x,int w){
    x++;
    while(x<=n+1)pre[x]=max(pre[x],w),x+=lb(x);
}
int quep(int x){
    int res=-inf;x++;
    while(x)res=max(res,pre[x]),x-=lb(x);
    return res;
}
void clrp(int x){
    x++;
    while(x<=n+1)pre[x]=-inf,x+=lb(x);
}
void upds(int x,int w){
    x++;
    while(x)suf[x]=max(suf[x],w),x-=lb(x);
}
int ques(int x){
    int res=-inf;x++;
    while(x<=n+1)res=max(res,suf[x]),x+=lb(x);
    return res;
}
void clrs(int x){
    x++;
    while(x)suf[x]=-inf,x-=lb(x);
}
int sovle(){
    f[0][0][0]=0;
    for(int i=0;i<=n+1;i++)pre[i]=suf[i]=-inf;
    for(int i=1;i<=n;i++){
        for(auto[p,w]:a[i-1])updt(p,w);
        for(auto[p,w]:f[i-1][0])updp(p,w-quet(p));
        for(auto[p,w]:a[i]){
            if(p==1)continue;
            f[i][0][p-1]=max(f[i][0][p-1],quep(p-1)+quet(p-1));
        }
        f[i][0][0]=max(f[i][0][0],quep(0));
        f[i][1][n]=max(f[i][1][n],quep(n)+quet(n));
        for(auto[p,w]:f[i-1][0])clrp(p);
        if(i>2){
            for(auto[p,w]:f[i-2][1])upds(p,w+quet(p));
            for(auto[p,w]:a[i]){
                f[i][0][p-1]=max(f[i][0][p-1],ques(p)-quet(p-1));
            }
            f[i][0][0]=max(f[i][0][0],ques(1));
            for(auto[p,w]:f[i-2][1])clrs(p);
        }
        for(auto[p,w]:a[i-1])clrt(p);
        for(auto[p,w]:a[i])updt(p,w);
        for(auto[p,w]:f[i-1][1])upds(p,w+quet(p));
        for(auto[p,w]:a[i]){
            if(p==1)continue;
            f[i][1][p-1]=max(f[i][1][p-1],ques(p-1)-quet(p-1));
        }
        for(auto[p,w]:f[i-1][1])f[i][0][0]=max(f[i][0][0],w);
        f[i][1][n]=max(f[i][1][n],ques(n)-quet(n));
        for(auto[p,w]:a[i])clrt(p);
        for(auto[p,w]:f[i-1][1])clrs(p);
        // cout<<i<<"\n";
        // for(auto[p,w]:f[i][0])cout<<p<<" "<<w<<"\n";
        // for(auto[p,w]:f[i][1])cout<<p<<" "<<w<<"\n";
    }
    int ans=-inf;
    for(int i:{0,1}){
        for(auto[p,w]:f[n][i])ans=max(ans,w);
    }
    for(auto[p,w]:a[n])updt(p,w);
    for(auto[p,w]:f[n-1][1])ans=max(ans,w+quet(p));
    return ans;
}
#undef int
}
long long max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W){
    my::n=N,my::m=M;
    for(int i=0;i<M;i++){
        int x=X[i]+1,y=Y[i]+1,w=W[i];
        my::a[x].pb({y,w});
    }
    return my::sovle();
}

// int main() {
//     freopen("A.in", "r", stdin);

//   int N, M;
//   assert(2 == scanf("%d %d", &N, &M));
//   std::vector<int> X(M), Y(M), W(M);
//   for (int i = 0; i < M; ++i) {
//     assert(3 == scanf("%d %d %d", &X[i], &Y[i], &W[i]));
//   }
//   long long result = max_weights(N, M, X, Y, W);
//   printf("%lld\n", result);
//   return 0;
// }