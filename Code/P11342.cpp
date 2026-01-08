#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=100010;
const ll inf=1e18;

extern long long place_police(vector<int> P, vector<long long> C, vector<long long> W);

int n,m;
vector<int> e[maxn];
ll a[maxn],b[maxn];
int in[maxn],idx;
ll f[maxn][2][2][2],g[2][2][2];
void dfs(int u){
	if(!e[u].size()){
		in[u]=idx++;
		for(int o=0;o<2;o++){
			for(int o1=0;o1<2;o1++){
				for(int o2=0;o2<2;o2++)f[u][o][o1][o2]=inf;
			}
		}
		f[u][0][0][0]=f[u][1][1][1]=0;
		return ;
	}
	in[u]=idx;
	for(int v:e[u]){
		dfs(v);
		// cout<<u<<" "<<v<<" "<<idx<<"\n";
		if(v==e[u].front()){
			for(int o=0;o<2;o++){
				for(int o1=0;o1<2;o1++){
					for(int o2=0;o2<2;o2++){
						g[o][o1][o2]=min(g[o][o1][o2],f[v][o][o1][o2]+a[v]);
						g[o^1][o1][o2]=min(g[o^1][o1][o2],f[v][o][o1][o2]);
					}
				}
			}
			for(int o=0;o<2;o++){
				for(int o1=0;o1<2;o1++){
					for(int o2=0;o2<2;o2++)f[u][o][o1][o2]=g[o][o1][o2],g[o][o1][o2]=inf;
				}
			}
		}
		else{
			for(int o=0;o<2;o++){
				for(int o1=0;o1<2;o1++){
					for(int o2=0;o2<2;o2++){
						for(int p=0;p<2;p++){
							for(int p1=0;p1<2;p1++){
								for(int p2=0;p2<2;p2++){
									g[o][o1][p2]=min(g[o][o1][p2],f[u][o][o1][o2]+f[v][p][p1][p2]+(o==p)*a[v]+(o2==p1)*b[in[v]-1]);
								}
							}
						}
					}
				}
			}
			for(int o=0;o<2;o++){
				for(int o1=0;o1<2;o1++){
					for(int o2=0;o2<2;o2++)f[u][o][o1][o2]=g[o][o1][o2],g[o][o1][o2]=inf;
				}
			}
		}
	}
}
ll place_police(vector<int> P,vector<ll> C,vector<ll> W){
	n=P.size()+1;m=W.size();
	for(int i=1;i<n;i++)e[P[i-1]+1].push_back(i+1);
	for(int i=1;i<n;i++)a[i+1]=C[i-1];
	for(int i=0;i<m;i++)b[i]=W[i];
	for(int o=0;o<2;o++){
		for(int o1=0;o1<2;o1++){
			for(int o2=0;o2<2;o2++)g[o][o1][o2]=inf;
		}
	}
	dfs(1);
	return min({f[1][0][0][0]+b[m-1],f[1][0][1][1]+b[m-1],f[1][0][0][1],f[1][0][1][0]});
}

// void my_assert(bool x) {
	// if (!x) {
		// puts("Wrong input");
		// exit(0);
	// }
// }
// 
// int main() {
	// int N;
	// my_assert(scanf("%d", &N) == 1);
	// vector<int> P(N - 1);
	// vector<long long> C(N - 1), W;
	// vector<int> cnt(N);
	// for (int i = 0; i < N - 1; i++) {
		// my_assert(scanf("%d %lld", &P[i], &C[i]) == 2);
		// cnt[i+1]++;
		// cnt[P[i]]++;
	// }
	// for (int i = 0; i < N; i++) {
		// if (cnt[i] == 1) {
			// long long w;
			// my_assert(scanf("%lld", &w) == 1);
			// W.push_back(w);
		// }
	// }
// 
	// printf("%lld\n", place_police(P, C, W));
// 
	// return 0;
// }
// 