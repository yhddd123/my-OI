// Problem: P5643 [PKUWC2018] 随机游走
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5643
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-03-25 12:57:22
// 
// Powered by CP Editor (https://cpeditor.org)

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

int n,q,x;
vector<int> e[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int k[maxn],b[maxn],d[maxn];
bool vis[maxn];
void dfs(int u,int fa){
	if(vis[u]){k[u]=0,b[u]=0;return ;}
	int s1=d[u],s2=d[u];
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		(s1+=mod-k[v])%=mod,(s2+=b[v])%=mod;
	}
	k[u]=ksm(s1),b[u]=s2*ksm(s1)%mod;
}
int f[1<<maxn];
void work(){
	n=read();q=read();x=read()-1;
	for(int i=1;i<n;i++){
		int u=read()-1,v=read()-1;
		e[u].pb(v),e[v].pb(u);
		d[u]++,d[v]++;
	}
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++)k[i]=b[i]=0;
		for(int i=0;i<n;i++)if(s&(1<<i))vis[i]=1;
		dfs(x,-1);
		f[s]=(((__builtin_popcount(s)+1)&1)?mod-1:1)*b[x]%mod;
		// cout<<s<<" "<<b[x]<<"\n";
		for(int i=0;i<n;i++)if(s&(1<<i))vis[i]=0;
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))(f[s]+=f[s^(1<<i)])%=mod;
	}
	while(q--){
		int k=read();
		int s=0;while(k--)s|=(1<<read()-1);
		printf("%lld\n",f[s]);
	}
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