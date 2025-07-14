// Problem: P3233 [HNOI2014] 世界树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3233
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-22 15:47:58
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=300010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int f[maxn][19],siz[maxn],dep[maxn];
int dfn[maxn],idx;
void dfs(int u,int fa){
	siz[u]=1;dfn[u]=++idx;
	dep[u]=dep[fa]+1;f[u][0]=fa;
	for(int i=1;i<=18;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
	}
}
int m,id[maxn];
int st[maxn],tp;
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	q=read();
	while(q--){
		m=read();for(int i=1;i<=m;i++)id[i]=read();
		sort(id+1,id+m+1,[&](int u,int v){return dfn[u]<dfn[v];});
		st[tp=1]=1;tot=0;head[1]=0;
		for(int i=1;i<=m;i++){
			int l=lca(st[tp],id[i]);
			if(l!=st[tp]){
				while(dfn[l]<dfn[st[tp-1]]){
					add(st[tp-1],st[tp]);
					tp--;
				}
				if(st[tp-1]!=l){
					head[l]=0;add(l,st[tp]);
					st[tp]=l;
				}
				else{
					add(l,st[tp]);tp--;
				}
			}
		}
		head[id[i]]=0;st[++tp]=id[i];
	}
}

// \
444

bool Med;
int T;
signed main(){
//w	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
