// Problem: AT_abc230_g [ABC230G] GCD Permutation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc230_g
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-10-13 20:40:22
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int mu[maxn];
vector<int> d[maxn];
int ans[maxn];
int c[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	mu[1]=1;for(int i=1;i<=n;i++){
		for(int j=2*i;j<=n;j+=i)mu[j]-=mu[i];
	}
	// for(int i=1;i<=n;i++)cout<<mu[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i)d[j].pb(i);
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			for(int k:d[a[j]]){
				ans[i]+=mu[k]*(2*c[k]+1);
				c[k]++;
			}
		}
		ans[i]=(n/i)*(n/i)-ans[i];
		for(int j=i;j<=n;j+=i){
			for(int k:d[a[j]])c[k]=0;
		}
	}
	// for(int i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<"\n";
	for(int i=n;i;i--){
		for(int j=2*i;j<=n;j+=i)ans[i]-=ans[j];
	}
	int res=0;for(int i=2;i<=n;i++)res+=ans[i];
	// cout<<res<<"\n";
	for(int i=1;i<=n;i++)res+=(i!=1&&a[i]!=1);
	printf("%lld\n",res>>1);
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