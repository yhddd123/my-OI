// Problem: P15001 摧毁时间线
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P15001
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-02-27 19:38:46
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
const int maxn=65;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],c[maxn],d[maxn];
int f[maxn][maxn][maxn][maxn],ans;
int v(int x){return x*x;}
int calc(int w,int x,int y,int z){return v(a[w]-b[x])+v(a[x]-c[y])+v(a[y]-d[z]);}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)d[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=i+2;j<=n+2;j++){
			f[i][i][j][i]=calc(i-1,i,i+1,j);
		}
	}
	for(int len=2;len<=n;len++){
		for(int l=1,r=l+len-1;r<=n;l++,r++){
			for(int i=r+2;i<=n+2;i++){
				for(int j=l;j<=r;j++){
					for(int k=j;k<=r;k++){
						for(int x=k+1;x<=r+1;x++){
							f[l][r][i][j]=max(f[l][r][i][j],f[l][k-1][x][j==k?l:j]+f[k+1][r][i][x==r+1?k+1:x]+calc(l-1,k,r+1,i));
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=n+2;i++){
		for(int j=1;j<=n;j++)ans=max(ans,f[1][n][i][j]);
	}
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}