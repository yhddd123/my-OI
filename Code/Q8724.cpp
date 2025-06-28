#include<bits/stdc++.h>
// #include "september.h"
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int vis[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int mx[maxn];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);mx[u]=max(mx[u],mx[v]);
	}
}
int solve(int N,int M,vector<int>F,vector<vector<int>>S){
	n=N,m=M;vector<int> f=F;vector<vector<int>> a=S;
	for(int i=0;i<n;i++)head[i]=mx[i]=0;tot=0;
	for(int i=1;i<n;i++)add(f[i],i),add(i,f[i]);
	for(int i=0;i<m;i++){
		for(int j=0;j<n-1;j++)mx[a[i][j]]=max(mx[a[i][j]],j);
	}
	dfs(0,0);
	int ans=0;
	for(int i=0,j=0,num=0,r=0;i<n-1;i++){
		for(int k=0;k<m;k++){
			vis[a[k][i]]++;r=max(r,mx[a[k][i]]);
			if(vis[a[k][i]]==m)num++;
		}
		if(num==i-j+1&&i==r){
			++ans;num=0;
			while(j<=i){
				for(int k=0;k<m;k++)vis[a[k][j]]--;
				j++;
			}
		}
	}
	return ans;
}

// int T;
// signed main(){
	// T=read();
	// while(T--){
		// n=read();m=read();
		// vector<int> f;f.push_back(-1);
		// for(int i=1;i<n;i++)f.push_back(read());
		// vector<vector<int>> s;
		// for(int i=0;i<m;i++){
			// vector<int> a;
			// for(int i=0;i<n-1;i++)a.push_back(read());
			// s.push_back(a);
		// }
		// printf("%lld\n",solve(n,m,f,s));
	// }
// }