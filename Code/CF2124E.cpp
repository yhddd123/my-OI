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

int n,a[maxn],sum[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),sum[i]=sum[i-1]+a[i];
	if(sum[n]&1){puts("-1");return ;}
	for(int i=1;i<n;i++)if(sum[i]==sum[n]/2){
		puts("1");
		for(int j=1;j<=n;j++)printf("%lld ",a[j]);puts("");
		return ;
	}
	for(int i=1;i<n;i++)if(sum[i]<sum[n]/2){
		int s=(sum[n]-sum[i]*2)/2;
		int p1=lower_bound(sum+1,sum+n+1,sum[i]+s)-sum;
		int p2=upper_bound(sum+1,sum+n+1,sum[n]-s)-sum;
		// cout<<i<<" "<<s<<" "<<p1<<" "<<p2<<"\n";
		if(p1<p2){
			puts("2");
			for(int j=1;j<=i;j++)printf("%lld ",a[j]);
			for(int j=i+1,v=s;j<=p1;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",a[j]-d);
			}
			for(int j=p1+1;j<p2;j++)printf("%lld ",a[j]);
			for(int j=p2,v=s;j<=n;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",a[j]-d);
			}
			puts("");
			for(int j=1;j<=i;j++)printf("0 ");
			for(int j=i+1,v=s;j<=p1;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",d);
			}
			for(int j=p1+1;j<p2;j++)printf("0 ");
			for(int j=p2,v=s;j<=n;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",d);
			}
			puts("");
			return ;
		}
	}
	for(int i=2;i<=n;i++)if(sum[n]-sum[i-1]<sum[n]/2){
		int s=(sum[n]-(sum[n]-sum[i-1])*2)/2;
		int p1=lower_bound(sum+1,sum+n+1,s)-sum;
		int p2=upper_bound(sum+1,sum+n+1,a[i-1]-s)-sum;
		if(p1<p2){
			puts("2");
			for(int j=1,v=s;j<=p1;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",a[j]-d);
			}
			for(int j=p1+1;j<p2;j++)printf("%lld ",a[j]);
			for(int j=p2,v=s;j<i;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",a[j]-d);
			}
			for(int j=i;j<=n;j++)printf("%lld ",a[j]);
			puts("");
			for(int j=1,v=s;j<=p1;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",d);
			}
			for(int j=p1+1;j<p2;j++)printf("0 ");
			for(int j=p2,v=s;j<i;j++){
				int d=min(a[j],v);v-=d;
				printf("%lld ",d);
			}
			for(int j=i;j<=n;j++)printf("0 ");
			puts("");
		}
	}
	puts("-1");
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