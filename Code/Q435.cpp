#include<bits/stdc++.h>
#include "paint.h"

using namespace std;
const int maxn=100010;
#define pb push_back

int n,m,k,c[maxn];
vector<int> a[maxn];
int dp[maxn];
int mn[17][maxn];
int f[2][maxn];
vector<int> pos[maxn];
bool vis[maxn],bk[maxn];
int minimumInstructions(int N, int M, int K, vector<int> C,vector<int> A, vector<vector<int>> B) {
	n=N,m=M,k=K;
	for(int i=1;i<=n;i++)c[i]=C[i-1];
	for(int i=0;i<M;i++){
		a[i].resize(A[i]);
		for(int j=0;j<A[i];j++)a[i][j]=B[i][j],pos[a[i][j]].pb(i);
	}
	for(int i=n;i;i--){
		for(int j:pos[c[i+2]])f[i&1][i]=0;
		for(int j:pos[c[i+1]])vis[j]=1;
		for(int j:pos[c[i]])if(i==n||vis[(j+1)%m])f[i&1][j]=f[(i&1)^1][(j+1)%m]+1;
		for(int j:pos[c[i+1]])vis[j]=0;
		for(int j:pos[c[i]])if(f[i&1][j]>=m)bk[i]=1;
		// cout<<i<<" "<<bk[i]<<"\n";
		// for(int j:pos[c[i]])cout<<j<<" "<<f[i&1][j]<<"\n";
	}
	for(int i=1;i<=n;i++)dp[i]=n+1;
	auto upd=[&](int p,int v){
		mn[0][p]=v;
		for(int j=1;p-(1<<j)+1>=0;j++){
			mn[j][p]=min(mn[j-1][p],mn[j-1][p-(1<<j-1)]);
		}
	};
	auto que=[&](int l,int r){
		int k=__lg(r-l+1);
		return min(mn[k][l+(1<<k)-1],mn[k][r]);
	};
	upd(0,0);for(int i=1;i<m;i++)upd(i,n+1);
	for(int i=m;i<=n;i++){
		if(bk[i-m+1])dp[i]=que(i-m,i-1)+1;
		upd(i,dp[i]);
	}
	if(dp[n]>n)dp[n]=-1;
	return dp[n];
}

// int main() {
  // int N, M, K;
  // assert(3 == scanf("%d %d %d", &N, &M, &K));
//   
  // std::vector<int> C(N);
  // for (int i = 0; i < N; ++i) {
    // assert(1 == scanf("%d", &C[i]));
  // }
// 
  // std::vector<int> A(M);
  // std::vector<std::vector<int>> B(M);
  // for (int i = 0; i < M; ++i) {
    // assert(1 == scanf("%d", &A[i]));
    // B[i].resize(A[i]);
    // for (int j = 0; j < A[i]; ++j) {
      // assert(1 == scanf("%d", &B[i][j]));
    // }
  // }
// 
  // int minimum_instructions = minimumInstructions(N, M, K, C, A, B);
  // printf("%d\n", minimum_instructions);
//   
  // return 0;
// }