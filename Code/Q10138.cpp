#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
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
const int maxn=5000010;
const int inf=1e9;
bool mbe;

int n,k,a[maxn];
int f[maxn];
vector<bool> dp[maxn];
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)dp[i].clear(),dp[i].resize(k+1);
	dp[1][0]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<=k;j++)if(dp[i][j]){
			int l=a[i]+j-2*min(a[i],j),r=a[i]+j-2*max(0,a[i]+j-k);
			if(l<=r){
				f[l]++;
				if(r+2<=k)f[r+2]--;
			}
		}
		for(int j=2;j<=k;j++)f[j]+=f[j-2];
		for(int j=0;j<=k;j++)if(f[j])dp[i+1][j]=1,f[j]=0;
	}
	if(dp[n][a[n]]){
		puts("YES");
		dp[n].clear(),dp[n].resize(k);
		for(int i=0;i<a[n];i++)dp[n][i]=1;
		for(int i=n-1,jj=a[n];i;i--){
			int p=0;
			for(int j=0;j<=k;j++)if(dp[i][j]){
				int l=a[i]+j-2*min(a[i],j),r=a[i]+j-2*max(0,a[i]+j-k);
				if(l<=jj&&jj<=r&&!((jj-l)&1)){p=j;break;}
			}
			int x=(a[i]+p-jj)/2,y=a[i]-x;
			// cout<<i<<" "<<p<<" "<<x<<" "<<y<<"\n";
			dp[i].clear();dp[i].resize(k);
			for(int j=0;j<k;j++)dp[i][j]=dp[i+1][j];
			for(int j=0;j<k;j++)if(dp[i][j]&&y)dp[i][j]=0,y--;
			for(int j=0;j<k;j++)if(!dp[i][j]&&!dp[i+1][j]&&x)dp[i][j]=1,x--;
			jj=p;
		}
		for(int i=1;i<=n;i++){
			for(int j=0;j<k;j++)printf("%d",(int)dp[i][j]);puts("");
		}
	}
	else puts("NO");
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