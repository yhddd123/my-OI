// Problem: P8435 【模板】点双连通分量
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8435
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-09-10 18:27:17
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,num;
vector<int> e[maxn],g[maxn];
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				g[++num].push_back(st[tp]);
				while(st[tp--]!=v){
					g[num].push_back(st[tp]);
				}
				g[num].push_back(u);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1;i<=n;i++)if(!dfn[i]){
		int lst=idx;
		tar(i);
		if(idx==lst+1)g[++num].push_back(i);
	}
	printf("%lld\n",num);
	for(int i=1;i<=num;i++){
		printf("%lld ",(int)g[i].size());
		for(int j:g[i])printf("%lld ",j);printf("\n");
	}
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
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
