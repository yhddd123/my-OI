// Problem: C - Fair Coin Partition
// Contest: AtCoder - AtCoder Regular Contest 210
// URL: https://atcoder.jp/contests/arc210/tasks/arc210_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-16 20:31:42
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
const int maxn=200100;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],b[maxn];
int ans[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=(b[i-1]+a[i])/10;
	for(int i=1;i<=n+10;i++)ans[i]=0;
	for(int i=n,del=0;i;i--,del=del*10){
		if(del){
			int d=min(del,a[i]);
			a[i]-=d,del-=d;
		}
		if(!del){
			int d=(b[i-1]+a[i])/m;
			ans[i]=d;
			del=max(0ll,d*m-a[i]);
		}
	}
	for(int i=1;i<=n+10;i++){
		int d=ans[i]/10;
		ans[i]%=10;ans[i+1]+=d;
	}
	int p=n+10;while(p&&!ans[p])p--;
	if(!p)puts("0");
	else{
		
	for(int i=p;i;i--)printf("%lld",ans[i]);puts("");
	}
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