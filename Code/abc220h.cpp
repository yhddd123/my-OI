// Problem: AT_abc220_h [ABC220H] Security Camera
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc220_h
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-28 08:46:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,m,ans;
int e1[1<<maxn],e2[1<<maxn];
int dp1[1<<maxn],dp2[1<<maxn];
int e[maxn<<1],to[1<<maxn];
int f[1<<maxn],g[1<<maxn];
void fmtor(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))a[s]+=a[s^(1<<i)]*w;
	}
}
void fmtand(int *a,int n,int w){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))a[s^(1<<i)]+=a[s]*w;
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		if(u>v)swap(u,v);
		if(v<n/2)e1[(1<<u)|(1<<v)]++;
		else if(u>=n/2)e2[(1<<u-n/2)|(1<<v-n/2)]++;
		else e[v]|=1<<u;
	}
	fmtor(e1,n/2),fmtor(e2,n-n/2);
	for(int s=0;s<(1<<n/2);s++)dp1[s]=e1[s]&1;
	for(int s=0;s<(1<<n-n/2);s++)dp2[s]=e2[s]&1;
	for(int s=0;s<(1<<n/2);s++){
		for(int i=n/2;i<n;i++)if(__builtin_parity(s&e[i]))to[s]|=1<<i-n/2;
	}
	for(int x=0;x<2;x++){
		for(int y=0;y<2;y++){
			for(int s=0;s<(1<<n-n/2);s++)f[s]=0;
			for(int s=0;s<(1<<n/2);s++)f[to[s]]+=(dp1[s]==x);
			for(int s=0;s<(1<<n-n/2);s++)g[s]=(dp2[s]==y);
			// for(int s=0;s<(1<<n-n/2);s++)cout<<f[s]<<" ";cout<<"\n";
			// for(int s=0;s<(1<<n-n/2);s++)cout<<g[s]<<" ";cout<<"\n";
			fmtand(f,n-n/2,1),fmtand(g,n-n/2,1);
			for(int s=0;s<(1<<n-n/2);s++)f[s]=f[s]*g[s];
			fmtand(f,n-n/2,-1);
			// for(int s=0;s<(1<<n-n/2);s++)cout<<f[s]<<" ";cout<<"\n";
			for(int s=0;s<(1<<n-n/2);s++)if((__builtin_parity(s)^x^y)==(m&1))ans+=f[s];
			// cout<<ans<<"\n";
		}
	}
	printf("%lld\n",ans);
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