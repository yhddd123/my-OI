// Problem: E - Sequence 3
// Contest: AtCoder - FPS 24: 24 Problems on Formal Power Series
// URL: https://atcoder.jp/contests/fps-24/tasks/fps_24_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-13 19:12:24
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
const int maxn=310;
const int inf=1e9;
bool mbe;

int n,m;
int f[maxn][maxn],C[maxn][maxn];
void work(){
	n=read();m=read();
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=n;j++)if(f[i-1][j]){
			for(int k=0;j+k<=n&&k<=i;k++)(f[i][j+k]+=C[j+k][j]*f[i-1][j])%=mod;
		}
	}
	printf("%lld\n",f[m][n]);
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