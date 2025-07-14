// Problem: P3657 [USACO17FEB] Why Did the Cow Cross the Road II P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3657
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-22 16:28:37
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
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n){
		tree[x]=max(tree[x],w);
		x+=lb(x);
	}
}
int que(int x){
	int res=0;
	while(x){
		res=max(res,tree[x]);
		x-=lb(x);
	}
	return res;
}
int a[maxn],b[maxn];
int val[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[read()]=i;
	for(int i=1;i<=n;i++){
		for(int j=a[i]-4;j<=a[i]+4;j++)if(j>=1&&j<=n)val[j]=que(b[j]-1);
		for(int j=a[i]-4;j<=a[i]+4;j++)if(j>=1&&j<=n)upd(b[j],val[j]+1);
	}
	printf("%lld\n",que(n));
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
