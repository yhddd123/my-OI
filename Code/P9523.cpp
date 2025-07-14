#include<bits/stdc++.h>
#define int unsigned long long
#define ls nd<<1
#define rs nd<<1|1
using namespace std;
const int maxn=2510;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a,b,c;
char s[maxn];
int hsh[maxn],pw[maxn],bas=31;
int get(int l,int r){
	return hsh[r]-hsh[l-1]*pw[r-l+1];
}
int dp[maxn][maxn],pre[maxn][maxn];
unordered_map<int,int> mp;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();scanf("%s",s+1);
	a=read();b=read();c=read();
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas;
	for(int i=1;i<=n;i++)hsh[i]=hsh[i-1]*bas+(s[i]-'a'+1);
	for(int len=1;len<=n;len++){
		mp.clear();
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			if(i>=len+1)mp[get(i-len,i-1)]=i-len;
			pre[i][len]=mp[get(i,j)];
		}
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++)dp[i][i]=a;
	for(int len=1;len<n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			dp[i-1][j]=min(dp[i-1][j],dp[i][j]+a);
			dp[i][j+1]=min(dp[i][j+1],dp[i][j]+a);
			int tim=1,p=pre[i][len];
			while(p){
				++tim;
				dp[p][j]=min(dp[p][j],dp[i][j]+b+tim*c+(j-p+1-len*tim)*a);
				p=pre[p][len];
			}
		}
	}
	printf("%lld\n",dp[1][n]);
}
