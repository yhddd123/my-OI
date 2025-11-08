// Problem: P10202 [湖北省选模拟 2024] 沉玉谷 / jade
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10202
// Memory Limit: 1024 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2025-11-08 12:41:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 1000000007ll
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
const int maxn=55;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
int f[maxn][maxn][maxn],g[maxn][maxn][maxn][maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int C[maxn][maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)inc(C[i][j]=C[i-1][j],C[i-1][j-1]);
	}
	for(int i=1;i<=n+1;i++){
		for(int c=0;c<=n;c++)g[i][i-1][0][c]=1;
	}
	for(int i=1;i<=n;i++){
		f[i][i][1]=1;
		g[i][i][0][a[i]]=1;
		for(int c=0;c<=n;c++)g[i][i][1][c]=1;
	}
	for(int l=2;l<=n;l++){
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			if(a[i]==a[j]){
				for(int k=0;k<=j-i-1;k++){
					inc(f[i][j][k+1],g[i+1][j-1][k][a[i]]);
				}
			}
			for(int k=0;k<=j-i+1;k++){
				inc(g[i][j][k][a[j]],g[i][j-1][k][a[j]]);
				for(int p=i-1;p<j;p++)if(a[p+1]==a[j]){
					for(int kk=max(0,k-j+p);kk<k&&kk<=p-i+1;kk++){
						for(int c=0;c<=n;c++){
							inc(g[i][j][k][c],1ll*g[i][p][kk][c]*f[p+1][j][k-kk]%mod*C[k][kk]%mod);
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++)inc(ans,g[1][n][i][0]);
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("jam.in","r",stdin);
	// freopen("jam.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}