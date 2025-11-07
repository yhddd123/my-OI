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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m;
pii a[maxn];
int lshx[maxn],lenx,lshy[maxn],leny;
int dp[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	for(int i=1;i<=n;i++)lshx[++lenx]=a[i].fi,lshy[++leny]=a[i].se;
	sort(lshx+1,lshx+lenx+1),lenx=unique(lshx+1,lshx+lenx+1)-lshx-1;
	sort(lshy+1,lshy+leny+1),leny=unique(lshy+1,lshy+leny+1)-lshy-1;
	for(int i=1;i<=n;i++)a[i].fi=lower_bound(lshx+1,lshx+lenx+1,a[i].fi)-lshx,a[i].se=lower_bound(lshy+1,lshy+leny+1,a[i].se)-lshy;
	sort(a+1,a+n+1,[&](pii u,pii v){return u.se<v.se;});
	for(int i=0;i<=n;i++)dp[i]=0;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[j].fi<=i&&a[j].se>dp[i]&&2*(lshy[a[j].se]-lshy[dp[i]])+lshx[i]<=m){
				dp[i]=max(dp[i],a[j].se);
			}
		}
		for(int j=1;j<=n;j++){
			if(a[j].fi>i&&a[j].se>dp[i]&&2*lshx[a[j].fi]+2*lshy[a[j].se]-lshx[i]-lshy[dp[i]]<=m){
				dp[a[j].fi]=max(dp[a[j].fi],a[j].se);
			}
			if(a[j].fi>i&&a[j].se<=dp[i]&&2*(lshx[a[j].fi]-lshx[i])+lshy[dp[i]]<=m){
				dp[a[j].fi]=max(dp[a[j].fi],dp[i]);
			}
		}
		cout<<dp[i]<<" ";
	}
	puts(dp[n]==n?"Yes":"No");
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