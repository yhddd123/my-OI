// Problem: AT_abc212_h [ABC212H] Nim Counting
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc212_h
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-28 20:18:52
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

int n,k,m=16;
int a[1<<16];
void fwt(int *a,int n,int w=1){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++){
				int u=a[j],v=a[j+k];
				a[j]=(u+v)*w%mod,a[j+k]=(u+mod-v)*w%mod;
			}
		}
	}
}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();k=read();
	for(int i=1;i<=k;i++)a[read()]++;
	fwt(a,1<<m,1);
	for(int s=0;s<(1<<m);s++){
		if(a[s]==1)a[s]=n;
		else a[s]=(ksm(a[s],n+1)+mod-a[s])*ksm(a[s]-1)%mod;
	}
	fwt(a,1<<m,(mod+1)/2);
	int ans=0;for(int s=1;s<(1<<m);s++)(ans+=a[s])%=mod;
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