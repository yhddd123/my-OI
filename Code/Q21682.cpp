#include<bits/stdc++.h>
#define ll long long
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
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,m,c;
ll e[maxn<<1],msk[1<<maxn];
int f[1<<maxn][maxn<<1],g[1<<maxn],dp[1<<maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void fwt(int *a,int n,int w){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],1ll*a[j]*w%mod);
		}
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1],ni[maxn+1];
void xorexp(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)gg[i]=0;
		for(int i=0;i<=n;i++){
			if(i<n)gg[i]=1ll*ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)inc(gg[i],1ll*ff[i-j+1][s]*(i-j+1)%mod*gg[j-1]%mod*ni[j]%mod);
		}
		for(int i=1;i<=n;i++)ff[i][s]=1ll*gg[i-1]*ni[i]%mod;
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
			ll t=e[i]&msk[s];
			while(t){
				int j=__builtin_ctzll(t);
				inc(f[s^(1<<j/2)][j^1],1ll*f[s][i]*c%mod);
				t&=t-1;
			}
			inc(g[s],f[s][i]);
		}
	}
	for(int s=0;s<(1<<n/2);s++)g[s]=1ll*g[s]*(mod+1)/2%mod;
	for(int mx=2;mx<=n;mx+=2){
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++)mems(f[s],0);
		f[1<<mx/2-1][mx-2]=1;
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++){
			for(int i=0;i<mx;i++)if(f[s][i]){
				ll t=e[i]&msk[s]&((1ll<<mx)-1);
				while(t){
					int j=__builtin_ctzll(t);
					inc(f[s^(1<<j/2)][j^1],1ll*f[s][i]*c%mod);
					t&=t-1;
				}
				if(e[i]&(1ll<<mx-1))inc(g[s],1ll*f[s][i]*c%mod);
				// cout<<s<<" "<<i<<" "<<f[s][i]<<" "<<(e[i]&(1<<mx-1))<<"\n";
			}
		}
	}
	// for(int s=0;s<(1<<n/2);s++)cout<<g[s]<<" ";cout<<"\n";
	ni[0]=ni[1]=1;for(int i=2;i<=n/2;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
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