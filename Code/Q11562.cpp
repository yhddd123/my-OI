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
const int maxn=1000010;
const int inf=1e18;
bool mbe;

int n,a[maxn];
tuple<int,int,int,int> ans;
void work(){
	n=read();ans={inf,0,0,0};
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]+=a[i-1];a[n+1]=inf;
	for(int x=0;x<n;x++){
		int y=lower_bound(a+1,a+n+1,a[x]+a[n]/3)-a;
		if(x<y&&y<n){
			int z=lower_bound(a+1,a+n+1,a[y]+(a[n]-(a[y]-a[x]))/2)-a;
			if(y<z&&z<n){
				int v1=a[y]-a[x],v2=a[z]-a[y],v3=a[n]-a[z]+a[x];
				ans=min(ans,{max({v1,v2,v3})-min({v1,v2,v3}),x,y,z});
			}
			z--;
			if(y<z&&z<n){
				int v1=a[y]-a[x],v2=a[z]-a[y],v3=a[n]-a[z]+a[x];
				ans=min(ans,{max({v1,v2,v3})-min({v1,v2,v3}),x,y,z});
			}
		}
		y--;
		if(x<y&&y<n){
			int z=lower_bound(a+1,a+n+1,a[y]+(a[n]-(a[y]-a[x]))/2)-a;
			if(y<z&&z<n){
				int v1=a[y]-a[x],v2=a[z]-a[y],v3=a[n]-a[z]+a[x];
				ans=min(ans,{max({v1,v2,v3})-min({v1,v2,v3}),x,y,z});
			}
			z--;
			if(y<z&&z<n){
				int v1=a[y]-a[x],v2=a[z]-a[y],v3=a[n]-a[z]+a[x];
				ans=min(ans,{max({v1,v2,v3})-min({v1,v2,v3}),x,y,z});
			}
		}
	}
	printf("%lld\n%lld %lld %lld\n",get<0>(ans),get<1>(ans)+1,get<2>(ans)+1,get<3>(ans)+1);
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