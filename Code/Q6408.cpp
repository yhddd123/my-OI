#include<bits/stdc++.h>
// #define int long long
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
const int maxn=110;
const int inf=1e9;
bool mbe;

int n,m,v,a[maxn],ans;
int f[maxn][maxn*maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();m=read();v=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1,greater<int>());
	for(int x=1;x<=n;x++){
		for(int i=x;i<=n;i++){
			for(int s=0;s<=m*v+1;s++)f[i][s]=0;
		}
		f[x][0]=1;
		for(int i=x+1;i<=n;i++){
			if(a[i]+m<a[x])break;
			for(int s=0;s<=m*v+1;s++)if(f[i-1][s]){
				if(s+a[x]-a[i]>m*v)inc(ans,mod-f[i-1][s]);
				inc(f[i][s],f[i-1][s]);inc(f[i][min(m*v+1,s+a[x]-a[i])],f[i-1][s]);
			}
		}
	}
	for(int y=1;y<=n;y++){
		for(int i=1;i<=y;i++){
			for(int s=0;s<=m*v;s++)f[i][s]=0;
		}
		f[y][0]=1;
		for(int i=y-1;i;i--){
			if(a[y]+m<a[i])break;
			for(int s=0;s<=m*v;s++)if(f[i+1][s]){
				if(s+m-a[i]+a[y]+(i-1+n-y+1)*m>=m*v){
					// cout<<i<<" "<<y<<" "<<s<<" "<<f[i+1][s]<<"\n";
					inc(ans,f[i+1][s]);
				}
				inc(f[i][min(m*v,s+m)],f[i+1][s]);inc(f[i][min(m*v,s+m-a[i]+a[y])],f[i+1][s]);
			}
		}
	}
	(ans+=n)%=mod;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}