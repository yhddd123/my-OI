#include<bits/stdc++.h>
using namespace std;
// #include "souvenirs.h"
std::pair<std::vector<int>, long long> transaction(long long M);

const int maxn=110;
int n,t[maxn],pos;long long a[maxn];
void sovle(long long w){
    auto[id,val]=transaction(w);val=w-val;
    for(int u:id)t[u]++;
    while(pos>id[0]){
        long long sum=val;int cnt=0;
        for(int u:id){
            if(!a[u])++cnt;
            else sum-=a[u];
        }
        // cout<<id[0]<<" "<<sum<<" "<<cnt<<"\n";
        sovle((sum-1)/cnt);
    }
    pos--;
    for(int u:id)val-=a[u];
    a[id[0]]=val;
}
void buy_souvenirs(int N, long long P0){
    n=N,a[0]=P0;pos=n-1;
    for(int i=1;i<n;i++)a[i]=t[i]=0;
    sovle(a[0]-1);
    for(int i=1;i<n;i++){
        while(t[i]<i)transaction(a[i]),t[i]++;
    }
}

// namespace {
// const int CALLS_CNT_LIMIT = 10'000;

// int calls_cnt;
// int N;
// std::vector<long long> P;
// std::vector<int> Q;

// void quit(const char* message) {
//   printf("%s\n", message);
//   exit(0);
// }
// } // namespace

// std::pair<std::vector<int>, long long> transaction(long long M) {
//     cout<<M<<"\n";
//   calls_cnt++;
//   if (calls_cnt > CALLS_CNT_LIMIT)
//     quit("Too many calls");
//   if (M >= P[0] || M < P[N - 1])
//     quit("Invalid argument");

//   std::vector<int> L;
//   long long R = M;
//   for (int i = 0; i < N; i++) {
//     if (R >= P[i]) {
//       R -= P[i];
//       Q[i]++;
//       L.push_back(i);
//     }
//   }
//   return {L, R};
// }

// int main() {
//     freopen("A.in","r",stdin);
// assert(1 == scanf("%d", &N));
// P.resize(N);
// for (int i = 0; i < N; i++)
// assert(1 == scanf("%lld", &P[i]));
// fclose(stdin);

// Q.assign(N, 0);
// calls_cnt = 0;
// buy_souvenirs(N, P[0]);
// for (int i = 0; i < N; i++)
// printf("%s%d", i ? " " : "", Q[i]);
// printf("\n");
// fclose(stdout);

// return 0;
// }
