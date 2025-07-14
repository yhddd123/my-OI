#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans;
int dp[2][76][76][76],pw[maxn],f[6],cur;
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	pw[0]=1;for(int i=1;i<=n;i++)inc(pw[i]=pw[i-1],pw[i-1]);
	dp[0][0][0][0]=1;
	for(int i=1;i<=n;i++){
		int d=a[i]-a[i-1];
		mems(dp[i&1],0);
		if(i==1){
			int a=0,b=0,c=0;
			int aa=max(0ll,a-d),bb=max(0ll,b-d),cc=max(0ll,c-d);
			f[0]=aa,f[1]=bb,f[2]=cc,f[3]=f[4]=f[5]=0;
			for(int j=0;j<5;j++){
				f[j+1]=max(f[j+1],f[j]+20);
				if(j+3<6)f[j+3]=max(f[j+3],f[j]+75);
			}
			for(int j=1;j<=5;j++)f[j]=max(f[j],f[j-1]);
			inc(dp[i&1][f[0]][f[1]][f[2]],dp[cur][a][b][c]);
			int p=0;while(!f[p])p++;
			(ans+=dp[cur][a][b][c]*pw[n-i]%mod*p)%=mod;
			inc(dp[i&1][f[p]][f[p+1]][f[p+2]],dp[cur][a][b][c]);
		}
		for(int a=0;a<=75;a++){
			for(int b=a+20;b<=75;b++){
				for(int c=b+20;c<=75;c++)if(dp[cur][a][b][c]){
					// cout<<i<<" "<<a<<" "<<b<<" "<<c<<" "<<dp[cur][a][b][c]<<"\n";
					int aa=max(0ll,a-d),bb=max(0ll,b-d),cc=max(0ll,c-d);
					f[0]=aa,f[1]=bb,f[2]=cc,f[3]=f[4]=f[5]=0;
					for(int j=0;j<5;j++){
						f[j+1]=max(f[j+1],f[j]+20);
						if(j+3<6)f[j+3]=max(f[j+3],f[j]+75);
					}
					for(int j=1;j<=5;j++)f[j]=max(f[j],f[j-1]);
					inc(dp[i&1][f[0]][f[1]][f[2]],dp[cur][a][b][c]);
					int p=0;while(!f[p])p++;
					(ans+=dp[cur][a][b][c]*pw[n-i]%mod*p)%=mod;
					inc(dp[i&1][f[p]][f[p+1]][f[p+2]],dp[cur][a][b][c]);
				}
			}
		}
		cur^=1;
	}
	printf("%lld\n",ans*2%mod);
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
