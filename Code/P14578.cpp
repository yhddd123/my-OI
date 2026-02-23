// Problem: P14578 【模板】无源汇上下界可行流
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14578
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-02-23 21:41:29
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
const int maxn=1010;
const int maxm=11010;
const int inf=1e9;
bool mbe;

int n,m;
int head[maxn],rad[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxm<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int d[maxn];
int s,t,flow;
int val[maxm];
int dis[maxn];
bool bfs(){
	queue<int> q;
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v])dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int val){
	if(u==t)return val;
	int res=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(val,e[i].w));
			val-=out,res+=out;
			e[i].w-=out,e[i^1].w+=out;
			if(!val)break ;
		}
	}
	return res;
}
void work(){
	n=read();m=read();s=n+1,t=n+2;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),l=read(),r=read();
		add(u,v,r-l);
		d[u]-=l,d[v]+=l;
		val[i]=l;
	}
	// for(int i=1;i<=n;i++)cout<<d[i]<<" ";cout<<"\n";
	int sum=0;
	for(int i=1;i<=n;i++){
		if(d[i]>=0)add(s,i,d[i]),sum+=d[i];
		else add(i,t,-d[i]);
	}
	// for(int i=2;i<=tot;i+=2)cout<<e[i+1].to<<" "<<e[i].to<<" "<<e[i].w<<"\n";
	while(bfs())flow+=dfs(s,inf);
	if(flow!=sum){puts("No");return ;}
	puts("Yes");
	for(int i=1;i<=m;i++)printf("%d\n",val[i]+e[i<<1|1].w);
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