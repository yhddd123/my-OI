// Problem: P4781 【模板】拉格朗日插值
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4781
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-18 19:53:44
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

int n,k,ans;
int x[maxn],y[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int g=1,t[maxn];

// int pre[maxn],suf[maxn];
// int fac[maxn],inv[maxn];
// inline int ksm(int a,int b=mod-2){
	// int ans=1;
	// while(b){
		// if(b&1)ans=ans*a%mod;
		// a=a*a%mod;
		// b>>=1;
	// }
	// return ans;
// }
// int calc(int k,int v){
	// if(v<=k+10)return f[k][v];
	// int res=0;
	// pre[0]=1;for(int i=1;i<=k+10;i++)pre[i]=pre[i-1]*(v-i+mod)%mod;
	// suf[k+11]=1;for(int i=k+10;~i;i--)suf[i]=suf[i+1]*(v-i+mod)%mod;
	// for(int i=1;i<=k+10;i++){
		// int val=pre[i-1]*suf[i+1]%mod*f[k][i]%mod*inv[i-1]%mod*inv[k+10-i]%mod;
		// if((k+10-i)&1)(res+=mod-val)%mod;
		// else (res+=val)%=mod;
	// }
	// return res;
// }

void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read();
	// for(int i=1;i<=n;i++){
		// int mul=y[i];
		// for(int j=1;j<=n;j++)if(i!=j){
			// mul=mul*(k-x[j]+mod)%mod*ksm(x[i]-x[j]+mod)%mod;
		// }
		// (ans+=mul)%=mod;
	// }
	for(int i=1;i<=n;i++){
		g=g*(k-x[i]+mod)%mod;
		t[i]=y[i];for(int j=1;j<i;j++)t[i]=t[i]*ksm(x[i]-x[j]+mod)%mod;
		for(int j=1;j<i;j++)t[j]=t[j]*ksm(x[j]-x[i]+mod)%mod;
	}
	for(int i=1;i<=n;i++)(ans+=t[i]*ksm(k-x[i]+mod))%=mod;ans=ans*g%mod;
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
