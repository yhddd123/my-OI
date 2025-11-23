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

int n,k,a,b;
bool check(int x){
	int num=0;
	for(int i=1;i<=min(n,2000000ll);i++){
		int lim=min(n-i,(int)((x-2*b*i-(__int128)a*i*i)/(2*a*i)));
		num+=lim;
		if(num>=k)return 1;
	}
	return 0;
}
void work(){
	n=read();k=read();a=read();b=read();
	int l=1,r=5e18,res=r;
	while(l<=r){
		int mid=((__int128)l+r)>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	int g=__gcd(res,a);
	res/=g,a/=g;
	printf("%lld %lld\n",res,a);
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