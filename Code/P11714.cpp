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
const int maxn=15;
const int inf=1e9;
bool mbe;

int n,m;
int e[maxn],num[1<<maxn];
int pw[maxn*maxn];
int f[1<<maxn],g[1<<maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u]|=1<<v;
		num[(1<<u)|(1<<v)]++;
	}
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
	}
	f[0]=g[0]=1;
	for(int s=1;s<(1<<n);s++){
		for(int t=(s-1)&s;t;t=(t-1)&s)if(__lg(s)==__lg(t))(g[s]+=mod-f[t]*g[s^t]%mod)%=mod;
		f[s]=pw[num[s]];
		for(int t=s;t;t=(t-1)&s){
			int cnt=num[s^t];
			for(int i=0;i<n;i++)if(t&(1<<i))cnt+=__builtin_popcount(e[i]&(s^t));
			(f[s]+=mod-g[t]*pw[cnt]%mod)%=mod;
		}
		(g[s]+=f[s])%=mod;
		// cout<<s<<" "<<f[s]<<" "<<g[s]<<" "<<num[s]<<"\n";
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