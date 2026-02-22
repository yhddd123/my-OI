// Problem: C - Strong Surname
// Contest: AtCoder - AtCoder Regular Contest 215
// URL: https://atcoder.jp/contests/arc215/tasks/arc215_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-22 20:27:18
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

int n,a[maxn],b[maxn],c[maxn],ida[maxn],idb[maxn],idc[maxn];
bool vis[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read(),ida[i]=idb[i]=idc[i]=i;
	sort(ida+1,ida+n+1,[&](int u,int v){return a[u]<a[v];});
	sort(idb+1,idb+n+1,[&](int u,int v){return b[u]<b[v];});
	sort(idc+1,idc+n+1,[&](int u,int v){return c[u]<c[v];});
	for(int i=n,vb=n+1,vc=n+1;i>1;i--){
		vb=min(vb,b[ida[i]]);
		vc=min(vc,c[ida[i]]);
		if(a[ida[i]]>a[ida[i-1]]&&vb>b[idb[i-1]]&&vc>c[idc[i-1]]){printf("%lld\n",n-i+1);return ;}
	}
	printf("%lld\n",n);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}