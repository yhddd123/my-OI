// Problem: P3337 [ZJOI2013] 防守战线
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3337
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-02-03 18:23:46
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
const int maxn=10010;
const int inf=1e9;
bool mbe;

int n,m,c[maxn];
int s,t,flow,ans;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w,c;
}e[maxn<<2];
void add(int u,int v,int w,int c){
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int h[maxn];bool vis[maxn];
void spfa(){
	queue<int> q;
	for(int i=0;i<=t;i++)h[i]=inf,vis[i]=0;
	h[s]=0,vis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&h[v]>h[u]+e[i].c){
				h[v]=h[u]+e[i].c;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
}
int dis[maxn],pre[maxn],id[maxn];
bool dij(){
	priority_queue<pii> q;
	for(int i=0;i<=t;i++)dis[i]=inf,vis[i]=0;
	dis[s]=0;q.push({0,s});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,val=e[i].c+h[u]-h[v];
			if(e[i].w&&dis[v]>dis[u]+val){
				dis[v]=dis[u]+val,pre[v]=u,id[v]=i;
				q.push({-dis[v],v});
			}
		}
	}
	return dis[t]!=inf;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)c[i]=read();
	s=0,t=n+2;
	for(int i=0;i<=n;i++){
		int v=abs(c[i]-c[i+1]);
		if(c[i]<c[i+1])add(s,i+1,v,0);
		if(c[i]>c[i+1])add(i+1,t,v,0);
	}
	for(int i=1;i<=n;i++)add(i,i+1,inf,0);
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),d=read();
		add(l,r+1,inf,-d);
	}
	spfa();
	int num=0;
	while(dij()){
		for(int i=0;i<=t;i++)h[i]+=dis[i];
		int mn=inf;
		for(int u=t;u!=s;u=pre[u])mn=min(mn,e[id[u]].w);
		flow+=mn;
		for(int u=t;u!=s;u=pre[u]){
			e[id[u]].w-=mn,e[id[u]^1].w+=mn;
            ans+=e[id[u]].c*mn;
		}
		++num;
	}
	// cout<<flow<<" "<<num<<"\n";
	printf("%lld\n",-ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}