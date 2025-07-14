// Problem: P5221 Product
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5221
// Memory Limit: 32 MB
// Time Limit: 500000 ms
// Written by yhm.
// Start codeing:2024-07-11 09:45:50
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 104857601ll
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

int n,ans=1;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int pre[maxn],cnt;
bool vis[maxn];
int mu[maxn];
void get(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1,mu[i*pre[j]]=i%pre[j]?-mu[i]:0;
			if(i%pre[j]==0)break;
		}
	}
}
int calc(int n,int lim){
	int ans=0,l=1;
	while(l<=lim&&n/l){
		int r=min(n/(n/l),lim);
		ans+=(n/l)*(n/l)*(mu[r]-mu[l-1]);
		l=r+1;
	}
	return ans;
}
int que[maxn];
void work(){
	n=read();get(n);
	for(int i=1;i<=n;i++)mu[i]+=mu[i-1];
	for(int i=1;i<=n;i++)ans=ans*ksm(i,2*n)%mod;
	for(int i=1;i<=n;i++){
		if(!que[n/i])que[n/i]=calc(n/i,n/i);
		ans=ans*ksm(ksm(i*i%mod,que[n/i]%(mod-1)))%mod;
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
