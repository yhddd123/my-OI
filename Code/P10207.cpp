// Problem: P10207 [JOI 2024 Final] 马拉松比赛 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10207
// Memory Limit: 1 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2024-07-14 11:03:22
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
const int maxn=500010;
const int maxm=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q,a[maxn];
int t[maxn];
int f[maxm][maxm][2],g[maxm][maxm][2];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),t[a[i]]++;
	n=0;for(int i=0;i<=m;i++)if(t[i])a[++n]=i;
	for(int i=1;i<=m;i++)t[i]+=t[i-1];
	if(n>=1000){
		q=read();
		while(q--)puts("No");
		return ;
	}
	mems(f,0x3f),mems(g,0x3f);
	f[1][n][0]=g[1][n][1]=0;
	for(int len=n-1;len;len--){
		for(int l=1,r=l+len-1;r<=n;l++,r++){
			int num=t[m]-t[a[r]]+(a[l]?t[a[l]-1]:0)+1;
			if(l>1)f[l][r][0]=min(f[l][r][0],f[l-1][r][0]+num*(a[l]-a[l-1]));
			if(r<n)f[l][r][0]=min(f[l][r][0],f[l][r+1][1]+num*(a[r+1]-a[l]));
			if(l>1)f[l][r][1]=min(f[l][r][1],f[l-1][r][0]+num*(a[r]-a[l-1]));
			if(r<n)f[l][r][1]=min(f[l][r][1],f[l][r+1][1]+num*(a[r+1]-a[r]));
			if(l>1)g[l][r][0]=min(g[l][r][0],g[l-1][r][0]+num*(a[l]-a[l-1]));
			if(r<n)g[l][r][0]=min(g[l][r][0],g[l][r+1][1]+num*(a[r+1]-a[l]));
			if(l>1)g[l][r][1]=min(g[l][r][1],g[l-1][r][0]+num*(a[r]-a[l-1]));
			if(r<n)g[l][r][1]=min(g[l][r][1],g[l][r+1][1]+num*(a[r+1]-a[r]));
		}
	}
	// for(int i=1;i<=n;i++)cout<<f[i][i][0]<<" "<<g[i][i][1]<<"\n";
	q=read();
	while(q--){
		int fr=read(),to=read(),tim=read();
		int p=lower_bound(a+1,a+n+1,to)-a,ans=inf;
		if(p<=n){
			ans=min(ans,g[p][p][1]+abs(fr-a[n])+(t[m]+1)*abs(a[p]-to));
			ans=min(ans,f[p][p][0]+abs(fr-a[1])+(t[m]+1)*abs(a[p]-to));
		}
		p--;
		if(p){
			ans=min(ans,g[p][p][1]+abs(fr-a[n])+(t[m]+1)*abs(a[p]-to));
			ans=min(ans,f[p][p][0]+abs(fr-a[1])+(t[m]+1)*abs(a[p]-to));
		}
		// cout<<ans<<"\n";
		if(ans+t[m]<=tim)puts("Yes");
		else puts("No");
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
