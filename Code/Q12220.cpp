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
inline void write(__int128 x){static char buf[50];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=100010;
const __int128 inf=1e20;
bool mbe;

int n,k;
int g[maxn],h[maxn];
__int128 f[maxn],a[maxn];
__int128 calc(int i,int j){return f[j]+(a[i]-a[j])*(a[i]-a[j]);}
__int128 K(int i){return -2*a[i];}
__int128 B(int i){return f[i]+a[i]*a[i];}
int q[maxn],hh,tt;
void check(__int128 x){
	q[hh=tt=1]=0;
	for(int i=1;i<=n;i++){
		while(hh<tt&&calc(i,q[hh])>calc(i,q[hh+1]))hh++;
		f[i]=calc(i,q[hh])+x;g[i]=g[q[hh]]+1;
		if(hh<tt&&calc(i,q[hh])==calc(i,q[hh+1]))g[i]=max(g[i],g[q[hh+1]]+1);
		while(hh<tt&&((B(i)-B(q[tt-1]))*(K(i)-K(q[tt]))<(B(i)-B(q[tt]))*(K(i)-K(q[tt-1]))||((B(i)-B(q[tt-1]))*(K(i)-K(q[tt]))==(B(i)-B(q[tt]))*(K(i)-K(q[tt-1]))&&g[q[tt-1]]>=g[q[tt]])))tt--;
		q[++tt]=i;
	}
}
void check1(__int128 x){
	q[hh=tt=1]=0;
	for(int i=1;i<=n;i++){
		while(hh<tt&&calc(i,q[hh])>calc(i,q[hh+1]))hh++;
		f[i]=calc(i,q[hh])+x;h[i]=h[q[hh]]+1;
		if(hh<tt&&calc(i,q[hh])==calc(i,q[hh+1]))h[i]=min(h[i],h[q[hh+1]]+1);
		while(hh<tt&&((B(i)-B(q[tt-1]))*(K(i)-K(q[tt]))<(B(i)-B(q[tt]))*(K(i)-K(q[tt-1]))||((B(i)-B(q[tt-1]))*(K(i)-K(q[tt]))==(B(i)-B(q[tt]))*(K(i)-K(q[tt-1]))&&h[q[tt-1]]<=h[q[tt]])))tt--;
		q[++tt]=i;
	}
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	__int128 l=0,r=inf,res=inf;
	while(l<=r){
		__int128 mid=(l+r)/2;
		check(mid);
		if(g[n]<=k)res=mid,r=mid-1;
		else l=mid+1;
	}
	// write(res);puts("");
	check(res);
	check1(res);
	// cout<<g[n]<<" "<<h[n]<<"\n";
	puts("Yes");
	vector<int> ans;
	for(int i=n,j=n-1;i;i=j,j--){
		while(f[i]!=calc(i,j)+res)j--;
		// cout<<i<<" "<<j<<" "<<g[j]<<" "<<h[j]<<endl;
		while(h[j]+1>k||g[j]+1<k)j--;
		if(j)ans.pb(j),k--;
	}
	reverse(ans.begin(),ans.end());
	for(int u:ans)printf("%lld ",u);
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