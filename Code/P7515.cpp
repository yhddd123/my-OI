// Problem: P7515 [省选联考 2021 A 卷] 矩阵游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7515
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-19 16:40:37
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define pii pair<int,int>
using namespace std;
const int maxn=610;
const int inf=1e6;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
vector<pii> e[maxn];
bool vis[maxn];
int dis[maxn],tim[maxn];
queue<int> q;
int a[maxn][maxn];
void sovle(){
	n=read(),m=read();
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			int x=read();
			a[i+1][j+1]=x-a[i+1][j]-a[i][j+1]-a[i][j];
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=m;j++)cout<<a[i][j]<<" ";
		// cout<<"\n";
	// }
	for(int i=1;i<=n+m;i++)e[i].clear();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)&1){
				e[j+n].push_back({i,inf-a[i][j]});
				e[i].push_back({j+n,a[i][j]});
			}
			else{
				e[i].push_back({j+n,inf-a[i][j]});
				e[j+n].push_back({i,a[i][j]});
			}
		}
	}
	while(!q.empty())q.pop();
	for(int i=1;i<=n+m;i++)dis[i]=tim[i]=0,q.push(i),vis[i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;tim[u]++;
		for(auto[v,w]:e[u]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(vis[v])continue;
				if(tim[v]>=n){puts("NO");return ;}
				vis[v]=1;q.push(v);
			}
		}
	}
	// for(int i=1;i<=n;i++)cout<<dis[i]<<" ";cout<<"\n";
	// for(int i=n+1;i<=n+m;i++)cout<<dis[i]<<" ";cout<<"\n";
	puts("YES");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)&1)a[i][j]+=dis[i];
			else a[i][j]-=dis[i];
			if((i+j)&1)a[i][j]-=dis[j+n];
			else a[i][j]+=dis[j+n];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)printf("%lld ",a[i][j]);
		printf("\n");
	}
}

int T;
signed main(){
	T=read();
	while(T--)sovle();
}