// Problem: P6791 [SNOI2020] 取石子
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6791
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-18 10:09:32
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=89;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,ans;
int f[maxn],num[maxn][maxn];
void work(){
	k=read();n=read();ans=0;
	int p=0;while(f[p+1]<=k)p++;
	for(int i=88;i;i--)if(n>f[i])n-=f[i],ans+=num[i][p];
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	f[0]=f[1]=1;for(int i=1;i<=88;i++)f[i]=f[i-1]+f[i-2];
	// cout<<f[88]<<"\n";
	num[1][1]=1;
	for(int i=2;i<=88;i++){
		num[i][i]=1;
		for(int j=1;j<=i-1;j++)num[i][j]=num[i-1][j]+num[i-2][j]-(j==i-2);
	}
	for(int i=1;i<=88;i++){
		for(int j=1;j<=88;j++)num[i][j]+=num[i][j-1];
	}
	T=read();
	while(T--)work();
}
