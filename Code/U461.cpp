// Problem: #461. 新年的Dog划分
// Contest: UOJ
// URL: https://uoj.ac/problem/461
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-16 08:29:51
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#include "graph.h"
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=210;

// #define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
// #define debug(...) fprintf(stderr, __VA_ARGS__)
// #define mp make_pair
// #define x first
// #define y second
// #define pb push_back
// #define SZ(x) (int((x).size()))
// #define ALL(x) (x).begin(), (x).end()
// static int _n;
// static bool _adj[maxn + 5][maxn + 5];
// void init(int n) {
	// _n = n;
	// int m;
	// assert(scanf("%d", &m) == 1);
	// memset(_adj, 0, sizeof _adj);
	// REP(i, 0, m){
		// int u, v;
		// assert(scanf("%d%d", &u, &v) == 2);
		// _adj[u][v] = _adj[v][u] = 1;
	// }
// }
// static int _pa[maxn + 5];
// static int _get(int x) { return _pa[x] == x ? x : _pa[x] = _get(_pa[x]); }
// bool query(vector<pair<int, int> > banned_edges){
	// static bool banned[maxn + 5][maxn + 5];
	// memset(banned, 0, sizeof banned);
	// REP(i, 0, SZ(banned_edges)){
		// banned[banned_edges[i].x][banned_edges[i].y] = 1;
		// banned[banned_edges[i].y][banned_edges[i].x] = 1;
	// }
	// REP(i, 0, _n) _pa[i] = i;
	// REP(i, 0, _n) REP(j, 0, _n - 1) if (_adj[i][j] && !banned[i][j]) _pa[_get(i)] = _get(j);
	// REP(i, 1, _n) if (_get(i) != _get(0)) return 0;
	// return 1;
// }

int n;
vector<int> e[maxn],a,b;
bool vis[maxn],bk[maxn];
void dfs(int u,int fl=0){
	if(!fl)a.push_back(u);
	else b.push_back(u);
	for(int v:e[u])dfs(v,fl^1);
}
vector<int> check_bipartite(int vsize){
	n=vsize;
	queue<int> q;q.push(0);bk[0]=1;
	map<pii,int> mp;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=1;
		vector<int> id;
		for(int i=0;i<n;i++)if(!bk[i])id.push_back(i);
		vector<pii> que;
		for(int i=0;i<n;i++)if(vis[i]&&i!=u){
			for(int j:id)que.push_back({i,j});
		}
		// cout<<u<<"\n";for(int i:id)cout<<i<<" ";cout<<"\n";
		while(id.size()){
			for(int i:id)que.push_back({u,i});
			if(query(que))break;
			for(int i:id)que.pop_back();
			int l=0,r=id.size()-1,res=id.size()-1;
			while(l<r){
				int mid=l+r>>1;
				int tmp=que.size();
				for(int i=l;i<=mid;i++)que.push_back({u,id[i]});
				bool fl=query(que);
				if(fl)l=mid+1;
				else{
					r=mid,res=mid;
					while(que.size()>tmp)que.pop_back();
				}
			}
			e[u].push_back(id[res]);q.push(id[res]);bk[id[res]]=1;
			// cout<<u<<" "<<id[res]<<"\n";
			mp[{u,id[res]}]=mp[{id[res],u}]=1;
			for(int i=0;i<=res;i++)swap(id[i],id.back()),id.pop_back();
		}
	}
	dfs(0);
	vector<pii> que;
	for(int i:a)for(int j:b)if(!mp[{i,j}])que.push_back({i,j});
	for(int u=0;u<n;u++){
		for(int v:e[u]){
			que.push_back({u,v});
			bool fl=query(que);
			if(fl){
				a.clear();
				return a;
			}
			que.pop_back();
		}
	}
	return a;
}

// int main(){
	// int n;
	// scanf("%d", &n);
	// init(n);
	// vector<int> out = check_bipartite(n);
	// printf("%d\n", SZ(out));
	// REP(i, 0, SZ(out))printf("%d ", out[i]);printf("\n");
// }