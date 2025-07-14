// Problem: P3807 【模板】卢卡斯定理/Lucas 定理
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3807
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-04 22:00:59
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
const int maxn=100010;

int n,m,mod;
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){
	if(m<n)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int lucas(int m,int n){
	if(!n)return 1;
	return C(m%mod,n%mod)*lucas(m/mod,n/mod)%mod;
}
void work(){
	n=read();m=read();mod=read();
	fac[0]=1;for(int i=1;i<mod;i++)fac[i]=fac[i-1]*i%mod;
	inv[mod-1]=ksm(fac[mod-1]);for(int i=mod-2;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	printf("%lld\n",lucas(n+m,n));
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
