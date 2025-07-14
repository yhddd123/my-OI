#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=2e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,w[maxn],d[maxn],c[maxn];
int dp[maxn],ans=inf;
int h=1,t,q[maxn];
double X(int u){return 1.0*(w[u]);}
double Y(int u){return 1.0*(w[u]*d[u]);}
double slope(int u,int v){
	if(X(u)==X(v)){
		if(Y(u)<Y(v))return inf;
		return -inf;
	}
	return (double)(1.0*(Y(u)-Y(v))/(X(u)-X(v)));
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)w[i]=w[i-1]+read(),d[i+1]=d[i]+read();
	for(int i=1;i<=n;i++)c[i+1]=c[i]+w[i]*(d[i+1]-d[i]);
	q[++t]=0;
	for(int i=1;i<=n;i++){
		while(h<t&&slope(q[h],q[h+1])<=d[i])h++;
		dp[i]=c[n+1]-w[q[h]]*(d[i]-d[q[h]])-w[i]*(d[n+1]-d[i]);
		ans=min(ans,dp[i]);
		while(h<t&&slope(q[t-1],q[t])>=slope(q[t-1],i))t--;
		q[++t]=i;
	}
	printf("%lld\n",ans);
}
