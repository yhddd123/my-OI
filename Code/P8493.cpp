// #include "circuit.h"
#include<bits/stdc++.h>
#define mod 1000002022ll
using namespace std;
const int maxn=100010;

int n,m,a[maxn],b[maxn];
vector<int> e[maxn<<1];
int f[maxn<<1],g[maxn<<1];
void dfs(int u){	
	if(!e[u].size()){f[u]=1;return ;}
	f[u]=e[u].size();
	for(int v:e[u])dfs(v),f[u]=1ll*f[u]*f[v]%mod;
}
int pre[maxn<<1],suf[maxn<<1];
void dfs1(int u){
	if(!e[u].size())return ;
	for(int i=0,mul=1;i<e[u].size();i++){
		pre[e[u][i]]=mul;
		mul=1ll*mul*f[e[u][i]]%mod;
	}
	for(int i=e[u].size()-1,mul=1;~i;i--){
		suf[e[u][i]]=mul;
		mul=1ll*mul*f[e[u][i]]%mod;
	}
	for(int v:e[u]){
		g[v]=1ll*g[u]*pre[v]%mod*suf[v]%mod;
		// cout<<u<<" "<<v<<" "<<pre[v]<<" "<<suf[v]<<" "<<g[v]<<"\n";
		dfs1(v);
	}
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int sum[maxn<<2][2],tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){
		sum[nd][0]=a[l]*b[l],sum[nd][1]=(1-a[l])*b[l];
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	sum[nd][0]=(sum[ls][0]+sum[rs][0])%mod,sum[nd][1]=(sum[ls][1]+sum[rs][1])%mod;
}
void upd(int nd){swap(sum[nd][0],sum[nd][1]),tag[nd]^=1;}
void down(int nd){upd(ls),upd(rs),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return upd(nd);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr);
	if(qr>mid)updata(rs,mid+1,r,ql,qr);
	sum[nd][0]=(sum[ls][0]+sum[rs][0])%mod,sum[nd][1]=(sum[ls][1]+sum[rs][1])%mod;
}
void init(int N, int M, std::vector<int> P, std::vector<int> A) {
	n=N,m=M;
	for(int i=1;i<n+m;i++)e[P[i]].push_back(i);
	for(int i=0;i<m;i++)a[i]=A[i];
	dfs(0);
	g[0]=1;dfs1(0);
	for(int i=0;i<m;i++)b[i]=g[n+i];
	// for(int i=0;i<m;i++)cout<<a[i]<<" "<<b[i]<<"\n";
	build(1,0,m-1);
}
int count_ways(int L, int R) {
	L-=n,R-=n;
	updata(1,0,m-1,L,R);
	return sum[1][0];
}

// int main() {
  // int N, M, Q;
  // assert(3 == scanf("%d %d %d", &N, &M, &Q));
  // std::vector<int> P(N + M), A(M);
  // for (int i = 0; i < N + M; ++i) {
    // assert(1 == scanf("%d", &P[i]));
  // }
  // for (int j = 0; j < M; ++j) {
    // assert(1 == scanf("%d", &A[j]));
  // }
  // init(N, M, P, A);
// 
  // for (int i = 0; i < Q; ++i) {
    // int L, R;
    // assert(2 == scanf("%d %d", &L, &R));
    // printf("%d\n", count_ways(L, R));
  // }
  // return 0;
// }