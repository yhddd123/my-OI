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
const int maxn=18;
const int inf=1e9;
bool mbe;

int n,m,c;
int e[maxn<<1],msk[1<<maxn];
int f[1<<maxn][maxn<<1],g[1<<maxn],dp[1<<maxn];
void fwt(int *a,int n,int w){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)(a[j+k]+=a[j]*w)%=mod;
		}
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn],ni[maxn+1];
void xorexp(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++){
			if(i<n)gg[i][s]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(gg[i][s]+=ff[j][s]*(j)%mod*gg[i-j][s]%mod*ni[i-j+1])%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=gg[i-1][s]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,mod-1);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();m=read();c=read();
	if(n&1)n++;
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u]|=1ll<<v,e[v]|=1ll<<u;
	}
	for(int s=0;s<(1<<n/2);s++){
		for(int i=0;i<n/2;i++)if(!(s&(1<<i)))msk[s]|=(1ll<<2*i)|(1ll<<2*i+1);
	}
	for(int i=0;i<n;i++)f[1<<i/2][i]=1;
	for(int s=0;s<(1<<n/2);s++){
		for(int i=0;i<n;i++)if(f[s][i]){
			for(int t=e[i]&msk[s];t;t&=t-1){
				int j=__builtin_ctzll(t);
				(f[s^(1<<j/2)][j^1]+=f[s][i]*c)%=mod;
			}
			g[s]+=f[s][i];
		}
	}
	for(int s=0;s<(1<<n/2);s++)g[s]=g[s]%mod*(mod+1)/2%mod;
	for(int mx=2;mx<=n;mx+=2){
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++)mems(f[s],0);
		f[1<<mx/2-1][mx-2]=1;
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++){
			for(int i=0;i<mx;i++)if(f[s][i]){
				for(int t=e[i]&msk[s]&((1ll<<mx)-1);t;t&=t-1){
					int j=__builtin_ctzll(t);
					(f[s^(1<<j/2)][j^1]+=f[s][i]*c)%=mod;
				}
				if(e[i]&(1ll<<mx-1))(g[s]+=f[s][i]*c)%=mod;
				// cout<<s<<" "<<i<<" "<<f[s][i]<<" "<<(e[i]&(1<<mx-1))<<"\n";
			}
		}
	}
	// for(int s=0;s<(1<<n/2);s++)cout<<g[s]<<" ";cout<<"\n";
	ni[0]=ni[1]=1;for(int i=2;i<=n/2;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	xorexp(g,dp,n/2);
	printf("%lld\n",dp[(1<<n/2)-1]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}