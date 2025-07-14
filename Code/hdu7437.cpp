// Problem: 博弈
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/showproblem.php?pid=7437
// Memory Limit: 524 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-24 14:30:02
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
const int maxn=10000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

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
int n,ans;
void work(){
	n=read();
	int cnt=0,sum=0;ans=1;
	for(int i=1;i<=n;i++){
		char op[3];scanf("%s",op+1);int t=read();
		sum+=t;ans=ans*fac[t]%mod*inv[t>>1]%mod;cnt+=(t&1);
	}
	ans=ans*inv[sum]%mod*fac[sum>>1]%mod;
	if(cnt>=2)printf("%lld\n",inv[2]);
	else if(cnt==1)printf("%lld\n",(1+ans)*inv[2]%mod);
	else printf("%lld\n",(mod+1-ans)*inv[2]%mod);
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
	
	fac[0]=1;for(int i=1;i<=maxn-1;i++)fac[i]=fac[i-1]*i%mod;
	inv[maxn-1]=ksm(fac[maxn-1]);for(int i=maxn-2;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	T=read();
	while(T--)work();
}
