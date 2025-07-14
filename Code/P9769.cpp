#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=5000010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int y,n,m,b[12];
int dp[maxn];
int q[maxn],h,t;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	y=read();n=read();m=read();
	for(int i=1;i<=m;i++)b[i]=read();
	h=t=1;
	for(int i=1;i<=y;i++){
		if(h<=t&&q[h]<i-n)h++;
		dp[i]=dp[q[h]]+1;
		for(int j=1;j<=m;j++){
			if(i%b[j]==0)dp[i]=min(dp[i],dp[i/b[j]]+1);
		}
		while(h<=t&&dp[q[t]]>=dp[i])t--;
		q[++t]=i;
//		cerr<<i<<" "<<h<<" "<<t<<" "<<dp[i]<<"\n";
	}
	printf("%lld\n",dp[y]);
}
