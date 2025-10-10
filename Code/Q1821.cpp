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
const int maxn=30010;
const int inf=1e9;
bool mbe;

int n,ans;
char s[maxn],tmp[maxn];
int dp[maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	scanf("%s",tmp+1);n=strlen(tmp+1);
	for(int i=1;i<=(n+1)/2;i++)s[2*i-1]=tmp[i];
	for(int i=n;i>(n+1)/2;i--)s[2*(n-i+1)]=tmp[i];
	dp[0]=1;for(int i=1;i<n;i++){
		int mul=1;
		for(int j=i,k=i+1;j&&k<=n&&(s[j]==s[k]||s[j]=='?'||s[k]=='?');j--,k++){
			mul=mul*((s[j]=='?'&&s[k]=='?')?26:1)%mod;
			if(j&1)(dp[k]+=dp[j-1]*mul)%=mod;
		}
	}
	// for(int i=1;i<=n;i++)cout<<s[i];cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
	int mul=1;
	for(int i=n;~i;i--){
		(ans+=dp[i]*mul)%=mod;
		mul=mul*((s[i]=='?')?26:1)%mod;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}