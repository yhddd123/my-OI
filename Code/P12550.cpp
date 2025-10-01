#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
int sum[maxn][3],num[maxn][3];
int dp[maxn];
void calc(int i,int j,int c){
	dp[i]=max(dp[i],dp[j-1]+sum[i][(c+1)%3]-sum[j-1][(c+1)%3]-(num[i][(c+1)%3]-num[j-1][(c+1)%3])*num[j-1][c]);
}
void work(){
	n=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		num[i][0]=num[i-1][0],num[i][1]=num[i-1][1],num[i][2]=num[i-1][2];
		num[i][s[i]-'A']=num[i-1][s[i]-'A']+1;
		sum[i][0]=sum[i-1][0],sum[i][1]=sum[i-1][1],sum[i][2]=sum[i-1][2];
		sum[i][s[i]-'A']=sum[i-1][s[i]-'A']+num[i][(s[i]-'A'+2)%3];
	}
	for(int i=1,j=1,k=1,c=s[1]-'A';i<=n;i++){
		if(i>1&&s[i]!=s[i-1]){
			if((s[i]-'A'+1)%3==s[i-1]-'A')c=s[i]-'A';
			else c=s[i-1]-'A';
		}
		while(num[i][(c+2)%3]!=num[j-1][(c+2)%3])j++;
		k=max(j,k);
		while(k<i&&s[k+1]==s[j])k++;
		dp[i]=dp[i-1];calc(i,j,c),calc(i,k+1,c);
		// cout<<i<<" "<<j<<" "<<k<<" "<<c<<" "<<dp[i]<<endl;
		// for(int p=j;p<=i;p++)cout<<s[p];cout<<"\n";
	}
	printf("%lld\n",dp[n]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}