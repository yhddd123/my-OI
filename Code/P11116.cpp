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

int n,ans=inf;
int x[maxn],p[maxn],d[maxn];
int sum[maxn];
bool vis1[maxn],vis2[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)x[i]=read(),p[i]=read(),d[i]=read(),sum[i]=sum[i-1]+(d[i]==1);
	for(int i=1;i<=n;i++){
		vis1[i]=1;
		if(x[i+1]-x[i]>p[i])break;
	}
	for(int i=n;i;i--){
		vis2[i]=1;
		if(x[i]-x[i-1]>p[i])break;
	}
	vis1[0]=vis2[n+1]=1;
	for(int i=0;i<=n;i++)if(vis1[i]&&vis2[i+1]&&x[i]+p[i]>=x[i+1]-p[i+1]){
		// cout<<i<<" "<<i-sum[i]+sum[n]-sum[i]<<"\n";
		ans=min(ans,i-sum[i]+sum[n]-sum[i]);
	}
	if(ans==inf)ans=-1;
	printf("%lld\n",ans);
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