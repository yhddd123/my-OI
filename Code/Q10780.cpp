#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,ll>
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=410;
const int maxm=100010;
const int maxk=500010;
const ll inf=1e18;
bool mbe;

int n,m,a[maxm];ll t;
int c[maxn],w[maxn],d[maxn];
ll f[maxk];
ll val[maxm][maxn];
struct ds{
	int id;
	int q[maxm];int h=1,t;
	void ins(int p){
		while(h<=t&&val[p][id]<val[q[t]][id])t--;q[++t]=p;
	}
	ll que(int p){
		while(h<=t&&q[h]<p)h++;
		return h<=t?val[q[h]][id]:inf;
	}
}q[maxn];
ll sum[maxn];
ll dp[maxn];
ll vmn[maxk];
void work(){
	m=read();n=read();t=read();
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=n;i++)c[i]=read(),w[i]=min(read(),maxk-10),d[i]=read();d[0]=n;
	f[0]=0;for(int i=1;i<=maxk-10;i++){
		f[i]=f[i-1]+t;
		for(int j=1;j<=n;j++)if(i>=w[j])f[i]=min(f[i],f[i-w[j]]+c[j]);
	}
	for(int i=maxk-10;i;i--)f[i-1]=min(f[i-1],f[i]);
	for(int j=0;j<=n;j++)dp[j]=inf;dp[0]=0;
	for(int i=1;i<=n;i++)q[i].id=i;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=n;j++)sum[j]+=max(0,a[i]-w[j])*t;
		for(int j=0;j<=a[i];j++)vmn[j]=inf;
		for(int k=0;k<=n;k++)vmn[max(0,a[i]-w[k])]=min(vmn[max(0,a[i]-w[k])],dp[k]);
		for(int j=1;j<=n;j++){
			ll mn=inf;for(int k=0;k<=a[i];k++)mn=min(mn,vmn[k]+f[max(0,k-w[j])]);
			mn+=c[j]-sum[j];
			val[i][j]=mn;
			q[j].ins(i);
		}
		// for(int j=1;j<=n;j++){
			// ll mn=inf;for(int k=0;k<=n;k++)mn=min(mn,dp[i-1][k]+f[max(0,a[i]-w[j]-w[k])]);
			// mn+=+c[j]-sum[i][j];
			// val[i][j]=mn;
			// q[j].ins({i,mn});
		// }
		dp[0]=dp[0]+t*a[i];
		for(int j=1;j<=n;j++)if(i-d[j]+1>0)dp[0]=min(dp[0],val[i-d[j]+1][j]+sum[j]);
		for(int j=1;j<=n;j++)dp[j]=q[j].que(i-d[j]+2)+sum[j];
		// cout<<i<<"\n";
		// for(int j=0;j<=n;j++)cout<<(dp[i][j]==inf?-1:dp[i][j])<<" ";cout<<"\n";
	}
	ll ans=inf;for(int j=0;j<=n;j++)ans=min(ans,dp[j]);
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}