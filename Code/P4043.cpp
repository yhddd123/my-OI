// Problem: P4043 [AHOI2014/JSOI2014] 支线剧情
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4043
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-02 20:36:21
// 
// Powered by CP Editor (https://cpeditor.org)

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
	int nxt,to,w,c;
}e[maxn];
void add(int u,int v,int w,int c){
	// cout<<u<<" "<<v<<" "<<w<<" "<<c<<"\n";
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int d[maxn],ans;
void add(int u,int v,int l,int r,int c){
	add(u,v,r-l,c);
	d[u]-=l,d[v]+=l;ans+=l*c;
}
int s,t,flow;
int dis[maxn],rad[maxn];
bool vis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,rad[i]=head[i],vis[i]=0;
	dis[s]=0,q.push(s),vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(!vis[v]&&e[i].w&&dis[v]==dis[u]+e[i].c){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			res-=out,cnt+=out;
			ans+=e[i].c*out;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
int s1,s2,t1,t2;
void work(){
	n=read();s1=1,t1=n+1,s2=n+2,t2=n+3;
	for(int i=1;i<=n;i++){
		add(i,t1,0,inf,0);
		int k=read();
		while(k--){
			int x=read(),c=read();add(i,x,1,inf,c);
		}
	}
	for(int i=1;i<=t1;i++){
		if(d[i]>0)add(s2,i,d[i],0);
		else add(i,t2,-d[i],0);
	}
	add(t1,s1,inf,0);
	flow=0,s=s2,t=t2;while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",ans);
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
