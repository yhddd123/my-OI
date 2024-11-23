// Problem: P4783 【模板】矩阵求逆
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4783
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-15 18:56:42
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=410;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn][maxn<<1];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();a[i][i+n]=1;
	}
	for(int i=1;i<=n;i++){
		if(!a[i][i]){
			for(int j=i+1;j<=n;j++)if(a[j][i]){
				swap(a[i],a[j]);
				break;
			}
		}
		if(!a[i][i]){puts("No Solution");return ;}
		int inv=ksm(a[i][i]);
		for(int j=1;j<=n;j++)if(i!=j){
			int d=a[j][i]*inv%mod;
			for(int k=i;k<=(n<<1);k++)(a[j][k]+=mod-a[i][k]*d%mod)%=mod;
		}
		for(int j=i;j<=(n<<1);j++)a[i][j]=a[i][j]*inv%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=n+1;j<=(n<<1);j++)printf("%lld ",a[i][j]);puts("");
	}
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
	
	T=1;
	while(T--)work();
}
