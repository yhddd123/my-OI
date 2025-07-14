#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=3010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int q[maxn],h,t;
int f[maxn],dp[maxn];
double X(int u){return 1.0*a[u];}
double Y(int u){return 1.0*(f[u]+a[u]*a[u]);}
double slope(int u,int v){
	if(X(u)==X(v)){
		if(Y(u)<Y(v))return inf;
		return -inf;
	}
	return (double)((Y(u)-Y(v))/(X(u)-X(v)));
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read()+a[i-1];
	for(int i=1;i<=n;i++)f[i]=a[i]*a[i];
	for(int i=2;i<=m;i++){
		h=1;t=0;q[++t]=i-1;
		for(int j=i;j<=n;j++){
			while(h<t&&slope(q[h],q[h+1])<=2*a[j])h++;
			dp[j]=f[q[h]]+(a[j]-a[q[h]])*(a[j]-a[q[h]]);
			while(h<t&&slope(q[t-1],q[t])>=slope(q[t-1],j))t--;
			q[++t]=j;
		}
		for(int j=1;j<=n;j++)f[j]=dp[j];
	}
	printf("%lld\n",m*dp[n]-a[n]*a[n]);
}
