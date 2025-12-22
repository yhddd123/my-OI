// Problem: A - Divide Grid
// Contest: AtCoder - AtCoder Grand Contest 075
// URL: https://atcoder.jp/contests/agc075/tasks/agc075_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-12-21 20:05:12
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=510;
const int inf=1e9;
bool mbe;

int n;
int a[maxn][maxn],f[maxn][maxn];
void work(){
	n=read();
	if(n&1){
		for(int i=2;i<=n;i+=2){
			for(int j=1;j<=n-i+1;j++)a[i-1][j]=1;
			for(int j=n-i+2;j<=n;j++)a[i-1][j]=0;
			for(int j=1;j<=n-i+1;j++)a[i][j]=1;
			for(int j=n-i+2;j<=n;j++)a[i][j]=0;
		}
		for(int i=1;i<=n;i++)a[n][i]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)cout<<a[i][j];cout<<"\n";
		}
		// for(int o=0;o<2;o++){
			// int ans=0;
			// for(int i=1;i<=n;i++){
				// for(int j=1;j<=n;j++){
					// f[i][j]=f[i-1][j]+f[i][j-1];
					// if(a[i][j]==o)ans+=f[i][j],f[i][j]++;
				// }
			// }
			// cout<<ans<<"\n";
		// }
	}
	else{
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=n;j++)putchar('0');puts("");
		}
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=n;j++)putchar('1');puts("");
		}
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