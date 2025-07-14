// Problem: 并
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/showproblem.php?pid=7444
// Memory Limit: 262 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-24 21:45:30
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
const int maxn=4010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
int a[maxn][4];
int bx[maxn],lenx,by[maxn],leny;
int sum[maxn][maxn];
int num[maxn];
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
int C(int m,int n){
	if(m<n)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
void work(){
	n=read();
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++)a[i][0]=read(),a[i][1]=read(),a[i][2]=read(),a[i][3]=read();
	for(int i=1;i<=n;i++)bx[++lenx]=a[i][0],bx[++lenx]=a[i][2];
	for(int i=1;i<=n;i++)by[++leny]=a[i][1],by[++leny]=a[i][3];
	sort(bx+1,bx+lenx+1),lenx=unique(bx+1,bx+lenx+1)-bx-1;
	sort(by+1,by+leny+1),leny=unique(by+1,by+leny+1)-by-1;
	for(int i=1;i<=n;i++){
		a[i][0]=lower_bound(bx+1,bx+lenx+1,a[i][0])-bx;
		a[i][1]=lower_bound(by+1,by+leny+1,a[i][1])-by;
		a[i][2]=lower_bound(bx+1,bx+lenx+1,a[i][2])-bx;
		a[i][3]=lower_bound(by+1,by+leny+1,a[i][3])-by;
		sum[a[i][0]][a[i][1]]++,sum[a[i][0]][a[i][3]]--,sum[a[i][2]][a[i][1]]--,sum[a[i][2]][a[i][3]]++;
	}
	for(int i=1;i<=lenx;i++){
		for(int j=1;j<=leny;j++){
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
			(num[sum[i][j]]+=(bx[i]-bx[i-1])*(by[j]-by[j-1]))%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		int ans=0;
		for(int j=1;j<=n;j++)(ans+=(C(n,i)-C(n-j,i)+mod)*ksm(C(n,i))%mod*num[j])%=mod;
		printf("%lld\n",ans);
	}
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
