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
const int maxn=2010;
const int inf=1e18;
bool mbe;

int n,k,p;
int a[maxn],c[maxn];
int val[maxn][maxn];
int f[maxn][maxn];
void sovle(int i,int l,int r,int pl,int pr){
	if(l>r)return ;
	int mid=l+r>>1,mx=-inf,p=pl;
	for(int k=pl;k<=pr&&k+1<mid;k++){
		int kk=mid-k-1;
		if(mx<f[i-1][mid-kk-1]+val[mid-kk][kk]){
			mx=f[i-1][mid-kk-1]+val[mid-kk][kk];
			p=k;
		}
	}
	f[i][mid]=max(f[i][mid],mx);
	// cout<<i<<" "<<l<<" "<<r<<" "<<p<<" "<<mx<<"\n";
	sovle(i,l,mid-1,pl,p);
	sovle(i,mid+1,r,p,pr);
}
void work(){
	n=read();k=read();p=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++){
		val[i][0]=p;for(int j=1;j<=n-i+1;j++)val[i][j]=val[i][j-1]+a[i+j-1]*c[j];
	}
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0;
	for(int j=1;j<=n;j++){
		f[j][j]=0;
		sovle(j,j+1,n+1,0,n-1);
		for(int i=j+1;i<=n+1;i++)f[j][i]=max(f[j][i],f[j-1][i-1]);
		// for(int i=j+1;i<=n+1;i++){
			// f[j][i]=f[j-1][i-1];
			// for(int k=1;k<i;k++)f[j][i]=max(f[j][i],f[j-1][i-k-1]+val[i-k][k]);
			// // cout<<f[j][i]<<" ";
		// }
		// cout<<"\n";
	}
	int ans=0;for(int i=1;i<=k&&i<=n;i++)ans=max(ans,f[n+1-i][n+1]);
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("1.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}