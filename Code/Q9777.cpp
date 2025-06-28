#include<bits/stdc++.h>
// #define int long long
// #define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=410;
const int inf=1e9;
bool mbe;

int n,m,mod,ans;
int C[maxn][maxn],fac[maxn],pre[maxn];
int f[maxn],g[maxn/2][maxn/2];
int vf[maxn*2][maxn][maxn],vg[maxn/2*3][maxn/2][maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();m=read();mod=read();ans=0;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)inc(C[i][j]=C[i-1][j-1],C[i-1][j]);
	}
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	pre[0]=1;for(int i=1;i<=n;i++)pre[i]=1ll*pre[i-1]*(2*i-1)%mod;
	for(int j=0;j<=n;j++)vf[0][j][j]=fac[j];
	for(int i=1;i<=2*n;i++){
		for(int j=0;j<=n&&i+j<=2*n;j++){
			for(int k=0;k<=n&&i+j+k<=2*n;k++){
				if(i>=2)inc(vf[i][j][k],1ll*vf[i-2][j][k]*(i-1)%mod);
				if(j)inc(vf[i][j][k],1ll*vf[i-1][j-1][k]*j%mod);
				if(k)inc(vf[i][j][k],1ll*vf[i-1][j][k-1]*k%mod);
			}
		}
	}
	for(int j=0;j<=n/2;j++)vg[0][j][0]=1;
	for(int i=1;i<=n+n/2;i++){
		for(int j=0;j<=n/2&&i+j<=n+n/2;j++){
			for(int k=0;k<=n;k++){
				inc(vg[i][j][k],vg[i-1][j][k]);
				if(i>=2&&k)inc(vg[i][j][k],1ll*vg[i-2][j][k-1]*(i-1)%mod);
				if(j&&k)inc(vg[i][j][k],1ll*vg[i-1][j-1][k-1]*j%mod);
			}
		}
	}
	f[0]=1;
	for(int t=1;t<=m;t++){
		if(t&1){
			for(int j=0;j<=n/2;j++){
				for(int k=0;k<=n/2;k++)g[j][k]=0;
			}
			for(int i=0;i<=n;i++)if(f[i]){
				for(int j=0;j<=i/2;j++){
					for(int k=0;k<=i/2;k++){
						inc(g[j][k],1ll*f[i]*vf[2*n-2*i][i-2*j][i-2*k]%mod*C[i][2*j]%mod*pre[j]%mod*C[i][2*k]%mod*pre[k]%mod);
					}
				}
			}
			// for(int j=0;j<=n/2;j++){
				// for(int k=0;k<=n/2;k++)cout<<g[j][k]<<" ";cout<<"\n";
			// }
		}
		else{
			for(int i=0;i<=n;i++)f[i]=0;
			for(int j=0;j<=n/2;j++){
				for(int k=0;k<=n/2;k++)if(g[j][k]){
					int p=n+k-2*j,q=n+j-2*k;
					for(int i=max(j,k);i<=n&&n+j+k-2*i>=0;i++){
						inc(f[i],1ll*g[j][k]*fac[n+j+k-2*i]%mod*vg[p][j][i-j]%mod*vg[q][k][i-k]%mod);
					}
				}
			}
			// for(int i=0;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
		}
	}
	if(m&1){
		for(int j=0;j<=n/2;j++){
			for(int k=0;k<=n/2;k++)inc(ans,g[j][k]);
		}
	}
	else{
		for(int i=0;i<=n;i++)inc(ans,f[i]);
	}
	printf("%lld\n",ans);
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