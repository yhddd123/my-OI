// Problem: P8375 [APIO2022] 游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8375
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-12 18:38:47
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #include "game.h"

using namespace std;
const int maxn=300010;
#define pb push_back

int n,k;
vector<int> e[maxn],g[maxn];
int pl[maxn],pr[maxn];
void init(int N, int K) {
	n=N,k=K;
	for(int i=1;i<=k;i++)pl[i]=pr[i]=i;
	for(int i=k+1;i<=n;i++)pl[i]=0,pr[i]=k+1;
}
bool add(int u,int v);
bool down(int u){
	for(int v:e[u])if(add(u,v))return 1;
	for(int v:g[u])if(add(v,u))return 1;
	return 0;
}
bool add(int u,int v){
	if(u<=k&&v<=k)return u>=v;
	if(pr[u]<pl[v])return 0;
	if(pr[v]<pl[u])return 1;
	if(pl[u]<=pl[v]){
		int mid=pl[u]+pr[u]>>1;
		if(pr[v]<=mid){
			pr[u]=mid;
			return pl[u]==pr[u]||down(u);
		}
	}
	if(pr[u]<=pr[v]){
		int mid=pl[v]+pr[v]>>1;
		if(pl[u]>mid){
			pl[v]=mid+1;
			return pl[v]==pr[v]||down(v);
		}
	}
	return 0;
}
int add_teleporter(int u, int v) {
	u++,v++;
	e[u].pb(v),g[v].pb(u);
	return add(u,v);
}

// int read_int() {
  // int x;
  // if (scanf("%d", &x) != 1) {
    // fprintf(stderr, "Error while reading input\n");
    // exit(1);
  // }
  // return x;
// }
// 
// int main() {
  // int N = read_int();
  // int M = read_int();
  // int K = read_int();
  // std::vector<int> u(M), v(M);
  // for (int i = 0; i < M; ++i) {
    // u[i] = read_int();
    // v[i] = read_int();
  // }
// 
  // init(N, K);
  // int i;
  // for (i = 0; i < M; ++i) {
    // int answer = add_teleporter(u[i], v[i]);
    // if (answer != 0 && answer != 1) {
      // i = -1;
      // break;
    // } else if (answer == 1) {
      // break;
    // }
  // }
  // printf("%d\n", i);
  // return 0;
// }