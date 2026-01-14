// Problem: P13843 集合幂级数 exp（非素数模数）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13843
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-01-14 07:51:57
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ull unsigned long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline ull read(){
	ull x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
const int maxn=20;
const int inf=1e9;
bool mbe;

int n;ull a[1<<maxn],b[1<<maxn];
ull ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn],hh[1<<maxn];
void fmt(ull *a,int n,ull w){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]+=a[j]*w;
		}
	}
}
void xormul(ull *a,ull *b,ull *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt(ff[i],1<<n,1);
	for(int i=0;i<=n;i++)fmt(gg[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++){
			hh[i]=0;
			for(int j=0;j<=i;j++)hh[i]+=ff[j][s]*gg[i-j][s];
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
	for(int i=0;i<=n;i++)fmt(ff[i],1<<n,-1ull);
	for(int s=0;s<(1<<n);s++)c[s]=ff[__builtin_popcount(s)][s];
}
ull tmpf[1<<maxn],tmpg[1<<maxn],tmph[1<<maxn];
void exp(ull *a,ull *b,int n){
	b[0]=1;
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<i);s++)tmpf[s]=a[s|(1<<i)];
		for(int s=0;s<(1<<i);s++)tmpg[s]=b[s];
		xormul(tmpf,tmpg,tmph,i);
		for(int s=0;s<(1<<i);s++)b[s|(1<<i)]+=tmph[s];
	}
}
void work(){
	n=read();
	for(int s=0;s<(1<<n);s++)a[s]=read();
	exp(a,b,n);
	for(int s=0;s<(1<<n);s++)printf("%llu ",b[s]);
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