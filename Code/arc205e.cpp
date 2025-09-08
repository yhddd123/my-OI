// Problem: E - Subset Product Problem
// Contest: AtCoder - AtCoder Regular Contest 205 (Div. 2)
// URL: https://atcoder.jp/contests/arc205/tasks/arc205_e
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2025-09-08 07:36:34
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

int n;
int mul[1<<20];
void work(){
	n=read();
	for(int i=0;i<(1<<20);i++)mul[i]=1;
	for(int i=1;i<=n;i++){
		int x=read();
		int x1=x&((1<<10)-1),x2=(x-x1)>>10;
		for(int s=0;s<(1<<10);s++)if((x1|s)==s)mul[s|(x2<<10)]=mul[s|(x2<<10)]*x%mod;
		int ans=1;for(int s=0;s<(1<<10);s++)if((s|x2)==x2)ans=ans*mul[x1|(s<<10)]%mod;
		printf("%lld\n",ans);
	}
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