// Problem: P10102 [GDKOI2023 提高组] 矩阵
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10102
// Memory Limit: 1 MB
// Time Limit: 2000 ms
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
const int maxn=3010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
int d[maxn],v1[maxn],v2[maxn],v3[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)b[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)c[i][j]=read();
	srand(time(0));for(int i=1;i<=n;i++)d[i]=rand();
	for(int j=0;j<=n;j++)v1[j]=v2[j]=v3[j]=0;
	for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)(v1[k]+=d[j]*a[j][k])%=mod;
	for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)(v2[k]+=v1[j]*b[j][k])%=mod;
	for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)(v3[k]+=d[j]*c[j][k])%=mod;
	for(int i=1;i<=n;i++)if(v2[i]!=v3[i]){printf("No\n");return ;}
	printf("Yes\n");
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
	
	T=read();
	while(T--)work();
}
