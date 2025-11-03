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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
int pre[maxn],suf[maxn];
bool vis[maxn];
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
vector<int> e[maxn];
void sovle(){
	// for(int i=1;i<=n;i++)vis[i]=0;vis[0]=1;
	// for(int i=1,mx=a[1];i<=n;i++,mx=max(mx,a[i])){
	// 	pre[i]=pre[i-1]+(mx==i&&i==a[i]);
	// 	if(mx==i)vis[i]=1;
	// }
	// for(int i=1;i<=n;i++)e[i].clear();clr();
	// suf[n+1]=0;for(int i=n,mn=a[n];i;i--,mn=min(mn,a[i])){
	// 	suf[i]=suf[i+1]+(mn==i&&i==a[i]);
	// 	// cout<<i<<" "<<mn<<"\n";
	// 	if(i==a[i]&&que(a[i])==1)e[mn].pb(i);
	// 	upd(a[i],1);
	// }
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)if(a[i]<i){
		// int res=pre[a[i]-1]+suf[i+1]+vis[a[i]-1]+(a[a[i]]==i&&vis[a[a[i]]]);
		// for(int j:e[a[i]])if(a[i]<j&&a[a[i]]>a[j])++res;
		int sum=0;
		int p=a[i];
		swap(a[p],a[i]);
		for(int j=1,mx=a[1];j<=n;j++,mx=max(mx,a[j]))if(mx==j&&j==a[j])++sum;
		swap(a[p],a[i]);
		// cout<<i<<" "<<a[i]<<" "<<res<<" "<<sum<<"\n";
		ans=max(ans,sum);
	}
}
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	bool fl=1;for(int i=1;i<=n;i++)fl&=(a[i]==i);
	if(fl){printf("%lld\n",n-2);return ;}
	sovle();
	for(int i=1;i<=n;i++)a[i]=n+1-a[i];
	reverse(a+1,a+n+1);
	sovle();
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("strike.in","r",stdin);
	// freopen("strike.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}