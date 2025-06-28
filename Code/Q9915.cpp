#include<bits/stdc++.h>
// #define int long long
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

int n,k,a[maxn],ans[maxn<<1];
bitset<maxn> f[1010],g;
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=max(1,a[i]-k);j<=min(1000,a[i]+k);j++)f[j][i+1]=1;
	}
	for(int i=1;i<=n;i++)ans[i*2]=2*min(i,n-i+1)-1;
	for(int i=1;i<n;i++)ans[i*2+1]=2*min(i,n-i);
	for(int i=1;i<=n;i++){
		auto h=g&f[a[i]];
		auto nw=g&(~h);
		for(int j=nw._Find_first();j<=i;j=nw._Find_next(j))ans[i+j-1]=i-j;
		g=h>>1;
		if(abs(a[i]-a[i-1])<=k)g[i-1]=1;
		else ans[2*i-1]=0;
		g[i]=i;
	}
	for(int i=2;i<=2*n;i+=2)printf("%d ",ans[i]);puts("");
	for(int i=3;i<=2*n;i+=2)printf("%d ",ans[i]);puts("");
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