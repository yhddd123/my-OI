// Problem: P3777 [APIO2017] 考拉的游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3777
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-09 12:47:43
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #include "koala.h"

void playRound(int*,int*);

using namespace std;

#define mkp make_pair
#define mems(a,x) memset(a,x,sizeof(a))
const int maxn=100;
int n,m,a[maxn],b[maxn];
int minValue(int N, int W) {
	n=N;
	mems(a,0),a[0]=1;
	playRound(a,b);
	for(int i=0;i<n;i++)if(b[i]<=a[i])return i;
}
int maxValue(int N, int W) {
    n=N;
	mems(a,0);for(int i=0;i<n;i++)a[i]=1;
	playRound(a,b);
	mems(a,0);for(int i=0;i<n;i++)if(b[i]==2)a[i]=2;
	playRound(a,b);
	mems(a,0);for(int i=0;i<n;i++)if(b[i]==3)a[i]=4;
	playRound(a,b);
	mems(a,0);for(int i=0;i<n;i++)if(b[i]==5)a[i]=11;
	playRound(a,b);
	for(int i=0;i<n;i++)if(b[i]==12)return i;
	return -1;
}
int greaterValue(int N, int W) {
	n=N;
	int l=0,r=14;
	while(l<=r){
		int mid=l+r>>1;
		mems(a,0);a[0]=a[1]=mid;
		playRound(a,b);
		if(b[0]>mid&&b[1]<=mid)return 0;
		if(b[0]<=mid&&b[1]>mid)return 1;
		if(b[0]<=mid&&b[1]<=mid)r=mid-1;
		if(b[0]>mid&&b[1]>mid)l=mid+1;
	}
	return 0;
}

void sovle(int l,int r,vector<int> &id,int *ans){
	if(l==r){
		ans[id[0]]=l;
		return ;
	}
	int k=0;for(int i=1;i<=m/(r-l+1);i++){
		pair<int,int> mx={0,0};
		auto sum=[&](int l,int r){return (l+r)*(r-l+1)/2;};
		auto calc=[&](int p){
			if(n-1-r+(r-p+1)*(i+1)>m)return mkp(0,0);
			int num=min(l,m-(n-1-r+(r-p+1)*(i+1)));
			return mkp(sum(p,n-1)+sum(l-num,l-1),n-p+num);
		};
		for(int j=l+1;j<=r;j++)mx=max(mx,calc(j));
		if(mx>max(calc(l),calc(r+1))){k=i;break;}
	}
	// cout<<l<<" "<<r<<" "<<k<<endl;
	mems(a,0);for(int i:id)a[i]=k;
	playRound(a,b);
	// for(int i=0;i<n;i++)cout<<b[i]<<" ";cout<<"\n";
	vector<int> vl,vr;
	for(int i:id){
		if(b[i]>k)vr.push_back(i);
		else vl.push_back(i);
	}
	// cout<<vl.size()<<" "<<vr.size()<<endl;
	sovle(l,l+vl.size()-1,vl,ans);
	sovle(l+vl.size(),r,vr,ans);
}
void allValues(int N, int W, int *P) {
	n=N,m=W;
	vector<int> id(n);
	for(int i=0;i<n;i++)id[i]=i;
    sovle(1,n,id,P);
}

// static int N, W;
// static int P[105];
// static int maxQueries = 3200;
// static int numQueries;
// static void runGame(int F);
// static void grader();
// int main() {
  // grader();
  // return 0;
// }
// void playRound(int *B, int *R) {
  // int i, j;
  // int S = 0;
  // for (i = 0; i < N; ++i) {
    // if (!(B[i] >= 0 && B[i] <= W)) {
      // printf("Invalid query 1.\n");
      // exit(0);
    // }
    // S += B[i];
  // }
  // if (S > W) {
    // printf("Invalid query 2.\n");
    // exit(0);
  // }
  // numQueries++;
  // if (numQueries > maxQueries) {
    // printf("Too many queries.\n");
    // exit(0);
  // }
  // int cache[2][205];
  // int num[2][205];
  // char taken[105][205];
  // for (i = 0; i < 205; ++i) {
    // cache[1][i] = 0;
    // num[1][i] = 0;
  // }
  // for (i = 0; i < N; ++i) {
    // int v = B[i] + 1;
    // int ii = i & 1;
    // int o = ii ^ 1;
    // for (j = 0; j <= W; ++j) {
      // cache[ii][j] = cache[o][j];
      // num[ii][j] = num[o][j];
      // taken[i][j] = 0;
    // }
    // for (j = W; j >= v; --j) {
      // int h = cache[o][j - v] + P[i];
      // int hn = num[o][j - v] + 1;
      // if (h > cache[ii][j] || (h == cache[ii][j] && hn > num[ii][j])) {
        // cache[ii][j] = h;
        // num[ii][j] = hn;
        // taken[i][j] = 1;
      // } else
        // taken[i][j] = 0;
    // }
  // }
  // int cur = W;
  // for (i = N - 1; i >= 0; --i) {
    // R[i] = taken[i][cur] ? (B[i] + 1) : 0;
    // cur -= R[i];
  // }
// }
// static void runGame(int F) {
  // int i;
  // scanf("%d %d", &N, &W);
  // for (i = 0; i < N; ++i) scanf("%d", &P[i]);
  // numQueries = 0;
  // if (F == 1) {
    // printf("%d\n", minValue(N, W));
  // } else if (F == 2) {
    // printf("%d\n", maxValue(N, W));
  // } else if (F == 3) {
  	// int ans=greaterValue(N, W);
    // printf("%d\n", ans);
    // if((P[0]<P[1])!=ans){
    	// puts("Wa");
    	// exit(0);
    // }
  // } else if (F == 4) {
    // int userP[105];
    // allValues(N, W, userP);
    // for (i = 0; i < N; i++) printf("%d ", userP[i]);
    // printf("\n");
  // }
  // printf("Made %d calls to playRound.\n", numQueries);
// }
// static void grader() {
  // int i;
  // int F, G;
  // scanf("%d %d", &F, &G);
  // for (i = 0; i < G; i++) runGame(F);
// }