#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=300010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],b[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
	}
}
int dp[515],f[515];
pii st[maxn<<2];int tp;
bool ans[maxn];
void dfs(int u){
	int lst=tp;
	for(int i=0;i<512;i++)f[i]=dp[i];
	for(int i=0;i<512;i++)f[(i+a[u])%512]=min(f[(i+a[u])%512],dp[i]+a[u]);
	for(int i=0;i<512;i++)if(f[i]<dp[i])st[++tp]={i,dp[i]},dp[i]=f[i];
	if(dp[b[u]%512]<=b[u])ans[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(dep[v]+1==dep[u])continue;
		dfs(v);
	}
	while(tp>lst)dp[st[tp].fi]=st[tp].se,tp--;
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	dfs(1,0);
	for(int u=1;u<=n;u++)if(dep[u]<=12)a[u]=1<<(20-dep[u]+1);
	for(int u=1;u<=n;u++)if(dep[u]<=12)ans[u]=(b[u]%(1<<(20-dep[u]+1))==0);
	mems(dp,0x3f);dp[0]=0;
	for(int u=1;u<=n;u++)if(dep[u]==13)dfs(u);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
	for(int i=1;i<=n;i++)printf("%d",ans[i]);puts("");
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
