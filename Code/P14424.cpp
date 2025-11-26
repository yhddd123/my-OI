// Problem: P14424 [JOISC 2014] 邮戳收集 / Collecting Stamps
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14424
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-11-25 22:15:01
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
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n,m;
int a[maxn],b[maxn],c[maxn],d[maxn];
int f[maxn][maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
	mems(f,0x3f);
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++)if(f[i-1][j]<=inf){
			f[i][j+1]=min(f[i][j+1],f[i-1][j]+b[i]+c[i]);
			f[i][j]=min(f[i][j],f[i-1][j]+a[i]+b[i]);
			if(j)f[i][j]=min(f[i][j],f[i-1][j]+c[i]+d[i]);
			if(j)f[i][j-1]=min(f[i][j-1],f[i-1][j]+a[i]+d[i]);
		}
		for(int j=0;j<n;j++)f[i][j+1]=min(f[i][j+1],f[i][j]+b[i]+c[i]);
		for(int j=n;j;j--)f[i][j-1]=min(f[i][j-1],f[i][j]+a[i]+d[i]);
		for(int j=0;j<=n;j++)f[i][j]+=2*j*m;
	}
	printf("%lld\n",f[n][0]+(n+1)*m);
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