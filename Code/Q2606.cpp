#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=4010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int n,m,p[maxn],t[maxn];
int f[maxn][maxn],g[maxn][maxn];
void work(){
	m=read();n=read();
	for(int i=0;i<=m;i++)p[i]=read();
	for(int i=1;i<=n;i++)t[i]=read();
	int sum=0;for(int i=0;i<=m;i++)sum+=p[i];
	int mul=1;for(int i=1;i<=n;i++)mul=mul*t[i]%mod;
	for(int i=0;i<=m;i++)p[i]=p[i]*ksm(sum)%mod;
	for(int i=0;i<=m;i++)f[0][i]=p[i];
	for(int i=1;i<=n;i++){
		vector<int> a(m+1);
		for(int j=0;j<=m;j++)a[j]=f[i-1][j];
		for(int j=1;j<=m;j++)(a[j]+=a[j-1])%=mod;
		for(int j=i;j<=m;j++)f[i][j]=(ksm(a[j],t[i])+(j?mod-ksm(a[j-1],t[i]):0))%mod;
	}
	int res=0;for(int i=n;i<=m;i++)(res+=f[n][i])%=mod;
	// cout<<res<<"\n";
	// for(int x=0;x<=m;x++){
		// for(int j=0;j<=m;j++)g[0][j]=0;g[0][x]=p[x];
		// for(int i=1;i<=n;i++){
			// vector<int> a(m+1),b(m+1);
			// for(int j=0;j<=m;j++)a[j]=f[i-1][j];
			// for(int j=1;j<=m;j++)(a[j]+=a[j-1])%=mod;
			// for(int j=0;j<=m;j++)b[j]=(ksm(a[j],t[i]-1)+(j?mod-ksm(a[j-1],t[i]-1):0))%mod;
			// // for(int j=0;j<=m;j++)cout<<b[j]<<" ";cout<<"\n";
			// for(int j=0;j<=m;j++)a[j]=g[i-1][j];
			// for(int j=1;j<=m;j++)(a[j]+=a[j-1])%=mod;
			// for(int j=1;j<=m;j++)(b[j]+=b[j-1])%=mod;
			// for(int j=i;j<=m;j++)g[i][j]=((a[j]+(j?mod-a[j-1]:0))*b[j]+(b[j]+(j?mod-b[j-1]:0))*(j?a[j-1]:0))%mod;
		// }
		// int ans=0;for(int i=n;i<=m;i++)(ans+=g[n][i])%=mod;
		// printf("%lld\n",ans*mul%mod);
	// }
	for(int i=n;i<=m;i++)g[n][i]=1;
	for(int i=n;i;i--){
		vector<int> a(m+1),b(m+1),pre(m+1),suf(m+1);
		for(int j=0;j<=m;j++)a[j]=f[i-1][j];
		for(int j=1;j<=m;j++)(a[j]+=a[j-1])%=mod;
		for(int j=0;j<=m;j++)b[j]=(ksm(a[j],t[i]-1)+(j?mod-ksm(a[j-1],t[i]-1):0))%mod;
		for(int j=0;j<=m;j++)pre[j]=((j?pre[j-1]:0)+b[j])%mod;
		for(int j=m;~j;j--)suf[j]=((j<m?suf[j+1]:0)+b[j]*g[i][j])%mod;
		for(int j=i-1;j<=m;j++)g[i-1][j]=(g[i][j]*pre[j]+(j<m?suf[j+1]:0))%mod;
	}
	for(int x=0;x<=m;x++)printf("%lld\n",p[x]*g[0][x]%mod*mul%mod);
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