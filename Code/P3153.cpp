// Problem: P3153 [CQOI2009] 跳舞
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3153
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-29 19:29:58
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
#define db double
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

int n,k;
char c[maxn];
int a[55][55];
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int dis[maxn],rad[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
bool check(int x){
	for(int i=1;i<=t;i++)head[i]=0;tot=1;
	s=4*n+1,t=4*n+2;
	for(int i=1;i<=n;i++)add(s,i,x),add(i,i+n,k);
	for(int i=1;i<=n;i++)add(i+2*n,t,x),add(i+3*n,i+2*n,k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j])add(i,j+2*n,1);
			else add(i+n,j+3*n,1);
		}
	}
	flow=0;while(bfs())flow+=dfs(s,inf);
	return flow==x*n;
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=n;j++)if(c[j]=='Y')a[i][j]=1;
	}
	int l=1,r=n,res=0;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	printf("%lld\n",res);
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
