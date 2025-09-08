// Problem: CF1043F Make It One
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1043F
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-09-08 20:34:58
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m=maxn-10,a[maxn];
int C[maxn][8];
int f[maxn];
void work(){
	n=read();
	for(int i=0;i<=m;i++){
		C[i][0]=1;for(int j=1;j<=min(i,7ll);j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	int gg=0;
	for(int i=1;i<=n;i++){
		int x=read();a[x]++;
		if(!gg)gg=x;
		else gg=__gcd(gg,x);
	}
	if(gg>1){puts("-1");return ;}
	for(int i=1;i<=m;i++){
		for(int j=2*i;j<=m;j+=i)a[i]+=a[j];
	}
	for(int ans=1;ans<=7;ans++){
		for(int i=1;i<=m;i++)f[i]=C[a[i]][ans];
		for(int i=m;i;i--){
			for(int j=2*i;j<=m;j+=i)f[i]-=f[j];
		}
		if(f[1]){printf("%lld\n",ans);break;}
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