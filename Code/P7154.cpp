#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=6010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,cur;
struct nd{
	int val,fl;
}a[maxn];
bool cmp(nd u,nd v){
	if(u.val==v.val)return u.fl>v.fl;
	return u.val<v.val;
}
int dp[2][maxn][2];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),1};
	for(int i=1;i<=n;i++)a[i+n]={read(),0};
	sort(a+1,a+n*2+1,cmp);
	dp[0][0][1]=1;
	for(int i=1;i<=2*n;i++){
		cur^=1;
		for(int j=0;j<=n;j++){
			dp[cur][j][0]=dp[cur][j][1]=0;
			if(a[i].fl){
				dp[cur][j][0]=dp[cur^1][j][0]+dp[cur^1][j][1];
				if(j)dp[cur][j][0]+=dp[cur^1][j-1][0];
				dp[cur][j][0]%=mod;
				if(j)dp[cur][j][1]=dp[cur^1][j-1][1];
			}else{
				dp[cur][j][0]=dp[cur^1][j+1][0]*(j+1)%mod;
				dp[cur][j][1]=(dp[cur^1][j+1][1]*(j+1)+dp[cur^1][j][1])%mod;
			}
		}
	}
	printf("%lld\n",(dp[cur][0][0]+dp[cur][0][1])%mod);
}
