// Problem: P1390 公约数的和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1390
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-12 08:09:31
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
const int maxn=20000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans;
int pre[maxn],cnt;
bool vis[maxn];
int mu[maxn];
void init(int n){
	mu[1]=1;for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1,mu[i*pre[j]]=i%pre[j]?-mu[i]:0;
			if(i%pre[j]==0)break;
		}
	}
	for(int i=1;i<=n;i++)mu[i]+=mu[i-1];
}
int calc(int n,int lim){
	int ans=0,l=1;
	while(l<=lim){
		int r=n/(n/l);
		ans+=(mu[r]-mu[l-1])*(n/l)*(n/l);
		l=r+1;
	}
	return ans;
}
int que[maxn];
void work(){
	n=read();init(n);
	for(int i=1;i<=n;i++){
		if(!que[n/i])que[n/i]=calc(n/i,n/i);
		ans+=i*que[n/i];
	}
	printf("%lld\n",(ans-n*(n+1)/2)/2);
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
