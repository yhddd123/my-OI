// Problem: P7386 「EZEC-6」0-1 Trie
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7386
// Memory Limit: 500 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2024-09-04 21:53:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 18888913ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=18888915;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans,res;
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
int calc(int n,int m){return lucas(n+m+2,n+1)-1;}
void work(){
	n=read();m=read();m-=n;
	if(m<0)return ;
	ans=(lucas(n+m-1,n-1)+1+calc(n-1,m-1)+2*calc(n-2,m)+mod)%mod;
	res^=ans;
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
	
	fac[0]=1;for(int i=1;i<mod;i++)fac[i]=fac[i-1]*i%mod;
	inv[mod-1]=ksm(fac[mod-1]);for(int i=mod-2;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	T=read();
	while(T--)work();
	printf("%lld\n",res);
}
