#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=10010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,p;
int dp[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();p=read();
	while(n--){
		int vv=read(),ww=read(),d=read();
		for(int i=1;i<=d;i*=2){
			int v=vv*i,w=ww*i;
			for(int k=p;k>=v;k--)dp[k]=max(dp[k],dp[k-v]+w);
			d-=i;
		}
		if(d){
			int v=vv*d,w=ww*d;
			for(int k=p;k>=v;k--)dp[k]=max(dp[k],dp[k-v]+w);
		}
	}
	while(m--){
		int a=read(),b=read(),c=read();
		for(int k=p;k>=0;k--){
			for(int j=0;j<=k;j++){
				int w=a*j*j+b*j+c;
				dp[k]=max(dp[k],dp[k-j]+w);
			}
		}
	}
	printf("%lld\n",dp[p]);
}
