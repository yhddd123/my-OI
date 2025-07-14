// Problem: P4370 [Code+#4] 组合数问题2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4370
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-07 21:22:59
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
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
double sum[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int fac[maxn],inv[maxn];
inline int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
inline double calc(int m,int n){return sum[m]-sum[n]-sum[m-n];}
priority_queue<pair<double,pii>> q;
void work(){
	n=read();k=read();
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+log2(i);
	for(int i=0;i<=n;i++)q.push({calc(n,i),{n,i}});
	while(!q.empty()&&k--){
		int a=q.top().se.fi,b=q.top().se.se;q.pop();
		((ans+=C(a,b))>=mod)&&(ans-=mod);
		if(a>b)q.push({calc(a-1,b),{a-1,b}});
	}
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
