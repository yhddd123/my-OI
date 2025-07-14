// Problem: P10532 [XJTUPC2024] 筛法
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10532
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-05-21 14:50:38
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
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans;
int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
void work(){
	n=read();
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)if(gcd(i,j)==1)ans+=n/max(i,j);
	// }
	ans=n*n;
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
	
	T=1;
	while(T--)work();
}
