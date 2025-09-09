#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl;
}
const int maxn=110;
bool mbe;

int n,d,ans;
int a[maxn][maxn][3];
void work(){
	n=read();d=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<n;j++){
			for(int k=0;k<d;k++)a[i][j][k]=read();
		}
		for(int j=n;j;j--){
			for(int k=0;k<d;k++)a[i][j][k]-=a[i][j-1][k];
		}
	}
	int pw=1;for(int i=1;i<=n-1;i++)pw=pw*n%mod;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=0;k<d;k++)(ans+=a[i][j][k]*a[i][j][k]*pw)%=mod;
		}
	}
	// cout<<ans<<" "<<pw<<"\n";
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++){
			// for(int k=0;k<d;k++)cout<<a[i][j][k]<<" ";
		// }
		// cout<<"\n";
	// }
	pw=1;for(int i=1;i<=n-2;i++)pw=pw*n%mod;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<d;k++){
				for(int p=i+1;p<=n;p++){
					for(int q=1;q<=n;q++)(ans+=mod+2*a[i][j][k]*a[p][q][k]*pw%mod)%=mod;
				}
			}
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	T=1;
	while(T--)work();
}