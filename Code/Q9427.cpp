#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
const int inf=2e18;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x;
}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
bool Mbe;

int n;
pii a[maxn];
int b[maxn],len;
int mn,mx;
bool check(int x){
	mn=-inf,mx=inf;
	for(int i=2;i<=n;i++){
		if(abs(b[a[i].se]-b[a[i-1].se])<=x*(a[i].fi-a[i-1].fi)){
			if(b[a[i].se]-x*a[i].fi<=mx&&b[a[i].se]+x*a[i].fi>=mn){
				mn=min(mn,b[a[i-1].se]+x*a[i-1].fi),mx=max(mx,b[a[i-1].se]-x*a[i-1].fi);
			}
		}
		else{
			if(b[a[i].se]-x*a[i].fi<=mx&&b[a[i].se]+x*a[i].fi>=mn){
				mn=b[a[i-1].se]+x*a[i-1].fi,mx=b[a[i-1].se]-x*a[i-1].fi;
			}
			else{
				// cout<<i<<" "<<mn<<" "<<mx<<" "<<a[i].fi<<" "<<a[i].se<<"\n";
				return 0;
			}
		}
	}
	return 1;
}
void work(){
	n=read();len=0;
	for(int i=1;i<=n;i++)a[i]={read(),read()},b[++len]=a[i].se;
	sort(b+1,b+len+1),len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=n;i++)a[i].se=lower_bound(b+1,b+len+1,a[i].se)-b;
	sort(a+1,a+n+1);
	int l=0,r=1e9,res=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	write(res);puts("");
	// cout<<check(r)<<"\n";
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
	
	T=read();
	while(T--)work();
}