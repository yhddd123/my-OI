// Problem: P11734 [集训队互测 2015] 胡策的统计
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11734
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-10-12 16:49:24
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=20;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int n,m;
int e[maxn],num[1<<maxn];
int f[1<<maxn],g[1<<maxn];
int pw[maxn*maxn];
inline void fix(int &u){u+=(u>>31)&mod;}
void fwtor(int *a,int n,int w=1){
	for(int l=2,k=1;l<=n;l<<=1,k<<=1){
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++){
				if(w==1)fix(a[j+k]+=a[j]-mod);
				else fix(a[j+k]-=a[j]);
			}
		}
	}
}
int ff[maxn+1][1<<maxn],hh[1<<maxn],ni[maxn+1];
void xorf(int *a,int *b,int n){//b=1/(1-ln(a))
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fwtor(ff[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			hh[i]=1ll*ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)fix(hh[i]-=1ll*ff[j][s]*hh[i-j]%mod);
		}
		for(int i=1;i<=n;i++)ff[i][s]=1ll*hh[i-1]*ni[i]%mod;
	}
	// for(int i=0;i<=n;i++)fwtor(ff[i],1<<n,-1);
	// for(int s=0;s<(1<<n);s++)cout<<ff[__builtin_popcount(s)][s]<<" ";cout<<"\n";
	// for(int i=0;i<=n;i++)fwtor(ff[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		ff[0][s]=mod+1-ff[0][s];for(int i=1;i<=n;i++)ff[i][s]=mod-ff[i][s];
		int nif=ksm(ff[0][s]);
		for(int i=0;i<=n;i++){
			hh[i]=1;for(int j=1;j<=i;j++)fix(hh[i]-=1ll*ff[j][s]*hh[i-j]%mod);
			hh[i]=1ll*hh[i]*nif%mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
	for(int i=0;i<=n;i++)fwtor(ff[i],1<<n,-1);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u]|=1<<v,e[v]|=1<<u;
		num[(1<<u)|(1<<v)]++;
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
	}
	pw[0]=1;for(int i=1;i<=m;i++)fix(pw[i]=pw[i-1]*2-mod);
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
	for(int s=1;s<(1<<n);s++)f[s]=pw[num[s]];
	xorf(f,g,n);
	printf("%d\n",g[(1<<n)-1]);
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