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
const int maxn=1010;
const int inf=1e9;
bool mbe;

int n,m,mod,ans;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int C[maxn][maxn];
void init(int n){
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int f[maxn][maxn];
void work(){
	n=read();m=read();ans=n*ksm(m,n)%mod;
	for(int k=1;k<n;k++){
		int lim=min(m,n/(k+1)+1);
		for(int j=0;j<=lim;j++)f[0][j]=1;
		for(int i=0;i<=n;i++)f[i][lim+1]=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=lim;j++){
				f[i][j]=f[i-1][j]*(m-j)%mod;
				if(i>=k+1)(f[i][j]+=mod-f[i-k-1][j+1]*C[i-1][k]%mod*(m-j)%mod)%=mod;
				// cout<<i<<" "<<j<<" "<<f[i][j]<<"\n";
			}
		}
		// cout<<k<<" "<<f[n][0]<<"\n";
		(ans+=mod-f[n][0])%=mod;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();mod=read();init(maxn-10);
	while(T--)work();
}