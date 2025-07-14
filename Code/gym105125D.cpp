// Problem: D. Subarray Majority
// Contest: Codeforces - MITIT 2024 Spring Invitational Qualification
// URL: https://codeforces.com/gym/105125/problem/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-10-14 15:27:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=210;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans;
char s[maxn];
int dp[2][maxn<<1][maxn<<1],cur;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int t[4];
void work(){
	n=read();scanf("%s",s+1);
	for(int op=1;op<=3;op++){
		int op1=op%3+1,op2=op1%3+1;
		mems(dp[cur=0],0);
		dp[0][2*n+1][2*n+1]=1;
		// cout<<op<<" "<<op1<<" "<<op2<<"\n";
		for(int i=1;i<=n;i++){
			mems(dp[i&1],0);
			for(int s1=0;s1<=2*n+1;s1++){
				for(int s2=0;s2<=2*n+1;s2++)if(dp[cur][s1][s2]){
					if(max(s1,s2)<n)continue;
					// cout<<i-1<<" "<<ss<<" "<<s1<<" "<<s2<<" "<<dp[cur][ss][s1][s2]<<endl;
					if(s[i]-'0'==op||s[i]=='?'){
						inc(dp[i&1][min(s1+1,2*n+1)][min(s2+1,2*n+1)],dp[cur][s1][s2]);
					}
					if(s[i]-'0'==op1||s[i]=='?'){
						if(!s1||!s2)continue;
						inc(dp[i&1][min(s1,n)-1][s2==2*n+1?2*n+1:s2-1],dp[cur][s1][s2]);
					}
					if(s[i]-'0'==op2||s[i]=='?'){
						if(!s1||!s2)continue;
						inc(dp[i&1][s1==2*n+1?2*n+1:s1-1][min(s2,n)-1],dp[cur][s1][s2]);
					}
				}
			}
			cur^=1;
		}
		for(int s1=0;s1<=2*n+1;s1++){
			for(int s2=0;s2<=2*n+1;s2++){
				if(max(s1,s2)<n)continue;
				if(s1==2*n+1||s2==2*n+1)continue;
				inc(ans,dp[n&1][s1][s2]);
			}
		}
	}
	// cout<<ans<<"\n";
	for(int i=1;i<=n;i++)if(s[i]!='?')t[s[i]-'0']++;
	if(!t[1])(ans+=ksm(2,n-t[2]-t[3]))%=mod;
	if(!t[2])(ans+=ksm(2,n-t[1]-t[3]))%=mod;
	if(!t[3])(ans+=ksm(2,n-t[1]-t[2]))%=mod;
	if(!t[1]&&!t[2])ans--;
	if(!t[1]&&!t[3])ans--;
	if(!t[2]&&!t[3])ans--;
	ans+=mod,ans%=mod;
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("majority.in","r",stdin);
	// freopen("majority.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
