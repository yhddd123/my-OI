// Problem: P3455 [POI2007] ZAP-Queries
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3455
// Memory Limit: 125 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-11 08:44:59
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

int n,m,d;
int pre[maxn],cnt;
bool vis[maxn];
int mu[maxn];
void s(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;mu[i*pre[j]]=i%pre[j]?-mu[i]:0;
			if(i%pre[j]==0)break;
		}
	}
}
int calc(int n,int m,int lim){
	int ans=0,l=1;
	while(l<=lim&&n/l&&m/l){
		int r=min({n/(n/l),m/(m/l),lim});
		ans+=(n/l)*(m/l)*(mu[r]-mu[l-1]);
		l=r+1;
	}
	return ans;
}
void work(){
	n=read();m=read();d=read();n/=d,m/=d;
	printf("%lld\n",calc(n,m,max(n,m)));
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
	
	s(maxn-10);
	for(int i=1;i<=maxn-10;i++)mu[i]+=mu[i-1];
	T=read();
	while(T--)work();
}
