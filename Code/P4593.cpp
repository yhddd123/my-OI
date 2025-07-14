// Problem: P4593 [TJOI2018] 教科书般的亵渎
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4593
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-19 08:33:43
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
const int maxn=55;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,a[maxn],ans;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int f[maxn],pre[maxn],suf[maxn],fac[maxn],inv[maxn];
int calc(int n){
	if(n<=k+2)return f[n];
	pre[0]=1;for(int i=1;i<=k+2;i++)pre[i]=pre[i-1]*((n-i)%mod)%mod;
	suf[k+3]=1;for(int i=k+2;i;i--)suf[i]=suf[i+1]*((n-i)%mod)%mod;
	int ans=0;
	for(int i=1;i<=k+2;i++){
		int p=pre[i-1]*suf[i+1]%mod,q=inv[i-1]*(((k+2-i)&1)?mod-1:1)%mod*inv[k+2-i]%mod;
		(ans+=f[i]*p%mod*q)%=mod;
	}
	return ans;
}
void work(){
	n=read();m=read();k=m+1;ans=0;
	for(int i=1;i<=m;i++)a[i]=read();
	sort(a+1,a+m+1);
	for(int i=1;i<=k+2;i++)f[i]=(f[i-1]+ksm(i,k))%mod;
	fac[0]=1;for(int i=1;i<=k+2;i++)fac[i]=fac[i-1]*i%mod;
	inv[k+2]=ksm(fac[k+2]);for(int i=k+1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=0;i<=m;i++){
		int val=calc(n-a[i]);
		for(int j=i+1;j<=m;j++)(val+=mod-ksm(a[j]-a[i],k))%=mod;
		(ans+=val)%=mod;
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
	
	T=read();
	while(T--)work();
}
