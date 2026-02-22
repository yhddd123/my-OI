// Problem: A - Zombie
// Contest: AtCoder - AtCoder Regular Contest 215
// URL: https://atcoder.jp/contests/arc215/tasks/arc215_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-22 20:00:11
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

int n,k,l,a[maxn],b[maxn];
void work(){
	n=read();k=read();l=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++)b[i]=(a[i+1]-a[i])/2;
	sort(b+1,b+n);
	int p1=a[1],p2=l-a[n];
	int ans=0,sum=0;
	for(int i=n-1;i;i--)if(k){
		ans=max(ans,sum+max(p1,p2)+(k-1)*(p1+p2));
		sum+=b[i],p1+=b[i],p2+=b[i];
		k--;
	}
	if(k)ans=max(ans,sum+max(p1,p2)+(k-1)*(p1+p2));
	else ans=max(ans,sum);
	printf("%lld\n",ans);
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