#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int dp[maxn],f[maxn];
int d[maxn],a[maxn],s[maxn];
int q[maxn],h,t;
db X(int u){return a[u];}
db Y(int u){return f[u]+s[u];}
db slope(int u,int v){
	return 1.0*(Y(u)-Y(v))/(X(u)-X(v));
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++){
		d[i]=read();a[i]=read();
		s[i]=s[i-1]+a[i]*d[i];
		a[i]+=a[i-1];
	}
	d[++n]=m;a[n]=a[n-1];s[n]=s[n-1];
	for(int i=1;i<=n;i++)f[i]=d[i]*a[i]-s[i];
	for(int tt=2;tt<=4;tt++){
//		cout<<tt<<"\n";
		q[h=1]=0;t=0;
		for(int i=1;i<=n;i++){
			while(h<t&&slope(q[h],q[h+1])<=d[i])h++;
			int j=q[h];
			dp[i]=f[j]+d[i]*(a[i]-a[j])-s[i]+s[j];
//			cout<<i<<" "<<j<<" "<<dp[i]<<"\n";
			while(h<t&&slope(q[t-1],q[t])>=slope(q[t-1],i))t--;
			q[++t]=i;
		}
		for(int i=1;i<=n;i++)f[i]=dp[i];
	}
	printf("%lld\n",dp[n]);
}
