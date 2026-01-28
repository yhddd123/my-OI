// Problem: CF2070F Friends and Pizza
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2070F
// Memory Limit: 500 MB
// Time Limit: 8000 ms
// Written by yhm.
// Start codeing:2026-01-28 11:22:30
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
const int maxm=500010;
const int maxn=20;
const int inf=1e9;
bool mbe;

int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
void fmt1(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]+=a[j];
		}
	}
}
void fmt2(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]-=a[j];
		}
	}
}
int n,m,a[maxm],t[maxn];
char s[25];
int tf[maxn+1],th[maxn+1];
int ans[maxm],sum[1<<maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",s+1);int l=strlen(s+1);
		for(int j=1;j<=l;j++)a[i]|=1<<s[j]-'A';
	}
	for(int i=0;i<n;i++)t[i]=read();
	for(int s=1;s<(1<<n);s++){
		int k=__lg(s);
		sum[s]=sum[s^(1<<k)]+t[k];
	}
	int all=0;for(int i=0;i<n;i++)if(t[i]&1)all|=1<<i;
	for(int i=1;i<=m;i++)ff[__builtin_popcount(a[i]&all)][a[i]]++;
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++){
			th[i]=0;
			for(int j=0;j<=i;j++)th[i]+=tf[j]*tf[i-j];
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)ans[sum[s]]+=ff[__builtin_popcount(s&all)][s];
	// for(int i=0;i<=sum[(1<<n)-1];i++)printf("%lld ",ans[i]);puts("");
	for(int i=1;i<=m;i++)if(!(a[i]&all))ans[sum[a[i]]]--;
	for(int i=sum[(1<<n)-1];~i;i--)printf("%lld ",ans[i]/2);
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