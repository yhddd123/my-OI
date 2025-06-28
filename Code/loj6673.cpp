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
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,m;
bool e[maxn][maxn];
struct bas{
	int cnt,sz,p[maxn];
	void insert(int x){
		++cnt;
		for(int i=n-1;~i;i--)if(x&(1<<i)){
			if(!p[i]){p[i]=x,sz++;return ;}
			x^=p[i];
		}
	}
	void clr(){
		cnt=sz=0;for(int i=0;i<n;i++)p[i]=0;
	}
}b[1<<maxn];
int pw[maxn*maxn];
int f[1<<maxn],g[1<<maxn];
void fmt(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i)){
			if(w==1)(a[s]+=a[s^(1<<i)])%=mod;
			else (a[s]+=mod-a[s^(1<<i)])%=mod;
		}
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1],ni[maxn+1];
void xorln(int *a,int *b,int n){
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)gg[i]=0;
		for(int i=0;i<n;i++){
			gg[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(gg[i]+=mod-ff[j][s]*gg[i-j]%mod)%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=gg[i-1]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fmt(ff[i],n,-1);
	b[0]=1;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u][v]=e[v][u]=1;
	}
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*2%mod;
	for(int s=1;s<(1<<n);s++){
		int p=__lg(s&(-s));
		b[s]=b[s^(1<<p)];
		for(int i=p+1;i<n;i++)if((s&(1<<i))&&e[i][p])b[s].insert((1<<p)|(1<<i));
		f[s]=pw[b[s].cnt-b[s].sz];
		// cout<<s<<" "<<f[s]<<" "<<b[s].cnt<<" "<<b[s].sz<<"\n";
	}
	xorln(f,g,n);
	printf("%lld\n",g[(1<<n)-1]);
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