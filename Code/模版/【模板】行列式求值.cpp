// Problem: P7112 【模板】行列式求值
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7112
// Memory Limit: 64 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-08-07 16:14:18
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=610;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,mod,ans=1;
int a[maxn][maxn];
void work(){
	n=read();mod=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			while(a[i][i]){
				int d=a[j][i]/a[i][i];
				for(int k=i;k<=n;k++)(a[j][k]+=mod-a[i][k]*d%mod)%=mod;
				swap(a[i],a[j]),ans=-ans;
			}
			swap(a[i],a[j]),ans=-ans;
		}
	}
	(ans+=mod)%=mod;
	for(int i=1;i<=n;i++)ans=ans*a[i][i]%mod;
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
