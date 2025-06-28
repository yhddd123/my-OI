// Problem: P6097 【模板】子集卷积
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6097
// Memory Limit: 1 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2024-05-12 10:07:45
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000009ll
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

int n,m;
int a[21][1<<21],b[21][1<<21],ans[21][1<<21];
void fmt(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		if(w==1){
			for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)])%=mod;
		}
		else{
			for(int s=(1<<n)-1;~s;s--)if(s&(1<<i))(a[s]+=mod-a[s^(1<<i)])%=mod;
		}
	}
}
void work(){
	n=read(),m=1<<n;
	for(int i=0;i<m;i++)a[__builtin_popcount(i)][i]=read();
	for(int i=0;i<m;i++)b[__builtin_popcount(i)][i]=read();
	for(int i=0;i<=n;i++)fmt(a[i],n),fmt(b[i],n);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<m;k++)(ans[i][k]+=a[j][k]*b[i-j][k])%=mod;
		}
	}
	for(int i=0;i<=n;i++)fmt(ans[i],n,mod-1);
	for(int i=0;i<m;i++)printf("%lld ",ans[__builtin_popcount(i)][i]);
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