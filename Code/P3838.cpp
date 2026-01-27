#include<bits/stdc++.h>
using namespace std;

const int maxn=5010;
int n;
vector<int> e[maxn],g[maxn];
bool a[maxn],ok[maxn],ans[maxn];
int d[maxn];
vector<int> who_wins(vector<int> A, vector<int> R, vector<int> U, vector<int> V) {
	int n=A.size();
	for(int i=0;i<n;i++)a[i+1]=A[i];
	for(int i=0;i<n;i++)ok[i+1]=R[i];
	for(int i=0;i<U.size();i++){
		e[U[i]+1].push_back(V[i]+1),g[V[i]+1].push_back(U[i]+1);
	}
	for(int t=1;t<=n;t++){
		for(int i=1;i<=n;i++)ans[i]=0;
		for(int i=1;i<=n;i++)d[i]=e[i].size();
		queue<int> q;
		for(int i=1;i<=n;i++)if(ok[i])ans[i]=1,q.push(i);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v:g[u])if(!ans[v]){
				if(a[v])ans[v]=1,q.push(v);
				else if(!--d[v])ans[v]=1,q.push(v);
			}
		}
		for(int u=1;u<=n;u++)if(ok[u]){
			bool fl=0;
			if(a[u]){
				for(int v:e[u])if(ans[v])fl=1;
			}
			else{
				fl=1;
				for(int v:e[u])if(!ans[v])fl=0;
			}
			if(!fl)ok[u]=0;
		}
	}
	vector<int> res(n);
	for(int i=1;i<=n;i++)res[i-1]=ans[i];
	return res;
}


// int main() {
	// int n, m;
	// assert(2 == scanf("%d %d", &n, &m));
// 
	// vector<int> a(n), r(n), u(m), v(m);
// 
	// for(int i = 0; i < n; i++)
		// assert(1 == scanf("%d", &a[i]));
// 
	// for(int i = 0; i < n; i++)
		// assert(1 == scanf("%d", &r[i]));
// 
	// for(int i = 0; i < m; i++)
		// assert(2 == scanf("%d %d", &u[i], &v[i]));
// 
	// vector<int> res = who_wins(a, r, u, v);
// 
	// for(int i = 0; i < (int)res.size(); i++)
		// printf(i ? " %d" : "%d", res[i]);
	// printf("\n");
// 
	// return 0;
// }