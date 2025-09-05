// Problem: CF2124D Make a Palindrome
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2124D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-03 22:17:20
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

int n,k,a[maxn];
int t[maxn];
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();a[n+1]=0;
	for(int i=0;i<=n;i++)t[i]=0;
	for(int i=1;i<=n;i++)t[a[i]]++;
	for(int i=1;i<=n;i++)t[i]+=t[i-1];
	int v=0;for(int i=1;i<=n;i++)if(t[i]>=k){v=i;break;}
	int num=k-t[v-1]-1;
	// cout<<v<<" "<<num<<"\n";
	for(int i=0;i<=n;i++)t[i]=0;
	n=0;for(int i=1;a[i];i++){
		if(a[i]<v)a[++n]=a[i];
		else if(a[i]==v)t[n]++;
	}
	if(!n){puts("YES");return ;}
	for(int i=1;i<=n;i++)if(a[i]!=a[n-i+1]){puts("NO");return ;}
	for(int i=0;i<=n/2;i++)num-=(i==n-i?1:2)*min(t[i],t[n-i]);
	if(num<=0)puts("YES");
	else puts("NO");
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