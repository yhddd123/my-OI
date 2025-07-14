#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1510;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,x,m,k,ans;
int p[maxn],dp[maxn];
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int inv[maxn],mul,cur;
int a[maxn][maxn],b[maxn];
void gas(){
	for(int i=1;i<=n;i++){
		int d=ksm(a[i][i],mod-2);
		a[i][i]=1;b[i]=b[i]*d%mod;
		if(i!=n)a[i][i+1]=a[i][i+1]*d%mod;
		for(int j=i+1;j<=n;j++){
			int d=a[j][i];a[j][i]=0;
			a[j][i+1]=(a[j][i+1]-d*a[i][i+1]%mod+mod)%mod;
			b[j]=(b[j]-d*b[i]%mod+mod)%mod;
		}
	}
	dp[n]=b[n];
	for(int i=n-1;i>=1;i--){
		dp[i]=(b[i]-a[i][i+1]*dp[i+1]%mod+mod)%mod;
	}
}

int T;
signed main(){
	T=read();
	inv[0]=inv[1]=1;
	for(int i=2;i<=maxn-10;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	while(T--){
		n=read();x=read();m=read();k=read();
		if(k==0){
			printf("-1\n");
			continue;
		}
		if(m==0){
			if(k==1)printf("-1\n");
			else{
				ans=0;
				while(x>0){
					if(x<n)x++;
					x-=k;
					++ans;
				}
				printf("%lld\n",ans);
			}
			continue;
		}
		memset(p,0,sizeof(p));
		mul=ksm(ksm(m+1,k),mod-2),cur=1;
		for(int i=0;i<=min(n,k);i++){
			p[i]=cur*ksm(m,k-i)%mod*mul%mod;
			cur=cur*inv[i+1]%mod*(k-i)%mod;
		}
		memset(a,0,sizeof(a));
		mul=ksm(m+1,mod-2);
		for(int i=1;i<n;i++){
			a[i][i]=1;b[i]=1;
			for(int j=0;j<=i-1;j++)a[i][i-j]=(a[i][i-j]+mod-p[j]*m%mod*mul%mod)%mod;
			for(int j=0;j<=i;j++)a[i][i+1-j]=(a[i][i+1-j]+mod-p[j]*mul%mod)%mod;
//			for(int j=1;j<=n;j++)cout<<a[i][j]<<" ";
//			cout<<"\n";
		}
		b[n]=1;a[n][n]=1;
		for(int j=0;j<=n-1;j++)a[n][n-j]=(a[n][n-j]+mod-p[j])%mod;
		gas();
		printf("%lld\n",dp[x]);
	}
}
