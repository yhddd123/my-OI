#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int h,n,s,ans=-inf;
int a[25],b[25],c[25];
int f[1<<22],dp[1<<22];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();s=(1<<n)-1;h=read();
	memset(dp,-0x3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		a[i]=read();b[i]=read();c[i]=read();
		for(int j=1;j<=s;j++){
			if((j|(1<<(i-1)))==j)f[j]+=a[i];
		}
		dp[1<<(i-1)]=c[i];
	}
	for(int i=1;i<=s;i++){
		for(int j=1;j<=n;j++){
			if((i&(1<<(j-1)))==0){
				dp[i|(1<<(j-1))]=max(dp[i|(1<<(j-1))],min(dp[i]-b[j],c[j]));
			}
		}
	}
	for(int i=1;i<=s;i++){
		if(f[i]>=h)ans=max(ans,dp[i]);
//		cout<<f[i]<<" "<<dp[i]<<"\n";
	}
	if(ans<0)printf("Mark is too tall\n");
	else printf("%lld\n",ans);
}
