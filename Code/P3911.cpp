// Problem: P3911 最小公倍数之和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3911
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-12 14:40:33
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

int n,t[maxn],ans;
int pre[maxn],cnt;
bool vis[maxn];
int mu[maxn],sum[maxn];
void init(int n){
	mu[1]=1;for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0)break;
			mu[i*pre[j]]=-mu[i];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i)sum[j]+=mu[i]*i;
	}
}
void work(){
	n=read();init(maxn-10);
	for(int i=1;i<=n;i++)t[read()]++;
	for(int i=1;i<=maxn-10;i++){
		int s=0;
		for(int j=1;j<=(maxn-10)/i;j++)s+=t[i*j]*j;
		ans+=i*sum[i]*s*s;
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
