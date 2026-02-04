// Problem: P4980 【模板】Pólya 定理
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4980
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-02-04 09:09:54
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int n,ans;
int phi(int n){
	int ans=n;
	for(int i=2;i*i<=n;i++)if(n%i==0){
		ans-=ans/i;
		while(n%i==0)n/=i;
	}
	if(n!=1)ans-=ans/n;
	return ans;
}
void work(){
	n=read();ans=0;
	for(int i=1;i*i<=n;i++)if(n%i==0){
		(ans+=phi(i)*ksm(n,n/i))%=mod;
		if(i*i!=n)(ans+=phi(n/i)*ksm(n,i))%=mod;
	}
	printf("%lld\n",ans*ksm(n)%mod);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}