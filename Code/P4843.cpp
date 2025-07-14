// Problem: P4843 清理雪道
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4843
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-02 20:16:05
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
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

int n;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn];
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<" "<<w<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int d[maxn];
void add(int u,int v,int l,int r){
	add(u,v,r-l);
	d[u]-=l,d[v]+=l;
}
int s,t,flow;
int dis[maxn],rad[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v]){
				dis[v]=dis[u]+1,q.push(v);
			}
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			res-=out,cnt+=out;
			if(!res)break;
		}
	}
	return cnt;
}
int s1,s2,t1,t2;
void work(){
	n=read();s1=n+1,t1=n+2,s2=n+3,t2=n+4;
	for(int i=1;i<=n;i++){
		add(s1,i,inf),add(i,t1,inf);
		int k=read();
		while(k--){
			int x=read();add(i,x,1,inf);
		}
	}
	for(int i=1;i<=t1;i++){
		if(d[i]>0)add(s2,i,d[i]);
		else add(i,t2,-d[i]);
	}
	flow=0,s=s2,t=t2;while(bfs())flow+=dfs(s,inf);
	add(t1,s1,inf);
	flow=0,s=s2,t=t2;while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",e[tot].w);
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
