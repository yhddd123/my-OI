// Problem: P6192 【模板】最小斯坦纳树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6192
// Memory Limit: 250 MB
// Time Limit: 1000 ms
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
const int maxn=110;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn*10];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dp[1<<10][maxn];bool vis[maxn];
priority_queue<pii> q;
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	mems(dp,0x3f);
	for(int i=0;i<k;i++)a[i]=read(),dp[1<<i][a[i]]=0;
	for(int s=1;s<(1<<k);s++){
		for(int i=1;i<=n;i++){
			for(int t=s&(s-1);t;t=(t-1)&s){
				if(t<(s^t))break;
				dp[s][i]=min(dp[s][i],dp[t][i]+dp[s^t][i]);
			}
			q.push({-dp[s][i],i});vis[i]=0;
		}
		while(!q.empty()){
			int u=q.top().se;q.pop();
			if(vis[u])continue;vis[u]=1;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(dp[s][v]>dp[s][u]+e[i].w)dp[s][v]=dp[s][u]+e[i].w,q.push({-dp[s][v],v});
			}
		}
		// for(int i=1;i<=n;i++)cout<<dp[s][i]<<" ";cout<<"\n";
	}
	int ans=inf;for(int i=1;i<=n;i++)ans=min(ans,dp[(1<<k)-1][i]);
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
