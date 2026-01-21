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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,ans,a[maxn];
int sum[maxn];
int lsh[maxn],len;
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void clr(){
	for(int i=1;i<=n;i++)tree[i]=0;
}
int val[maxn],tim[maxn];
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	bool fl=1;for(int i=1;i<=n;i++)fl&=(a[i]==0);
	if(fl){puts("0");return ;}
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	if(sum[n]<=0){puts("-1");return ;}
	int p=0;for(int i=1;i<=n;i++)if(sum[i]<sum[p])p=i;
	rotate(a+1,a+p+1,a+n+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	len=0;for(int i=1;i<=n;i++)lsh[++len]=sum[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<n;i++){
		int p=lower_bound(lsh+1,lsh+len+1,sum[i])-lsh;
		ans+=i-1-que(p);
		upd(p,1);
	}
	clr();
	sort(sum+1,sum+n);
	for(int i=1;i<=n;i++)a[i]=sum[i]-sum[i-1];
	// if(a[n]>=0){
		// printf("%lld\n",ans);
		// return ;
	// }
	// cout<<ans<<"\n";
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)a[i-1]=a[i];a[n]=0;
	while(ans<=5e6){
		int lst=p,fl=0;
		while(a[p]>=0){
			p=(p+1)%n;
			if(p==lst){fl=1;break;}
		}
		if(fl)break;
		++ans;
		int p1=(p+n-1)%n,p2=(p+1)%n;
		a[p1]+=a[p],a[p2]+=a[p],a[p]=-a[p];
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