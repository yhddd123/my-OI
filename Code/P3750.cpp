#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 100003
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],num,ans;
vector<int> p[maxn];
int dp[maxn],inv[maxn];
void work(){
	n=read();m=read();
	inv[1]=1;for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i)p[j].push_back(i);
	}
	for(int i=n;i>=1;i--)if(a[i]){
		for(int j:p[i])a[j]^=1;
		++num;
	}
	if(num<=m)ans=num;
	else{
		dp[n]=1;
		for(int i=n-1;i>m;i--)dp[i]=((n-i)*(dp[i+1]+1)%mod*inv[i]%mod+1)%mod;
		for(int i=num;i>m;i--)ans+=dp[i],ans%=mod;
		ans+=m,ans%=mod;
	}
	for(int i=1;i<=n;i++)ans*=i,ans%=mod;
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
