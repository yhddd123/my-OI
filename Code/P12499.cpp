// Problem: P12499 Life Lies in Movement
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12499
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-29 14:41:45
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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,k,ans;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int siz[maxn],dep[maxn];
int dfn[maxn],out[maxn],idx;
int f[maxn],tag;
void upd(int l,int r,int w){
	f[l]+=w,f[r+1]-=w;
}
void dfs(int u,int fa){
	dfn[u]=++idx;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dep[v]=dep[u]+e[i].w;dfs(v,u);siz[u]+=siz[v];
		upd(dfn[v],out[v],2*siz[v]*e[i].w-n*e[i].w);
	}
	out[u]=idx;
}
int lsh[maxn],len;
int tree[maxn];
#define lb(x) (x&(-x))
void upd(int x,int w){
	while(x<=len)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void dfs1(int u,int fa){
	ans+=n-que(lower_bound(lsh+1,lsh+len+1,tag)-lsh-1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		tag+=(2*siz[v]-n)*e[i].w;
		siz[u]-=siz[v],siz[v]+=siz[u];
		dfs1(v,u);
		siz[v]-=siz[u],siz[u]+=siz[v];
		tag-=(2*siz[v]-n)*e[i].w;
	}
}
void work(){
	n=read();k=read();ans=0;
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<=n;i++)f[i]=tree[i]=0;
	idx=0;dfs(1,0);tag=2*n*k;
	for(int i=1;i<=n;i++)f[i]+=f[i-1];
	len=0;for(int i=1;i<=n;i++)lsh[++len]=f[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++){
		f[i]=lower_bound(lsh+1,lsh+len+1,f[i])-lsh;
		upd(f[i],1);
	}
	dfs1(1,0);
	printf("%lld\n",ans);
}
	
bool med;
int T;
signed main(){
	// freopen("carracing.in","r",stdin);
	// freopen("carracing.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}