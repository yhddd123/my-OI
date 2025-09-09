#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(a,x) memset(a,x,sizeof(a))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl;
}
bool mbe;

int n,a[maxn];
#define poly vector<int>
poly merge(poly u,poly v){
	poly res;res.pb(u[0]+v[0]);
	int p=1,q=1;
	while(p<u.size()&&q<v.size()){
		if(u[p]-u[p-1]>v[q]-v[q-1])res.pb(u[p]-u[p-1]+res.back()),p++;
		else res.pb(v[q]-v[q-1]+res.back()),q++;
	}
	while(p<u.size())res.pb(u[p]-u[p-1]+res.back()),p++;
	while(q<v.size())res.pb(v[q]-v[q-1]+res.back()),q++;
	return res;
}
void chkmax(poly &u,poly v){
	while(u.size()<v.size())u.pb(-inf);
	for(int i=0;i<v.size();i++)u[i]=max(u[i],v[i]);
}
poly dp[maxn<<2][3][3];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
void sovle(int nd,int l,int r){
	if(l==r){
		dp[nd][0][0].pb(0),dp[nd][0][0].pb(0),dp[nd][0][1].pb(-a[l]),dp[nd][0][2].pb(a[l]);
		dp[nd][1][0].pb(-a[l]),dp[nd][1][1].pb(-inf),dp[nd][1][2].pb(-inf);
		dp[nd][2][0].pb(a[l]),dp[nd][2][1].pb(-inf),dp[nd][2][2].pb(-inf);
		return ;
	}
	sovle(ls,l,mid),sovle(rs,mid+1,r);
	for(int i=0;i<=2;i++){
		for(int j=0;j<=2;j++){
			chkmax(dp[nd][i][j],dp[ls][i][j]);
			chkmax(dp[nd][i][j],dp[rs][i][j]);
			chkmax(dp[nd][i][j],merge(dp[ls][i][0],dp[rs][0][j]));
			poly f=merge(dp[ls][i][1],dp[rs][2][j]);
			reverse(f.begin(),f.end());f.pb(-inf);reverse(f.begin(),f.end());
			chkmax(dp[nd][i][j],f);
			f=merge(dp[ls][i][2],dp[rs][1][j]);
			reverse(f.begin(),f.end());f.pb(-inf);reverse(f.begin(),f.end());
			chkmax(dp[nd][i][j],f);
		}
	}
	// cout<<l<<" "<<r<<" "<<dp[nd][0][0].size()<<" "<<dp[nd][0][2].size()<<"\n";
	// for(int v:dp[nd][0][0])cout<<v<<" ";cout<<"\n";
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sovle(1,1,n);dp[1][0][0].pb(0);
	for(int i=1;i<=n;i++)printf("%lld\n",dp[1][0][0][i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}