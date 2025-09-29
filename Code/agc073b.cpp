// Problem: B - Cyclic Jump
// Contest: AtCoder - AtCoder Grand Contest 073
// URL: https://atcoder.jp/contests/agc073/tasks/agc073_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-28 22:09:46
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
const int maxn=250010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int sovle(){
	if(a[1]==a[2])return a[1];
	int d=(a[2]+a[1]-1)/a[1]-1;for(int i=2;i<=n;i++)a[i]-=a[1]*d;
	int p=1;for(int i=2;i<=n;i++)if(a[i]<a[1])p=i;
	int tmp=a[1];for(int i=1;i<p;i++)a[i]=a[i+1];a[p]=tmp;
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	return sovle()+tmp*d;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	printf("%lld\n",sovle());
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}