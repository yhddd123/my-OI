// Problem: P2325 [SCOI2005] 王室联邦
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2325
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-02-26 18:33:07
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,B;
vector<int> e[maxn];
int id[maxn],up[maxn],p[maxn],idx;
int st[maxn],tp;
void dfs(int u,int fa){
	int lst=tp;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		if(tp-lst>=B){
			p[++idx]=u;
			while(tp>lst){
				int p=st[tp--];
				id[p]=idx;
			}
		}
	}
	if(!fa){
		if(!idx)idx=1;
		p[idx]=u;
		while(tp){
			int p=st[tp--];
			id[p]=idx;
		}
	}
	st[++tp]=u;
}
void work(){
	n=read();B=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=idx;i++)if(p[i]==1)id[1]=i;
	printf("%lld\n",idx);
	for(int i=1;i<=n;i++)printf("%lld ",id[i]);puts("");
	for(int i=1;i<=idx;i++)printf("%lld ",p[i]);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}