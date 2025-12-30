// Problem: CF2178I Numbers or Fireworks
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2178I
// Memory Limit: 1000 MB
// Time Limit: 12000 ms
// Written by yhm.
// Start codeing:2025-12-30 17:21:08
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=31;
const int inf=1e9;
bool mbe;

int n,k,n1,n2,ans;
int x[maxn],y[maxn];
int e[maxn];
int col[maxn];
vector<int> id[2];
void dfs(int u){
	id[col[u]].pb(u);
	for(int v=0;v<n;v++)if((e[u]&(1<<v))&&col[v]==-1){
		col[v]=col[u]^1;dfs(v);
	}
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int f[1<<maxn/2],g[1<<maxn/2];
void work(){
	n=read();k=read();ans=0;
	for(int i=0;i<n;i++){
		x[i]=read(),y[i]=read();
		col[i]=-1;e[i]=0;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])==k)e[i]|=1<<j;
	}
	id[0].clear(),id[1].clear();
	for(int i=0;i<n;i++)if(col[i]==-1){
		col[i]=0;dfs(i);
	}
	if(id[0].size()>id[1].size())swap(id[0],id[1]);
	n1=id[0].size(),n2=id[1].size();
	for(int ss=0;ss<(1<<n1);ss++){
		vector<int> idd;for(int i=0;i<n1;i++)if(!(ss&(1<<i)))idd.pb(id[0][i]);
		int sz=idd.size();
		for(int s=0;s<(1<<sz);s++)f[s]=1;
		for(int i=0;i<n2;i++){
			int u=id[1][i];
			int num=0;for(int i=0;i<n1;i++)if(ss&(1<<i))num+=e[u]>>id[0][i]&1;
			for(int s=0;s<(1<<sz);s++)g[s]=f[s],f[s]=1ll*f[s]*(1+num)%mod;
			for(int i=0;i<sz;i++)if(e[u]&(1<<idd[i])){
				for(int s=0;s<(1<<sz);s++)if(!(s&(1<<i)))inc(g[s|(1<<i)],g[s]);
			}
			for(int s=0;s<(1<<sz);s++)inc(f[s],g[s]);
		}
		inc(ans,f[(1<<sz)-1]);
	}
	printf("%lld\n",ans-1);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}