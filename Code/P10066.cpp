// Problem: P10066 [CCO2023] Binaria
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10066
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000003ll
#define pii pair<int,int>
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

int n,k,a[maxn],ans;
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
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void work(){
	n=read();k=read();
	for(int i=1;i<=n-k+1;i++)a[i]=read();
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	int num=a[1],cnt=0;
	for(int i=1;i<=k;i++){
		bool fl=0;
		for(int j=i;j+k<=n;j+=k){
			if(a[j]-a[j+1]==1)num--;
			if(a[j]-a[j+1]){fl=1;break;}
		}
		if(!fl)++cnt;
	}
	printf("%lld\n",C(cnt,num));
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
