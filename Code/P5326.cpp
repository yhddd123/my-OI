// Problem: P5326 [ZJOI2019] 开关
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5326
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-02-04 11:39:03
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
const int maxn=110;
const int maxm=50010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],p[maxn];
int f[maxn][maxm][2],ans;
int ni[maxm];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)p[i]=read(),m+=p[i];
	ni[0]=ni[1]=1;for(int i=2;i<=m;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	f[0][0][0]=1;
	for(int i=1,s=0;i<=n;s+=p[i],i++){
		for(int j=0;j<=s;j++){
			for(int o=0;o<2;o++)if(f[i-1][j][o]){
				inc(f[i][j][o],f[i-1][j][o]);
				inc(f[i][j+p[i]][o^a[i]],f[i-1][j][o]);
			}
		}
	}
	for(int i=0;i<=m;i++)inc(ans,f[n][i][1]*ni[i]%mod);
	printf("%lld\n",ans*m%mod);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}