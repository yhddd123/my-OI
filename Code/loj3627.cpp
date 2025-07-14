// Problem: #3627. 「2021 集训队互测」这是一道集训队胡策题
// Contest: LibreOJ
// URL: https://loj.ac/p/3627
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-12 17:00:52
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=5010;
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
int num[2][maxn],t[2][maxn];
int val[2][maxn],cnt[2][maxn];
int sum[maxn];
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)if(s[j]-'0')++num[0][i],++num[1][j];
	}
	sort(num[0]+1,num[0]+n+1,greater<int>()),sort(num[1]+1,num[1]+n+1,greater<int>());
	for(int i=1;i<=n;i++)t[0][num[0][i]]++,t[1][num[1][i]]++;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=n;i;i--)sum[i]=sum[i+1]+n-num[0][i];
	val[0][0]=1,cnt[0][0]=sum[1];
	for(int i=1,p=n,s=0,ss=t[0][n];i<=n;i++){
		while(!t[0][p])p--,ss=t[0][p];
		s+=p,t[0][p]--;
		val[0][i]=C(ss,t[0][p]),cnt[0][i]=s+sum[i+1];
	}
	for(int i=n;i;i--)sum[i]=sum[i+1]+n-num[1][i];
	val[1][0]=1,cnt[1][0]=sum[1];
	for(int i=1,p=n,s=0,ss=t[1][n];i<=n;i++){
		while(!t[1][p])p--,ss=t[1][p];
		s+=p,t[1][p]--;
		val[1][i]=C(ss,t[1][p]),cnt[1][i]=s+sum[i+1];
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(cnt[0][i]+cnt[1][j]-i*j-(n-i)*(n-j)==n*n){
				// cout<<i<<" "<<j<<" "<<cnt[0][i]<<" "<<cnt[1][j]<<" "<<val[0][i]<<" "<<val[1][j]<<"\n";
				(ans+=val[0][i]*val[1][j])%=mod;
			}
		}
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}