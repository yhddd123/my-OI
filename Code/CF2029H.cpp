// Problem: CF2029H Message Spread
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2029H
// Memory Limit: 1000 MB
// Time Limit: 12000 ms
// Written by yhm.
// Start codeing:2026-01-20 19:30:55
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=21;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,ans;
int e[maxn][maxn];
int f[1<<maxn],g[1<<maxn];
int val[1<<maxn],ival[1<<maxn];
inline int ban(int s,int t){return val[s|t]*ival[s]%mod*ival[t]%mod;}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
void fmt1(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],a[j]);
		}
	}
}
void fmt2(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],mod-a[j]);
		}
	}
}
vector<int> id[maxn+1];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1,p=read(),q=read();
		e[u][v]=e[v][u]=p*ksm(q)%mod;
	}
	val[0]=ival[0]=1;for(int s=1;s<(1<<n);s++){
		int k=__lg(s);
		val[s]=val[s^(1<<k)];
		for(int j=0;j<k;j++)if(s&(1<<j))val[s]=val[s]*(1+mod-e[j][k])%mod;
		ival[s]=ksm(val[s]);
	}
	for(int s=1;s+1<(1<<n);s+=2)g[s]=ksm(1+mod-ban(s,(1<<n)-1-s));
	f[1]=1;
	for(int s=1;s<(1<<n);s+=2)id[__builtin_popcount(s)].pb(s);
	ff[1][1]=1;fmt1(ff[1],1<<n);
	for(int s=1;s<(1<<n);s+=2)gg[__builtin_popcount(s)][s]=val[(1<<n)-1-s];
	for(int i=1;i<n;i++)fmt1(gg[i],1<<n);
	for(int i=2;i<n;i++){
		for(int j=1;j<i;j++){
			for(int s:id[i])(ff[i][s]+=ff[j][s]*gg[i-j][s])%=mod;
		}
		fmt2(ff[i],1<<n);
		for(int s:id[i]){
			f[s]=ff[i][s];
			f[s]=f[s]*ival[(1<<n)-1-s]%mod;
			for(int j=0;j<n;j++)if(s&(1<<j))inc(f[s],mod-f[s^(1<<j)]);
		}
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
		for(int s:id[i])ff[i][s]=f[s]*g[s]%mod*ival[s]%mod;
		fmt1(ff[i],1<<n);
	}
	for(int s=1;s<(1<<n);s+=2)cout<<s<<" "<<f[s]<<" "<<g[s]<<" "<<ban(s,(1<<n)-1-s)<<"\n";
	for(int s=1;s+1<(1<<n);s+=2)(ans+=f[s]*g[s])%=mod;
	printf("%lld\n",ans);
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