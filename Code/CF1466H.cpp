// Problem: CF1466H Finding satisfactory solutions
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1466H
// Memory Limit: 1000 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-10-29 17:20:16
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=45;
const int maxm=1445;
const int inf=1e9;
bool mbe;

int n,m,p[maxn];
bool vis[maxn];
vector<int> cnt;
vector<int> a[maxm],b;
int num[maxm],siz[maxm],idx;
void dfs(int d,int s1=0,int s2=0){
	// cout<<d<<" "<<s1<<" "<<s2<<"\n";
	if(d==n){
		// for(int v:b)cout<<v<<" ";cout<<"\n";
		a[++idx]=b;num[idx]=s1,siz[idx]=s2;
		return ;
	}
	for(int i=0;i<=cnt[d];i++){
		b.pb(i);
		dfs(d+1,s1+i,s2+i*(d+1));
		b.pop_back();
	}
}
int fac[maxn],C[maxn][maxn],coef[maxn][maxn];
int f[maxm];
void work(){
	n=read();
	for(int i=1;i<=n;i++)p[i]=read();
	cnt.resize(n);
	for(int i=1;i<=n;i++)if(!vis[i]){
		int x=i,l=0;while(!vis[x])vis[x]=1,x=p[x],++l;
		cnt[l-1]++;
	}
	dfs(0);
	// cout<<idx<<"\n";
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=0;i<n;i++){
		coef[i][0]=1;
		for(int j=0;j<=i;j++)(coef[i][1]+=C[i][j]*fac[j]%mod*fac[n-1-j])%=mod;
		for(int j=2;j<=n;j++)coef[i][j]=coef[i][j-1]*coef[i][1]%mod;
	}
	m=idx;f[1]=1;
	for(int i=2;i<=m;i++){
		for(int j=1;j<i;j++){
			int res=1;for(int k=0;k<n;k++)res=res*C[a[i][k]][a[j][k]]%mod;
			// cout<<i<<" "<<j<<" "<<coef[siz[j]][siz[i]-siz[j]]<<"\n";
			(f[i]+=(((num[i]-num[j]+1)&1)?mod-1:1)*f[j]%mod*coef[siz[j]][siz[i]-siz[j]]%mod*res)%=mod;
		}
		// cout<<i-1<<" "<<f[i]<<"\n";
	}
	printf("%lld\n",f[m]);
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