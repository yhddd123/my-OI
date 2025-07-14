// Problem: P4948 数列求和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4948
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-03-29 10:21:22
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
using namespace std;
const int maxn=2010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a,k;
inline int ksm(int a,int b=mod-2){
	int ans=1;a%=mod,b%=(mod-1);
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
namespace sub1{
	int s[maxn];
	void sovle(){
		for(int i=0;i<=k;i++){
			s[i]=(ksm(n+1,i)*ksm(a,n+1)%mod-a+mod)%mod;
			for(int j=0;j<i;j++)(s[i]+=mod-a*C(i,j)%mod*s[j]%mod)%=mod;
			s[i]=s[i]*ksm(a-1)%mod;
		}
		printf("%lld\n",s[k]);
	}
}
namespace sub2{
	int s[maxn];
	void sovle(){
		for(int i=0;i<=k;i++){
			s[i]=ksm(n+1,i+1)+mod-1;
			for(int j=0;j<i;j++)(s[i]+=mod-C(i+1,j)%mod*s[j]%mod)%=mod;
			s[i]=s[i]*ksm(i+1)%mod;
			// cout<<s[i]<<"\n";
		}
		printf("%lld\n",s[k]);
	}
}
namespace sub3{
	void sovle(){
		int ans=0;
		for(int i=1;i<=n;i++)(ans+=ksm(i,k)*ksm(a,i))%=mod;
		printf("%lld\n",ans);
	}
}
void work(){
	n=read();a=read();k=read();
	fac[0]=1;for(int i=1;i<=k+1;i++)fac[i]=fac[i-1]*i%mod;
	inv[k+1]=ksm(fac[k+1]);for(int i=k;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	if(a>1)sub1::sovle();
	else sub2::sovle();
	// sub3::sovle();
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
