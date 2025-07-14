// Problem: P2260 [清华集训2012] 模积和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2260
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-11 08:21:54
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 19940417ll
#define inv2 9970209
#define inv6 3323403
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

int n,m;
int calc(int n,int lim){
	int ans=0,l=1;
	while(l<=lim&&n/l){
		int r=min((n/(n/l)),lim);
		(ans+=(n/l)*(l+r)%mod*(r-l+1)%mod*inv2)%=mod;
		l=r+1;
	}
	return ans;
}
int s(int n){return n*(n+1)%mod*(2*n+1)%mod*inv6%mod;}
int calc1(int n,int m,int lim){
	int ans=0,l=1;
	while(l<=lim&&n/l&&m/l){
		int r=min({n/(n/l),m/(m/l),lim});
		(ans+=(n/l)*(m/l)%mod*(s(r)-s(l-1)+mod))%=mod;
		l=r+1;
	}
	return ans;
}
void work(){
	n=read();m=read();if(n>m)swap(n,m);
	int ans=(n*n%mod-calc(n,n)+mod)*(m*m%mod-calc(m,m)+mod)%mod;
	ans=(ans-(n*n%mod*m%mod-m%mod*calc(n,n)%mod-n%mod*calc(m,n)%mod+calc1(n,m,n)+2*mod)%mod+mod)%mod;
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
