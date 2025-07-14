#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000003
using namespace std;
const int maxn=15;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,k,m,len,ans;
char c[maxn][55];
int dp[55][1<<maxn],f[55][26];
void sovle(){
	n=read();k=read();m=(1<<n)-1;ans=0;
	for(int i=0;i<n;i++)scanf("%s",c[i]+1);
	len=strlen(c[1]+1);
	memset(dp,0,sizeof(dp));
	memset(f,0,sizeof(f));
	dp[0][m]=1;
	for(int i=0;i<n;i++){
		for(int j=1;j<=len;j++){
			if(c[i][j]=='?'){
				for(int l=0;l<26;l++)f[j][l]|=(1<<i);
			}
			else f[j][c[i][j]-'a']|=(1<<i);
		}
	}
	for(int i=0;i<len;i++){
		for(int j=0;j<=m;j++){
			if(!dp[i][j])continue;
			for(int l=0;l<26;l++)dp[i+1][j&f[i+1][l]]+=dp[i][j],dp[i+1][j&f[i+1][l]]%=mod;
		}
	}
	for(int i=0;i<=m;i++){
		if(__builtin_popcount(i)==k)ans+=dp[len][i],ans%=mod;
	}
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--)sovle();
}
