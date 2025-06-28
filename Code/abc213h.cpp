// Problem: AT_abc213_h [ABC213H] Stroll
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc213_h
// Memory Limit: 1 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-05-28 20:34:16
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
const int maxn=11;
const int maxm=40010;
const int inf=1e9;
bool mbe;

int n,m,k;
pii edge[maxn*maxn];
vector<int> p[maxn*maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
	int g=3,invg=ksm(3);
	int to[maxm<<2];
	vector<int> ntt(vector<int> a,int fl){
		int n=a.size();
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int l=2;l<=n;l<<=1){
			int bas=ksm(fl==1?g:invg,(mod-1)/l);
			int k=l>>1;
			for(int i=0;i<n;i+=l){
				int mul=1;
				for(int j=i;j<i+k;j++){
					int u=a[j],v=a[j+k]*mul%mod;
					a[j]=(u+v)%mod,a[j+k]=(u+mod-v)%mod;
					mul=mul*bas%mod;
				}
			}
		}
		if(fl==-1){
			int invn=ksm(n);
			for(int i=0;i<n;i++)a[i]=a[i]*invn%mod;
		}
		return a;
	}
	vector<int> mul(vector<int> a,vector<int> b){
		int n=a.size()-1,m=b.size()-1;int k=1;
		while(k<n+m+1)k<<=1;
		vector<int> f(k),g(k);
		for(int i=0;i<=n;i++)f[i]=a[i];
		for(int i=0;i<=m;i++)g[i]=b[i];
		for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
		f=ntt(f,1),g=ntt(g,1);
		for(int i=0;i<k;i++)f[i]=f[i]*g[i]%mod;
		f=ntt(f,-1);f.resize(n+m+1);
		return f;
	}
}
using poly::mul;
vector<int> dp[maxn];
void sovle(int l,int r){
	if(l==r){
		// cout<<l<<"\n";
		// for(int u=1;u<=n;u++){
			// cout<<u<<" ";for(int v:dp[u])cout<<v<<" ";cout<<"\n";
		// }
		return ;
	}
	int mid=l+r>>1;
	sovle(l,mid);
	for(int i=1;i<=m;i++){
		auto[u,v]=edge[i];
		vector<int> g(r-l+1);
		for(int j=0;j<=r-l;j++)g[j]=p[i][j];
		vector<int> f(mid-l+1);
		for(int j=l;j<=mid;j++)f[j-l]=dp[u][j];
		f=mul(f,g);
		for(int j=mid+1;j<=r;j++)(dp[v][j]+=f[j-l])%=mod;
		f.clear();f.resize(mid-l+1);
		for(int j=l;j<=mid;j++)f[j-l]=dp[v][j];
		f=mul(f,g);
		for(int j=mid+1;j<=r;j++)(dp[u][j]+=f[j-l])%=mod;
	}
	sovle(mid+1,r);
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		edge[i]={read(),read()};
		p[i].resize(k+1);
		for(int j=1;j<=k;j++)p[i][j]=read();
	}
	for(int i=1;i<=n;i++)dp[i].resize(k+1);
	dp[1][0]=1;
	sovle(0,k);
	printf("%lld\n",dp[1][k]);
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