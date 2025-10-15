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
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn],b[maxn];
int ans[maxn];
int f[maxn][maxn],g[maxn][maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+n+1);
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++)if(f[i-1][j]){
			(f[i][j]+=f[i-1][j])%=mod;
			if(a[i]>b[j+1])(f[i][j+1]+=f[i-1][j])%=mod;
		}
	}
	g[n+1][0]=1;
	for(int i=n;i;i--){
		for(int j=0;j<=n-i;j++)if(g[i+1][j]){
			(g[i][j]+=g[i+1][j])%=mod;
			if(a[i]<b[n-j])(g[i][j+1]+=g[i+1][j])%=mod;
		}
	}
	for(int i=0,p=0;i<=n;i++){
		while(p<=n&&a[p+1]<b[i])p++;
		for(int j=0;j<=p&&j<=i;j++){
			(ans[i]+=f[p][j]*g[p+1][n-p-i+j])%=mod;
		}
	}
	// for(int i=0;i<=n;i++)printf("%lld ",ans[i]);puts("");
	for(int i=1;i<=n;i++)(ans[i]+=ans[i-1])%=mod;
	q=read();
	while(q--){
		int l=read(),r=read();
		printf("%lld\n",(ans[r]+mod-(!l?0:ans[l-1]))%mod);
	}
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