// Problem: P3327 [SDOI2015] 约数个数和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3327
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-11 20:27:09
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
const int maxn=50010;
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
int pre[maxn],cnt;
bool vis[maxn];
int mu[maxn],sum[maxn];
int calc1(int n){
	int ans=0,l=1;
	while(l<=n){
		int r=n/(n/l);
		ans+=(n/l)*(r-l+1);
		l=r+1;
	}
	return ans;
}
void init(int n){
	mu[1]=1;for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1,mu[i*pre[j]]=i%pre[j]?-mu[i]:0;
			if(i%pre[j]==0)break;
		}
	}
	for(int i=2;i<=n;i++)mu[i]+=mu[i-1];
	for(int i=1;i<=n;i++)sum[i]=calc1(i);
}
int calc(int n,int m,int lim){
	int ans=0,l=1;
	while(l<=lim&&n/l){
		int r=min({n/(n/l),m/(m/l),lim});
		ans+=sum[n/l]*sum[m/l]*(mu[r]-mu[l-1]);
		l=r+1;
	}
	return ans;
}
void work(){
	n=read();m=read();if(n>m)swap(n,m);
	printf("%lld\n",calc(n,m,m));
	
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
	
	init(maxn-10);
	T=read();
	while(T--)work();
}
