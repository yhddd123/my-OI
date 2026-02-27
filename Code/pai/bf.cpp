#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
void add(int &x,int v){((x+=v)>=MOD)&&(x-=MOD);}
int n,ok[305][305][305],dp[305][305][305],res;
char s[305];
int main(){
	scanf("%s",s+1);n=strlen(s+1);ok[0][0][0]=1;
	for(int i=1;i<=n;i++)for(int j=n;~j;j--)for(int k=n;~k;k--){
		ok[i][j][k]|=ok[i-1][j][k];
		ok[i][j][k]|=ok[i][j+1][k];
		ok[i][j][k]|=ok[i][j][k+1];
		if(j&&i>=2&&(s[i]=='0'||s[i-1]=='0'))ok[i][j][k]|=ok[i-2][j-1][k];
		if(k&&i>=2&&(s[i]=='1'||s[i-1]=='1'))ok[i][j][k]|=ok[i-2][j][k-1];
		if(j&&s[i]=='0')ok[i][j][k]|=ok[i-1][j-1][k+1];
		if(k&&s[i]=='1')ok[i][j][k]|=ok[i-1][j+1][k-1];
	}
	dp[n][0][0]=1;
	for(int i=n;i;i--)for(int j=0;j<=n;j++)for(int k=0;k<=n;k++){
		add(dp[i-1][j][k],dp[i][j][k]);
		if(s[i]=='0')add(dp[i][j][k+1],dp[i][j][k]);
		if(s[i]=='1')add(dp[i][j+1][k],dp[i][j][k]);
	}
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)for(int k=0;k<=n;k++)
		if(ok[i][j][k])add(res,dp[i][j][k]);
	add(res,MOD-1);printf("%d\n",res);
	return 0;
}
