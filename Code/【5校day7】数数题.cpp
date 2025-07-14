#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int id;
int n,a[maxn];ull ans;
int f[maxn],g[maxn],mx[maxn],mn[maxn],sum[maxn],sum1[maxn];
void sovle(int l,int r){
	if(l==r){ans+=a[l]-a[l-1];return ;}
	int mid=l+r>>1;
	// cout<<l<<" "<<r<<" "<<mid<<" "<<ans<<"\n";
	mx[mid]=-inf;for(int i=mid+1;i<=r;i++)mx[i]=max(mx[i-1],a[i]);
	sum1[mid]=0;for(int i=mid+1;i<=r;i++)sum1[i]=sum1[i-1]+mx[i];
	mn[mid]=a[mid-1];for(int i=mid-1;i>=l;i--)mn[i]=min(mn[i+1],a[i-1]);
	f[mid+1]=-inf;
	for(int i=mid,val=-inf;i>=l;i--){
		val=max(val,a[i]);
		f[i]=max(f[i+1],val-a[i-1]);
	}
	g[mid]=-inf;
	for(int i=mid+1,val=inf;i<=r;i++){
		val=min(val,a[i-1]);
		g[i]=max(g[i-1],a[i]-val);
	}
	sum[r+1]=0;for(int i=r;i>mid;i--)sum[i]=sum[i+1]+g[i];
	for(int i=l;i<=mid;i++){
		int ll=mid+1,rr=r,res=mid;
		while(ll<=rr){
			int mm=ll+rr>>1;
			if(f[i]>=max(mx[mm]-mn[i],g[mm]))ll=mm+1,res=mm;
			else rr=mm-1;
		}
		ans+=f[i]*(res-mid);
		// cout<<i<<" "<<res<<"\n";
		int pos=res+1;
		ll=res+1,rr=r;
		while(ll<=rr){
			int mm=ll+rr>>1;
			if(mx[mm]-mn[i]>=g[mm])ll=mm+1,res=mm;
			else rr=mm-1;
		}
		// cout<<i<<" "<<res<<" "<<mx[res]<<" "<<mn[i]<<"\n";
		// cout<<pos<<" "<<sum1[res]-sum1[pos-1]<<" "<<mn[i]*(res-pos+1)<<"\n";
		ans+=sum1[res]-sum1[pos-1]-mn[i]*(res-pos+1);
		pos=res+1;
		ans+=sum[pos];
		// cout<<i<<" "<<ans<<" "<<pos<<" "<<sum[pos]<<"\n";
	}
	// cout<<l<<" "<<r<<" "<<mid<<" "<<ans<<"\n";
	sovle(l,mid),sovle(mid+1,r);
}
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]+=a[i-1];
	sovle(1,n);
	printf("%llu\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("sagiri.in","r",stdin);
	// freopen("sagiri.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
