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
const int maxn=510;
const int inf=1e18;
bool mbe;

int n,d,r,lim,a[maxn],ans;
int f[maxn][maxn][maxn];
inline void chkmx(int &u,int v){(u<v)&&(u=v);}
vector<int> pos[maxn];
bool fl;
void work(){
	n=read();d=read(),r=read();ans=0;
	lim=n;for(int i=1;i<=n;i++)if(i*r%d==0){lim=i;break;}
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=n;i;i--){
		for(int j=i;j<=n;j++){
			for(int k=0;k<=j-i+1&&k<=d;k++)f[i][j][k]=-inf;
		}
		for(int k=1;k<=n-i+1&&k<=lim;k++)pos[k].clear();
		f[i][i][0]=0;
		if((a[i]-a[i-1]-r)%d==0)f[i][i][1]=(a[i]-a[i-1])/d,pos[1].pb(i);
		for(int j=i+1;j<=n;j++){
			for(int k=0;k<=j-i&&k<=d;k++)f[i][j][k]=max(f[i][j][k],f[i+1][j][k]);
			for(int k=1;k<=j-i&&k<=lim;k++){
				for(int p:pos[k]){
					int val=(a[p]-a[i-1]-k*r)/d;
					for(int k1=0;k1<=j-p&&k+k1<=d;k1++)if(f[p+1][j][k1]>=0){
						f[i][j][k+k1]=max(f[i][j][k+k1],val+f[p+1][j][k1]);
						// cout<<i<<" "<<p<<" "<<j<<" "<<k<<" "<<k1<<" "<<f[i][j][k+k1]<<" "<<(a[p]-a[i-1]-k*r)/d<<" "<<f[p+1][j][k1]<<"\n";
					}
				}
			}
			for(int k=1;k<=j-i+1&&k<=lim;k++)if(f[i][j][k-1]>=0&&(a[j]-a[i-1]-k*r)%d==0){
				f[i][j][k]=(a[j]-a[i-1]-k*r)/d;
				pos[k].pb(j);
				break;
			}
		}
	}
	for(int k=1;k<=n;k++)ans=max(ans,f[1][n][k]);
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	if(T<=2)fl=1;
	while(T--)work();
}