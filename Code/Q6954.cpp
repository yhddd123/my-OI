#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=16;
const int inf=1e9;
bool mbe;

int n,ans;
int e[maxn][maxn];
int a[maxn][maxn];
void clr(){for(int i=0;i<n;i++)for(int j=0;j<n;j++)a[i][j]=0;}
void add(int u,int v,int w){(a[u][u]+=w)%=mod,(a[v][v]+=w)%=mod,(a[u][v]+=mod-w)%=mod,(a[v][u]+=mod-w)%=mod;}
int det(){
	int ans=1;
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n-1;j++){
			while(a[i][i]){
				int d=a[j][i]/a[i][i];
				for(int k=i;k<n-1;k++)(a[j][k]+=mod-a[i][k]*d%mod)%=mod;
				swap(a[i],a[j]),ans=mod-ans;
			}
			swap(a[i],a[j]),ans=mod-ans;
		}
	}
	for(int i=0;i<n-1;i++)ans=ans*a[i][i]%mod;
	return ans;
}
int dp[1<<maxn][maxn],f[1<<maxn],g[1<<maxn],h[1<<maxn];
void work(){
	n=read();ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)e[i][j]=read();
	}
	for(int i=0;i<n;i++)dp[1<<i][i]=1;
	for(int s=0;s<(1<<n);s++)if(__builtin_popcount(s)>1){
		int p=__lg(s&(-s));
		for(int i=p+1;i<n;i++)if(s&(1<<i)){
			dp[s][i]=0;
			for(int j=p;j<n;j++)if((s^(1<<i))&(1<<j))(dp[s][i]+=dp[s^(1<<i)][j]*e[i][j])%=mod;
		}
		int val=0;for(int i=p+1;i<n;i++)if(s&(1<<i))(val+=dp[s][i]*e[i][p])%=mod;val=val*(mod+1)/2%mod;
		clr();
		for(int i=0;i<n;i++)if(!(s&(1<<i))){
			int sum=0;for(int j=0;j<n;j++)if(s&(1<<j))(sum+=e[i][j])%=mod;
			add(i,p,sum);
			for(int j=i+1;j<n;j++)if(!(s&(1<<j)))add(i,j,e[i][j]);
		}
		for(int i=p+1;i<n;i++)if(s&(1<<i))add(p,i,1);
		int sz=__builtin_popcount(s);
		(ans+=det()*(sz*(sz-1)/2-sz+1)%mod*val)%=mod;
		// cout<<s<<" "<<ans<<"\n";
	}
	// cout<<ans<<"\n";
	for(int s=1;s<(1<<n);s++){
		int p=__lg(s&(-s));
		clr();
		for(int i=0;i<n;i++)if(s&(1<<i)){
			for(int j=i+1;j<n;j++)if(s&(1<<j))add(i,j,e[i][j]);
		}
		for(int i=0;i<n;i++)if(!(s&(1<<i)))add(p,i,1);
		f[s]=det();
		// cout<<s<<" "<<f[s]<<"\n";
	}
	(ans+=(n*(n-1)/2-n+1)*f[(1<<n)-1])%=mod;
	// cout<<ans<<"\n";
	for(int u=0;u<n;u++){
		for(int s=0;s<(1<<n);s++)g[s]=h[s]=0;
		for(int s=0;s<(1<<n);s++){
			int val=1;for(int i=0;i<n;i++)if(s&(1<<i))val=val*(e[u][i]+1)%mod;
			g[s]=f[s]*(val-1)%mod;
		}
		h[0]=1;for(int s=1;s<(1<<n);s++)if(!(s&(1<<u))){
			for(int t=s;t;t=(t-1)&s)if((s&(-s))==(t&(-t)))(h[s]+=g[t]*h[s^t])%=mod;
		}
		// cout<<u<<" "<<h[((1<<n)-1)^(1<<u)]<<"\n";
		(ans+=h[((1<<n)-1)^(1<<u)])%=mod;
	}
	// cout<<ans<<"\n";
	for(int u=0;u<n;u++){
		for(int v=u+1;v<n;v++){
			for(int s=0;s<(1<<n);s++)g[s]=h[s]=0;
			for(int s=0;s<(1<<n);s++)if(!(s&((1<<u)|(1<<v)))){
				int valu=0,valv=0;for(int i=0;i<n;i++)if(s&(1<<i))(valu+=e[u][i])%=mod,(valv+=e[v][i])%=mod;
				g[s]=f[s]*((valu+1)*(valv+1)%mod-1)%mod;
			}
			h[0]=1;for(int s=0;s<(1<<n);s++)if(!(s&((1<<u)|(1<<v)))){
				for(int t=s;t;t=(t-1)&s)if((s&(-s))==(t&(-t)))(h[s]+=g[t]*h[s^t])%=mod;
			}
			// cout<<u<<" "<<v<<" "<<h[((1<<n)-1)^(1<<u)^(1<<v)]*(e[u][v]+1)%mod<<" "<<g[((1<<n)-1)^(1<<u)^(1<<v)]<<"\n";
			(ans+=mod-h[((1<<n)-1)^(1<<u)^(1<<v)]*(e[u][v]+1)%mod)%=mod;
		}
	}
	// cout<<ans<<"\n";
	for(int s=0;s<(1<<n-1);s++){
		int sz=__builtin_popcount(s);
		(ans+=f[s]*f[((1<<n)-1)^s]%mod*sz*(n-sz))%=mod;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}