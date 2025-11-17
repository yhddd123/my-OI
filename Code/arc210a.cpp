// Problem: A - Always Increasing
// Contest: AtCoder - AtCoder Regular Contest 210
// URL: https://atcoder.jp/contests/arc210/tasks/arc210_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-16 20:00:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn],b[maxn];
void work(){
	n=read();q=read();
	while(q--){
		int p=read(),w=read();
		a[p]+=w;
		b[p]=max(b[p],a[p]-a[p+1]);
	}
	int sum=0;for(int i=1,v=0;i<=n;i++)v+=b[i-1]+1,sum+=v;
	printf("%lld\n",sum);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}