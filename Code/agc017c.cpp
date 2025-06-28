// Problem: AT_agc017_c [AGC017C] Snuke and Spells
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc017_c
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-03-11 12:28:16
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=2e9;
bool mbe;

int n,q,a[maxn],ans;
int c[maxn],s[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)c[a[i]]++;
	for(int i=1;i<=n;i++)if(c[i]){
		for(int j=i;j>=i-c[i]+1&&j;j--)s[j]++;
	}
	for(int i=1;i<=n;i++)if(!s[i])++ans;
	while(q--){
		int u=read(),v=read();
		c[a[u]]--;
		if(a[u]-c[a[u]]>0)s[a[u]-c[a[u]]]--,ans+=(s[a[u]-c[a[u]]]==0);
		a[u]=v;
		if(a[u]-c[a[u]]>0)s[a[u]-c[a[u]]]++,ans-=(s[a[u]-c[a[u]]]==1);
		c[a[u]]++;
		// for(int i=1;i<=n;i++)cout<<s[i];cout<<"\n";
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