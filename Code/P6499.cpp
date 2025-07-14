// Problem: P6499 [COCI2016-2017#2] Burza
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6499
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-10-18 15:01:41
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=410;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],dfn[maxn],idx,rnk[maxn],siz[maxn],mx[maxn];
void dfs(int u,int fa){
	rnk[dfn[u]=++idx]=u;siz[u]=1;dep[u]=dep[fa]+1;mx[u]=dep[u];
	// cout<<u<<" "<<idx<<" "<<dep[u]<<" "<<mx[u]<<"\n";
	if(dep[u]==k)return ;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];mx[u]=max(mx[u],mx[v]);
	}
}
bool dp[maxn][1<<19];
void work(){
	n=read();k=read();
	if(k>=20){puts("DA");return ;}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dep[0]=-1;dfs(1,0);dp[idx+1][0]=1;
	for(int i=idx;i>1;i--){
		int u=rnk[i];
		if(siz[u]>1||mx[u]<k){
			for(int s=0;s<(1<<k);s++)dp[i][s]=dp[i+1][s];
		}
		for(int s=0;s<(1<<k);s++)if(!(s&(1<<dep[u]-1))){
			dp[i][s|(1<<dep[u]-1)]|=dp[i+siz[u]][s];
		}
		// cout<<u<<" "<<siz[u]<<" "<<dep[u]<<"\n";
		// for(int s=0;s<(1<<k);s++)cout<<dp[i][s]<<" ";cout<<"\n";
	}
	bool fl=0;for(int s=0;s<(1<<k);s++)fl|=dp[2][s];
	if(fl)puts("DA");
	else puts("NE");
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
