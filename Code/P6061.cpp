// Problem: P6061 [加油武汉] 疫情调查
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6061
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-04-07 18:23:53
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
int head[maxn],tot=1;
struct nd{
	int nxt,to,w,c;
}e[maxn*100];
void add(int u,int v,int w,int c){
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int s,t,ans;
int dis[maxn],h[maxn],pre[maxn],id[maxn];
bool vis[maxn];
priority_queue<pii> q;
bool dij(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0;
	dis[s]=0,q.push({0,s});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,ww=e[i].c+h[u]-h[v];
			if(e[i].w&&dis[v]>dis[u]+ww){
				dis[v]=dis[u]+ww,q.push({-dis[v],v});
				pre[v]=u,id[v]=i;
			}
		}
	}
	return dis[t]!=inf;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	s=2*n+1,t=2*n+2;
	for(int i=1;i<=n;i++){
		add(s,i,1,0),add(i+n,t,1,0);
		add(i,i+n,1,a[i]),add(i+n,i,inf,0);
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v+n,inf,w);
	}
	while(dij()){
		int mn=inf;
		for(int u=t;u!=s;u=pre[u])mn=min(mn,e[id[u]].w);
		for(int u=t;u!=s;u=pre[u]){
			e[id[u]].w-=mn,e[id[u]^1].w+=mn;
			ans+=mn*e[id[u]].c;
		}
		for(int i=1;i<=t;i++)h[i]+=dis[i];
	}
	printf("%lld\n",ans);
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