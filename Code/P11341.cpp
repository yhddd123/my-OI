#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
const int inf=1e9;

extern int max_item_sum (std::vector<std::vector<int>> V);

int n,a[maxn][maxn],ans=-inf;
int f1[maxn][maxn],f2[maxn][maxn],f3[maxn][maxn],f4[maxn][maxn];
int max_item_sum (std::vector<std::vector<int>> V){
	n=V.size();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)a[i+1][j+1]=V[i][j];
	}
	memset(f1,-0x3f,sizeof(f1));
	memset(f2,-0x3f,sizeof(f2));
	memset(f3,-0x3f,sizeof(f3));
	memset(f4,-0x3f,sizeof(f4));
	f1[0][1]=f1[1][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f1[i][j]=max(f1[i-1][j],f1[i][j-1])+a[i][j];
		}
	}
	f2[0][n]=f2[1][n+1]=0;
	for(int i=1;i<=n;i++){
		for(int j=n;j;j--){
			f2[i][j]=max(f2[i-1][j],f2[i][j+1])+a[i][j];
		}
	}
	f3[n+1][n]=f3[n][n+1]=0;
	for(int i=n;i;i--){
		for(int j=n;j;j--){
			f3[i][j]=max(f3[i+1][j],f3[i][j+1])+a[i][j];
		}
	}
	f4[n+1][1]=f4[n][0]=0;
	for(int i=n;i;i--){
		for(int j=1;j<=n;j++){
			f4[i][j]=max(f4[i+1][j],f4[i][j-1])+a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans=max(ans,f1[i][j-1]+f2[i-1][j]+f3[i][j+1]+f4[i+1][j]+a[i][j]);
			ans=max(ans,f1[i-1][j]+f2[i][j+1]+f3[i+1][j]+f4[i][j-1]+a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1,s=0,mx=-inf;j<=n;j++){
			int v2=max({f2[i][j+1]+f3[i+1][j],f2[i-1][j]+f3[i][j+1],f2[i-1][j]+f3[i+1][j]});
			ans=max(ans,v2+s+a[i][j]+mx);
			int v1=max({f1[i][j-1]+f4[i+1][j],f1[i-1][j]+f4[i+1][j],f1[i-1][j]+f4[i][j-1]});
			mx=max(mx,v1-s);
			s+=a[i][j];
		}
	}
	for(int j=1;j<=n;j++){
		for(int i=1,s=0,mx=-inf;i<=n;i++){
			int v2=max({f3[i][j+1]+f4[i][j-1],f3[i][j+1]+f4[i+1][j],f3[i+1][j]+f4[i][j-1]});
			ans=max(ans,v2+s+a[i][j]+mx);
			int v1=max({f1[i][j-1]+f2[i][j+1],f1[i][j-1]+f2[i-1][j],f1[i-1][j]+f2[i][j+1]});
			mx=max(mx,v1-s);
			s+=a[i][j];
		}
	}
	return ans;
}

// void my_assert (bool x) {
	// if (!x) {
		// puts("Wrong input");
		// exit(0);
	// }
// }
// 
// int main() {
	// int N;
	// my_assert(scanf("%d", &N) == 1);
// 
	// std::vector<std::vector<int>> V(N, std::vector<int>(N));
	// for (int i = 0; i < N; i++) {
		// for (int j = 0; j < N; j++) {
			// my_assert(scanf("%d", &V[i][j]) == 1);
		// }
	// }
// 
	// int ans = max_item_sum(V);
	// printf("%d\n", ans);
// 
	// return 0;
// }