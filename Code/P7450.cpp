// Problem: P7450 [THUSCH2017] 巧克力
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7450
// Memory Limit: 500 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=310;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
int a[maxn],c[maxn];
int val[maxn],b[maxn];
int dp[1<<5][maxn];bool vis[maxn];
priority_queue<pii> q;
int id(int u,int v){return (u-1)*m+v;}
pii pos[maxn];
int fx[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
mt19937 rnd(1989);
int sovle(int lim=-1){
	int ans=1e9;
	for(int t=1;t<=200;t++){
		for(int i=1;i<=n*m;i++)val[i]=rnd()%k;
		mems(dp,0x3f);for(int i=1;i<=n*m;i++)if(~c[i])dp[1<<val[c[i]]][i]=b[i];
		for(int s=1;s<(1<<k);s++){
			for(int i=1;i<=n*m;i++)if(~c[i]){
				for(int t=s&(s-1);t;t=(t-1)&s){
					if(t<(s^t))break;
					dp[s][i]=min(dp[s][i],dp[t][i]+dp[s^t][i]-b[i]);
				}
				if(dp[s][i]<1e9)q.push({-dp[s][i],i});vis[i]=0;
			}
			while(!q.empty()){
				int u=q.top().se;q.pop();
				if(vis[u])continue;vis[u]=1;
				int x=pos[u].fi,y=pos[u].se;
				for(int i=0;i<4;i++){
					int nx=x+fx[i][0],ny=y+fx[i][1],v=id(nx,ny);
					if(nx<1||nx>n||ny<1||ny>m||!~c[v]||vis[v])continue;
					if(dp[s][v]>dp[s][u]+b[v])dp[s][v]=dp[s][u]+b[v],q.push({-dp[s][v],v});
				}
			}
			// for(int i=1;i<=n*m;i++)cout<<dp[s][i]<<" ";cout<<"\n";
		}
		for(int i=1;i<=n*m;i++)ans=min(ans,dp[(1<<k)-1][i]);
		if(~lim&&ans<=lim)return 1;
	}
	if(~lim)return 0;
	return ans;
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n*m;i++)c[i]=read();
	for(int i=1;i<=n*m;i++)a[i]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)pos[id(i,j)]={i,j};
	for(int i=1;i<=n*m;i++)b[i]=1;
	int ans=sovle();
	if(ans==1e9){printf("-1 -1\n");return ;}
	int l=1,r=1e6,res=1e6;
	while(l<=r){
		int mid=l+r>>1;
		for(int i=1;i<=n*m;i++)b[i]=10000-(a[i]<=mid)*2+1;
		if(sovle(ans*10000))res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d %d\n",ans,res);
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
	
	T=read();
	while(T--)work();
}
