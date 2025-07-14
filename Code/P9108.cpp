// Problem: P9108 [PA2020] Malowanie płotu
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9108
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-09-03 19:04:35
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=10000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,mod;
int f[maxn],g[maxn],ff[maxn],gg[maxn];
int inc(int u,int v){
	((u+=v)>=mod)&&(u-=mod);
	return u;
}
int sum[maxn];
void work(){
	n=read();m=read();mod=read();
	if(m==1){puts("1");return ;}
	for(int i=1;i<=m;i++){
		f[i]=m-i+1,g[i]=i;
		ff[i]=inc(ff[i-1],f[i]),gg[i]=inc(gg[i-1],g[i]);
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++)sum[j]=inc(sum[j-1],ff[j]);
		for(int j=1;j<=m;j++){
			f[j]=(sum[m]-sum[j-1]-gg[j-1]*(m-j+1)%mod+2*mod)%mod;
		}
		for(int j=1;j<=m;j++)sum[j]=inc(sum[j-1],mod-gg[j]);
		for(int j=1;j<=m;j++){
			g[j]=(sum[j-1]+ff[j]*j)%mod;
		}
		for(int j=1;j<=m;j++){
			ff[j]=inc(ff[j-1],f[j]),gg[j]=inc(gg[j-1],g[j]);
		}
	}
	printf("%lld\n",ff[m]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
