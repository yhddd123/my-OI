// Problem: P10322 高洁（Purity）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10322
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-19 09:15:30
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
const int maxn=65;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,d,ans;
vector<pii> p;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int get(int k){
	int val=1;
	for(auto [a,b]:p)val=val*ksm(a,(b+k-1)/k);
	return val;
}
int f[maxn],pre[maxn],suf[maxn],fac[maxn],inv[maxn];
int sovle(int n,int k){
	for(int i=1;i<=k+2;i++)f[i]=(f[i-1]+ksm(i,k))%mod;
	if(n<=k+2)return f[n];
	pre[0]=1;for(int i=1;i<=k+2;i++)pre[i]=pre[i-1]*((n-i)%mod)%mod;
	suf[k+3]=1;for(int i=k+2;i;i--)suf[i]=suf[i+1]*((n-i)%mod)%mod;
	int ans=0;
	for(int i=1;i<=k+2;i++){
		int p=pre[i-1]*suf[i+1]%mod,q=inv[i-1]*(((k+2-i)&1)?mod-1:1)%mod*inv[k+2-i]%mod;
		(ans+=p*q%mod*f[i])%=mod;
	}
	return ans;
}
int calc(int p,int k){return ksm(p,k)*sovle(n/p,k)%mod;}
void work(){
	n=read();d=read();ans=0;p.clear();
	for(int i=2;i*i<=d;i++)if(d%i==0){
		int cnt=0;
		while(d%i==0)d/=i,++cnt;
		p.push_back({i,cnt});
	}
	if(d>1)p.push_back({d,1});
	for(int i=1;i<=60;i++){
		(ans+=calc(get(i),i+1))%=mod;
		if(i>1)(ans+=mod-calc(get(i-1),i+1))%=mod;
	}
	(ans+=mod-calc(get(60),1))%=mod;
	n%=mod;(ans+=n*(n+1)/2)%=mod;
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
	
	T=read();
	fac[0]=1;for(int i=1;i<=64;i++)fac[i]=fac[i-1]*i%mod;
	inv[64]=ksm(fac[64]);for(int i=63;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	while(T--)work();
}
