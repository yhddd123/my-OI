// Problem: P4897 【模板】最小割树（Gomory-Hu Tree）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4897
// Memory Limit: 125 MB
// Time Limit: 500000 ms
// Written by yhm.
// Start codeing:2024-05-28 20:22:14
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=510;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,p;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn*12];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int id[maxn];
int s,t;
int dis[maxn],rad[maxn];bool vis[maxn];
queue<int> q;
bool bfs(){
	for(int i=0;i<=n;i++)dis[i]=0,rad[i]=head[i],vis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v])dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int &i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			res-=out,cnt+=out;
			e[i].w-=out,e[i^1].w+=out;
			if(!res)break;
		}
	}
	vis[u]=0;return cnt;
}
int mp[maxn][maxn];
void sovle(int l,int r){
	if(l==r)return ;
	s=id[l],t=id[l+1];int ss=s,tt=t;
	for(int i=2;i<=tot;i+=2)e[i].w+=e[i^1].w,e[i^1].w=0;
	int ans=0;while(bfs())ans+=dfs(s,inf);
	mp[s][t]=mp[t][s]=ans;
	// cout<<s<<" "<<t<<" "<<ans<<"\n";
	vector<int> tmp1,tmp2;
	for(int i=l;i<=r;i++){
		if(dis[id[i]])tmp1.push_back(id[i]);
		else tmp2.push_back(id[i]);
	}
	int p=l,mid=l;for(int i:tmp1)id[p++]=i;
	mid=p-1;for(int i:tmp2)id[p++]=i;
	for(int i=0;i<=n;i++)if(dis[i]){
		for(int j=0;j<=n;j++)if(!dis[j]){
			mp[i][j]=mp[j][i]=min(mp[i][j],ans);
		}
	}
	sovle(l,mid),sovle(mid+1,r);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	mems(mp,0x3f);
	for(int i=0;i<=n;i++)id[i]=i;
	sovle(0,n);
	p=read();
	while(p--){
		int u=read(),v=read();
		printf("%lld\n",mp[u][v]);
	}
	
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
