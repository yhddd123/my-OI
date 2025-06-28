#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=18;
const int inf=1e9;
bool mbe;

int n,m;
int e[1<<maxn],pw[maxn*maxn];
void fmt(int *a,int n,int w){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)]*w)%=mod;
	}
}
int ff[maxn+1][1<<maxn],hh[maxn+1],ni[maxn+1];
void xorln(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)hh[i]=0;
		for(int i=0;i<n;i++){
			hh[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(hh[i]+=mod-ff[j][s]*hh[i-j]%mod)%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=hh[i-1]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fmt(ff[i],n,mod-1);
	b[0]=0;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
int f[1<<maxn],g[1<<maxn],h[1<<maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[(1<<u)|(1<<v)]++;
	}
	if(n==1){puts("1");return ;}
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*2%mod;
	fmt(e,n,1);
	for(int s=0;s<(1<<n);s++)f[s]=pw[e[s]];
	xorln(f,f,n);
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)g[s]=h[s]=0;
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))g[s^(1<<i)]=f[s];
		xorln(g,h,n);
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))f[s]=h[s^(1<<i)];
		// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	}
	printf("%lld\n",f[(1<<n)-1]);
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