#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=410;
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
int a[maxn][maxn];
int cnt[maxn][3];
bool vis[maxn][maxn];
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn*maxn];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w},head[u]=tot;
	e[++tot]={head[v],u,0},head[v]=tot;
}
int s,t,ans;
int dis[maxn],rad[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(e[i].w&&!dis[v])dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int &i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			res-=out,cnt+=out;
			e[i].w-=out,e[i^1].w+=out;
			if(!res)break;
		}
	}
	return cnt;
}
void dic(){
	ans=0;while(bfs())ans+=dfs(s,inf);
}
void work(){
	n=read();m=read();
	if(m+1&1){puts("No");return ;}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			a[i][j]=read();
			cnt[a[i][j]][2]++;
			vis[i][a[i][j]]=vis[j][a[i][j]]=1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(!vis[i][j])cnt[j][1]++;
	}
	for(int i=1;i<=m;i++){
		cnt[i][0]=(m+1)/2-cnt[i][1]-cnt[i][2];
		if(cnt[i][0]<0){puts("No");return ;}
	}
	while(n<=m){
		s=n+m+2,t=n+m+3;
		for(int i=1;i<=t;i++)head[i]=0;tot=1;
		for(int i=1;i<=m;i++)add(s,i,1);
		for(int i=1;i<=n;i++)add(i+m,t,1);
		add(n+m+1,t,m-n);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)if(!vis[i][j])add(j,i+m,1);
		}
		for(int i=1;i<=m;i++)add(i,n+m+1,2*cnt[i][0]);
		dic();
		for(int u=1;u<=n;u++){
			for(int i=head[u+m];i;i=e[i].nxt){
				int v=e[i].to;
				if(v>=1&&v<=m&&e[i].w){
					a[u][n+1]=v,vis[u][v]=vis[n+1][v]=1;
					cnt[v][1]--,cnt[v][2]++;
				}
			}
		}
		for(int i=1;i<=m;i++)if(!vis[n+1][i])cnt[i][1]++,cnt[i][0]--;
		n++;
	}
	puts("Yes");
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)printf("%lld ",a[i][j]);
		printf("\n");
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
