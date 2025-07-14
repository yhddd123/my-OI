#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
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

int n,m,s,t,ans;
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int d[maxn],in[maxn];
int dp[maxn],inv[maxn];
queue<int> q;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();s=read();t=read();
	inv[0]=inv[1]=1;for(int i=2;i<=n;i++)inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v);d[v]++;in[v]++;
	}
	d[t]++;
	ans=1;for(int i=2;i<=n;i++)ans*=d[i],ans%=mod;
	if(t==1){
		printf("%lld\n",ans);
		return 0;
	}
	for(int i=1;i<=n;i++)if(!in[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		if(u==t)dp[u]=ans;
		dp[u]*=inv[d[u]],dp[u]%=mod;
		if(u==s)break;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			dp[v]+=dp[u],dp[v]%=mod;
			if(!--in[v])q.push(v);
		}
	}
	ans+=mod-dp[s],ans%=mod;
	printf("%lld\n",ans);
}
