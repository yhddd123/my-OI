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

int n,m,a[maxn];
int dp[maxn],f[maxn];
int pre[210][maxn];
int X(int u){return (a[u]);}
int Y(int u){return (-f[u]+a[u]*a[u]);}
double slope(int u,int v){
	if(X(u)==X(v)){
		if(Y(u)<Y(v))return inf;
		return -inf;
	}
	return (double)(1.0*(Y(u)-Y(v))/((X(u)-X(v))));
}
int h,t,q[maxn];

int T;
signed main(){
//		freopen("P3648_66.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=m;i++){
		h=1;t=0;q[++t]=0;
		for(int j=1;j<=n;j++){
			while(h<t&&slope(q[h],q[h+1])<=a[j])h++;
			dp[j]=f[q[h]]+a[q[h]]*(a[j]-a[q[h]]);
			pre[i][j]=q[h];
			while(h<t&&slope(q[t-1],q[t])>=slope(q[t-1],j))t--;
			q[++t]=j;
		}
		for(int j=1;j<=n;j++)f[j]=dp[j];
	}
	printf("%lld\n",dp[n]);
	for(int i=m,p=n;i>=1;i--){
		p=pre[i][p];
		printf("%lld ",p);
	}
}
