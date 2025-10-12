// Problem: A - Bitwise OR Game
// Contest: AtCoder - AtCoder Regular Contest 208 (Div. 2)
// URL: https://atcoder.jp/contests/arc208/tasks/arc208_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-12 20:00:15
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

int n,a[maxn];
bool vis[30];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int s=0;
	for(int i=1;i<=n;i++)s^=a[i];
	for(int j=0;j<30;j++)vis[j]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<30;j++)if(a[i]&(1<<j))vis[j]=1;
	}
	for(int j=0;j<30;j++)if(vis[j])s^=1<<j;
	if(s)puts("Alice");
	else puts("Bob");
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