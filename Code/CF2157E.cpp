// Problem: E. Adjusting Drones
// Contest: Codeforces - Codeforces Round 1066 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2157/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-23 18:07:45
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
const int maxn=600010;
const int inf=1e9;
bool mbe;

int n,k,a[maxn],ans;
int q[maxn],h,t,p[maxn];
void work(){
	n=read();k=read();ans=0;
	for(int i=1;i<=3*n;i++)a[i]=0;
	for(int i=1;i<=n;i++)a[read()]++;
	h=3*n+1,t=3*n;
	for(int i=1;i<=3*n;i++){
		int tim=i;while(h<=t&&a[i]<=k)a[i]+=q[h++],tim=p[h-1];
		if(a[i]>k){
			q[--h]=a[i]-1;p[h]=tim;
		}
		ans=max(ans,i-tim);
		// cout<<i<<" "<<tim<<" "<<ans<<" "<<h<<" "<<t<<"\n";
	}
	printf("%lld\n",ans);
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