#include<bits/stdc++.h>
#define int long long
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
const int maxn=45;
const int inf=1e9;
bool mbe;

int n,m,mod,ans;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int C[maxn*maxn][maxn*maxn],S[maxn][maxn],fac[maxn],val[maxn];
int f[maxn][maxn][maxn],g[maxn][maxn][maxn];
void work(){
	n=read();m=read();mod=read();
	for(int i=0;i<=n*n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=0,mul=1;i<=n;mul=mul*(m-i)%mod*ksm(i+1)%mod,i++)val[i]=mul;
	S[0][0]=1;for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)S[i][j]=(S[i-1][j-1]+j*S[i-1][j])%mod;
	}
	f[1][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=i+j-1;k<=n;k++){
				f[i][j][k]=C[i*j][k];
				for(int ii=1;ii<=i;ii++){
					for(int jj=0;jj<=j;jj++)if(i!=ii||j!=jj){
						for(int kk=ii+jj-1;kk<=k;kk++){
							(f[i][j][k]+=mod-f[ii][jj][kk]*C[i-1][ii-1]%mod*C[j][jj]%mod*C[(i-ii)*(j-jj)][k-kk])%=mod;
						}
					}
				}
				// cout<<i<<" "<<j<<" "<<k<<" "<<f[i][j][k]<<"\n";
			}
		}
	}
	g[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++)if(i||j){
			for(int k=0;k<=n;k++){
				for(int ii=1;ii<=i;ii++){
					for(int jj=1;jj<=j;jj++){
						for(int kk=ii+jj-1;kk<=k;kk++){
							(g[i][j][k]+=f[ii][jj][kk]*C[i-1][ii-1]%mod*C[j][jj]%mod*g[i-ii][j-jj][k-kk]%mod*m)%=mod;
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=n&&i<=m;i++){
		for(int j=1;j<=n&&j<=m;j++){
			for(int k=1;k<=n;k++){
				(ans+=g[i][j][k]*S[n][k]%mod*fac[k]%mod*val[i]%mod*val[j]%mod*ksm(m,2*m-i-j))%=mod;
			}
		}
	}
	// cout<<ans<<"\n";
	printf("%lld\n",ans*ksm(ksm(m,2*m+2*n))%mod);
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