//dp[i]=min(dp[j]+(sum[i[-sum[j]-l)^2);
//dp[i]=sum[i]^2-2sum[i]l+dp[j]+(sum[j]+l)^2-2sum[i]sum[j]
//(2sum[i])*sum[j]+(dp[i]-sum[i]^2+2sum[i]l)=(dp[j]+(sum[j]+l)^2)
//k*x+b=y
//k=2sum[i];x=sum[j];b=(dp[i]-sum[i]^2+2sum[i]l);y=(dp[j]+(sum[j]+l)^2);

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=50010;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

int n,l,sum[maxn],dp[maxn];
int h=1,t=0,q[maxn];

int X(int u){return sum[u];}
int Y(int u){return dp[u]+(sum[u]+l)*(sum[u]+l);}
double slope(int u,int v){return (double)(1.0*(Y(u)-Y(v))/(X(u)-X(v)));}

signed main(){
	n=read();l=read()+1;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+read()+1;
	q[++t]=0;
	for(int i=1;i<=n;i++){
		while(h<t&&slope(q[h],q[h+1])<=2*sum[i])h++;
		dp[i]=dp[q[h]]+(sum[i]-sum[q[h]]-l)*(sum[i]-sum[q[h]]-l);
		while(h<t&&slope(q[t-1],q[t])>=slope(q[t-1],i))t--;
		q[++t]=i;
	}
	printf("%lld",dp[n]);
}
