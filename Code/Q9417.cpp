#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
bool Mbe;

int n,a[maxn*2];
pii b[maxn*2];
int dp[maxn*2][maxn*2][3],ans;
int calc(pii a,pii b,pii c){
	return abs(a.fi*b.se+b.fi*c.se+c.fi*a.se-a.fi*c.se-b.fi*a.se-c.fi*b.se);
}
void chkmax(int &x,int y){(y>x)&&(x=y);}
void work(){
	n=read();ans=0;
	if(n>maxn){
		puts("0");
		return;
	}
	for(int i=1;i<=n;i++)a[i]=a[i+n]=read();
	for(int i=1;i<=n;i++)b[i]=b[i+n]={read(),read()};
	for(int len=1;len<=n;len++){
		for(int i=1,j=len;j<=2*n;i++,j++){
			if(a[i]==a[j])dp[i][j][0]=0;
			else dp[i][j][0]=-inf;
			dp[i][j][1]=dp[i][j][2]=0;
            if(a[i]==a[j]){
                for(int k=i+1;k<j;k++){
					chkmax(dp[i][j][0],dp[k][j][2]+calc(b[i],b[j],b[k]));
					chkmax(dp[i][j][0],dp[i][k][1]+calc(b[i],b[j],b[k]));
                }
            }
			for(int k=i+1;k<j;k++){
				chkmax(dp[i][j][1],dp[k][j][0]+calc(b[i],b[j],b[k]));
				chkmax(dp[i][j][2],dp[i][k][0]+calc(b[i],b[j],b[k]));
			}
			chkmax(ans,dp[i][j][0]);
		}
	}
	write(ans);puts("");
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
	
	T=read();
	while(T--)work();
}
