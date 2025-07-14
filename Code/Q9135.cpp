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

int n,a[maxn];
int dp[maxn][maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn*maxn];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
priority_queue<pii> q;bool vis[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)dp[i][i]=0;
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n;i++)head[i]=0;tot=0;
		for(int i=1,j=len;j<=n;i++,j++){
			dp[i][j]=inf;
			for(int k=1;k<=n;k++){
				int l=2*k-j,r=2*k-i;
				if(l>n||r<1)continue;
				if(l<1){
					dp[i][j]=min(dp[i][j],a[k]+max(dp[1][r],dp[j-(1-l)+1][j]));
				}
				else if(r>n){
					dp[i][j]=min(dp[i][j],a[k]+max(dp[l][n],dp[i][i+(r-n)-1]));
				}
				else{
					add(i,l,a[k]);
					// cout<<i<<" "<<l<<" "<<a[k]<<" e\n";
				}
				// cout<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<r<<" "<<dp[i][j]<<"\n";
			}
			// cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
		}
		for(int i=1;i<=n-len+1;i++){
			vis[i]=0;
			q.push({-dp[i][i+len-1],i});
		}
		while(!q.empty()){
			int u=q.top().se;q.pop();
			if(vis[u])continue;vis[u]=1;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(dp[v][v+len-1]>dp[u][u+len-1]+e[i].w){
					dp[v][v+len-1]=dp[u][u+len-1]+e[i].w;
					q.push({-dp[v][v+len-1],v});
				}
			}
		}
		// for(int i=1;i<=n-len+1;i++)cout<<i<<" "<<i+len-1<<" "<<dp[i][i+len-1]<<"\n";
	}
	printf("%lld\n",dp[1][n]);
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
