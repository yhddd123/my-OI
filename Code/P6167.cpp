// Problem: P6167 [IOI2016] shortcut
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6167
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,c;
int s[maxn],a[maxn];
int q[maxn],l,r;
bool check(int len){
	int mx1=-inf,mx2=-inf,x1=inf,x2=-inf,x3=inf,x4=-inf;l=1,r=0;
	for(int i=1;i<=n;i++){
		if(mx1+a[i]+s[i]>len){
			while(l<=r&&a[q[l]]-s[q[l]]+a[i]+s[i]>len)mx2=max(mx2,a[q[l]]+s[q[l]]),l++;
			x1=min(x1,len-mx1-c-a[i]+s[i]);
			x2=max(x2,-len+mx2+c+a[i]+s[i]);
			x3=min(x3,len-mx2-c-a[i]+s[i]);
			x4=max(x4,-len+mx1+c+a[i]+s[i]);
		}
		mx1=max(mx1,a[i]-s[i]);
		while(l<=r&&a[q[r]]-s[q[r]]<=a[i]-s[i])r--;
		q[++r]=i;
	}
	// cout<<len<<" "<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<"\n";
	if(x1<x2||x3<x4)return 0;
	int l1=n+1,l2=1,r1=n,r2=0;
	for(int i=1;i<=n;i++){
		while(l1>1&&s[i]+s[l1-1]>=x2)l1--;
		while(r1>=l1&&s[i]+s[r1]>x1)r1--;
		while(r2<n&&s[r2+1]-s[i]<=x3)r2++;
		while(l2<=r2&&s[l2]-s[i]<x4)l2++;
        if(l1<=r1&&l2<=r2&&l1<=r2&&l2<=r1)return true;
	}
	return 0;
}
void work(){
	n=read();c=read();
	for(int i=2;i<=n;i++)s[i]=s[i-1]+read();
	for(int i=1;i<=n;i++)a[i]=read();
	int l=1,r=inf,ans=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}