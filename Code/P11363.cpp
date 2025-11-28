// Problem: P11363 [NOIP2024] 树的遍历
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11363
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-11-28 16:45:06
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
const int maxn=100010;
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
int n,k,ans;
int d[maxn],a[maxn];
int head[maxn],tot=1;
struct nd{
	int nxt,to,fl;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v,0};head[u]=tot;}
int fac[maxn];
int f[maxn];
void dfs(int u,int fa){
	f[u]=0;
	for(int i=head[u],sum=0;i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		if(e[i].fl)(f[u]+=mod-1)%=mod;
		else (f[u]+=a[v]*f[v])%=mod;
		if(e[i].fl){
			int w=((mod-1)+(mod-1)*f[v]%mod*a[v])%mod;
			(ans+=w)%=mod;
			(ans+=sum*(mod-1)%mod*a[u])%=mod;
			(sum+=mod-1)%=mod;
		}
		else{
			int w=a[v]*f[v]%mod;
			(ans+=sum*w%mod*a[u])%=mod;
			(sum+=w)%=mod;
		}
		// cout<<u<<" "<<f[u]<<"\n";
	}
}
void work(){
	n=read();k=read();ans=0;
	for(int i=1;i<=n;i++)head[i]=d[i]=0;tot=1;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++)a[i]=ksm(d[i]-1);
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=k;i++){
		int x=read();
		e[x<<1].fl=e[x<<1|1].fl=1;
	}
	dfs(1,0);
	ans=mod-ans;for(int i=1;i<=n;i++)ans=ans*fac[d[i]-1]%mod;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	n=maxn-10;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	read();T=read();
	while(T--)work();
}