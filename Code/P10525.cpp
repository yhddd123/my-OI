// Problem: P10525 [XJTUPC 2024] 图上操作
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10525
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-21 16:18:08
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,q,ans;
int pw[maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
struct node{
	int head[maxn],tot;
	struct nd{
		int nxt,to;
	}e[maxn];
	bool vis[maxn];
	int q[maxn],h,t;
	void calc(int u,int v){
		if(!vis[u]||vis[v])return ;
		vis[v]=1;
		q[h=t=1]=v;
		while(h<=t){
			int u=q[h++];
			inc(ans,pw[u]);
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(!vis[v])q[++t]=v,vis[v]=1;
			}
		}
	}
	void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;calc(u,v);}
}g[101];
pii edge[maxn];int w[maxn];
pii mdf[maxn];
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		edge[i]={read(),read()};w[i]=read();
	}
	for(int i=1;i<=q;i++){
		int p=read(),v=read();
		mdf[i]={p,w[p]};w[p]-=v;
	}
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=100;i++)g[i].vis[1]=1;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=w[i];j++)g[j].add(edge[i].fi,edge[i].se);
	}
	vector<int> res;
	res.pb(ans);
	for(int i=q;i>1;i--){
		auto[p,v]=mdf[i];
		for(int j=w[p]+1;j<=v;j++)g[j].add(edge[p].fi,edge[p].se);
		w[p]=v;
		res.pb(ans);
	}
	reverse(res.begin(),res.end());
	for(int v:res)printf("%lld\n",v);
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