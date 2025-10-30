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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int pl[maxn],pr[maxn];
int sum[maxn];
int calc(int l,int r){
	if(pr[l]>=r)return (r-l+1)*(r-l+2)/2;
	return sum[r]-sum[pr[l]]+(pr[l]-l+1)*(pr[l]-l+2)/2;
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	pl[1]=1;for(int i=2;i<=n;i++){
		if(a[i-1]<=a[i])pl[i]=pl[i-1];
		else pl[i]=i;
	}
	pr[n]=n;for(int i=n-1;i;i--){
		if(a[i+1]>=a[i])pr[i]=pr[i+1];
		else pr[i]=i;
	}
	for(int i=1;i<=n;i++)sum[i]=sum[pl[i]-1]+(i-pl[i]+1)*(i-pl[i]+2)/2;
	while(q--){
		int l=read(),r=read();
		if(l==r){puts("1");continue;}
		int ll=l+1,rr=r,res=l;
		while(ll<=rr){
			int mid=ll+rr>>1;
			if(calc(l,mid)<=calc(mid,r))res=mid,ll=mid+1;
			else rr=mid-1;
		}
		// cout<<res<<" "<<calc(l,res)<<" "<<calc(res,r)<<" "<<calc(l,res+1)<<" "<<calc(res+1,r)<<"\n";
		printf("%lld\n",min(calc(res,r),calc(l,res+1)));
	}
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