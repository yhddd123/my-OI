// Problem: P3391 【模板】文艺平衡树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3391
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-10 18:17:40
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int val[maxn],w[maxn],ls[maxn],rs[maxn],rt,idx,siz[maxn];
bool fl[maxn];
void up(int u){siz[u]=siz[ls[u]]+siz[rs[u]]+1;}
void down(int u){
	swap(ls[u],rs[u]);
	fl[ls[u]]^=1,fl[rs[u]]^=1;
	fl[u]=0;
}
pii split(int u,int k){
	if(!u)return {0,0};
	if(fl[u])down(u);
	if(siz[ls[u]]+1<=k){
		pii t=split(rs[u],k-siz[ls[u]]-1);
		rs[u]=t.first;
		up(u);
		return {u,t.second};
	}
	else{
		pii t=split(ls[u],k);
		ls[u]=t.second;
		up(u);
		return {t.first,u};
	}
}
int merge(int u,int v){
	if(!u||!v)return u|v;
	if(w[u]<w[v]){
		if(fl[u])down(u);
		rs[u]=merge(rs[u],v);
		up(u);
		return u;
	}
	else{
		if(fl[v])down(v);
		ls[v]=merge(u,ls[v]);
		up(v);
		return v;
	}
}
void dfs(int u){
	if(fl[u])down(u);
	if(ls[u])dfs(ls[u]);
	printf("%lld ",val[u]);
	if(rs[u])dfs(rs[u]);
}
void insert(int x){
	val[++idx]=x,w[idx]=rand()*rand()%mod,siz[idx]=1;
	rt=merge(rt,idx);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)insert(i);
	// dfs(rt);printf("\n");
	while(m--){
		int l=read(),r=read();
		pii u=split(rt,r),v=split(u.first,l-1);
		fl[v.second]^=1;
		rt=merge(merge(v.first,v.second),u.second);
		// dfs(rt);printf("\n");
	}
	dfs(rt);
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
