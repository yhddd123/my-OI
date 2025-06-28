// Problem: P11904 [NHSPC 2023] C. 与自动辅助驾驶畅游世界
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11904
// Memory Limit: 1 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2025-04-15 16:52:43
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n,m,s,t;
vector<int> e[maxn];
int dp[maxn];
queue<int> q;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[v].pb(u);
	}
	s=read(),t=read();
	for(int i=1;i<=n;i++)dp[i]=inf;
	dp[t]=0;q.push(t);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u])if(dp[v]==inf)dp[v]=-1,q.push(v);
	}
	for(int i=1;i<=n;i++)if(dp[i]==inf)q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u])if(dp[v]==-1)dp[v]=-2,q.push(v);
	}
	for(int i=1;i<=n;i++)if(dp[i]==-1)dp[i]=0;
	for(int i=1;i<=n;i++)if(dp[i]==-2)dp[i]=-1;
	for(int w=1;w<=n;w++){
		for(int u=1;u<=n;u++)if(dp[u]==w-1){
			for(int v:e[u])if(dp[v]==-1)dp[v]=w;
		}
		for(int i=1;i<=n;i++)if(dp[i]==inf)q.push(i);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v:e[u])if(dp[v]==-1)dp[v]=-2,q.push(v);
		}
		for(int i=1;i<=n;i++)if(dp[i]==-1)dp[i]=w;
		for(int i=1;i<=n;i++)if(dp[i]==-2)dp[i]=-1;
	}
	printf("%d\n",dp[s]==inf?-1:dp[s]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}