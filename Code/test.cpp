#include<bits/stdc++.h>
#define LL long long
#define pc __builtin_popcount
#define ctz __builtin_ctz
#define ar array<int,p>
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1<<17,M=19,p=17,mod=998244353,g=337827833,ig=634461433;
int n,m,u,I[M];ar a[M][M],f[N],A[N][M],ans;
inline int md(int x){return x>=p?x-p:x;}
inline void ad(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
inline void DFT(ar &a,bool o=1)
{
	static ar b;const int A=o?g:ig;
	for(int i=0,w=1;i<p;i++,w=1ll*w*A%mod)
	{
		LL sum=0;
		for(int j=0,s=1;j<p;j++,s=1ll*s*w%mod) sum+=1ll*s*a[j];
		b[i]=sum%mod;
	}
	for(int i=0;i<p;i++) a[i]=o?1ll*b[i]:(1ll*b[i]*I[p]%mod);
}
inline void Ln(ar *a)
{
	static ar b[M];
	for(int i=0;i<=n;i++)
	{
		b[i]=a[i];
		for(int j=0;j<p;j++) a[i][j]=0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++) for(int x=0;x<p;x++) a[i][x]=(a[i][x]+1ll*a[j][x]*b[i-j][x]%mod*j)%mod;
		for(int x=0;x<p;x++) a[i][x]=(b[i][x]+1ll*(mod-I[i])*a[i][x])%mod;
	}
	// for(int i=0;i<=n;i++) for(int j=0;j<p;j++) if(a[i][j]!=b[i][j]) assert(0);
}
inline void FWT()
{
	for(int i=1;i<u;i<<=1) for(int j=0;j<u;j+=(i<<1)) for(int k=j;k<j+i;k++)
		for(int t=0;t<=n;t++) for(int x=0;x<p;x++) ad(A[k+i][t][x],A[k][t][x]);
}
inline void IFWT()
{
	for(int i=1;i<u;i<<=1) for(int j=0;j<u;j+=(i<<1)) for(int k=j;k<j+i;k++)
		for(int t=0;t<=n;t++) for(int x=0;x<p;x++) ad(A[k+i][t][x],mod-A[k][t][x]);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n>>m;
	u=1<<n;
	for(int i=1,u,v,w;i<=m;i++)
	{
		cin>>u>>v>>w;if(u>v) swap(u,v);
		a[u-1][v-1][w]++;
	}
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) a[i][j][0]++,DFT(a[i][j]),a[j][i]=a[i][j];
	// for(int k=0;k<p;k++) cout<<a[0][1][k]<<" ";cout<<"\n";
	// for(int k=0;k<p;k++) cout<<a[0][3][k]<<" ";

	I[1]=1;for(int i=2;i<=p;i++) I[i]=mod-1ll*I[mod%i]*(mod/i)%mod;
	f[0][0]=1;DFT(f[0]);
	for(int i=1;i<u;i++)
	{
		int x=ctz(i),S=i^(1<<x);f[i]=f[S];
		while(S)
		{
			int y=ctz(S);S^=1<<y;
			for(int j=0;j<p;j++) f[i][j]=1ll*f[i][j]*a[x][y][j]%mod;
		}
		// for(int j=0;j<p;j++) cout<<f[i][j]<<" ";cout<<"\n";
	}

	for(int i=0;i<u;i++) A[i][pc(i)]=f[i];
	FWT();
	for(int i=0;i<u;i++) Ln(A[i]);
	IFWT();
	for(int i=0;i<p;i++) ad(ans[i],A[u-1][n][i]);
	DFT(ans,0);
	for(int i=0;i<p;i++) cout<<ans[i]<<"\n";
	return 0;
}