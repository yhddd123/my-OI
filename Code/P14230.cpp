// Problem: P14230 不连续子串 / subseq
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14230
// Memory Limit: 1024 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-10-17 16:42:49
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
const int maxn=8010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
int f[maxn],g[maxn],sum;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	f[0]=1;for(int i=1;i<=n+1;i++){
		sum=0;
		for(int j=0;j<=n;j++)g[j]=0;
		g[a[i]]=1,sum=1;
		for(int j=i-1;~j;j--){
			// cout<<i<<" "<<j<<" "<<sum<<"\n";
			if(i==n+1&&!j)break;
			(f[i]+=f[j]*sum)%=mod;
			if(!j)break;
			if(a[j]==a[i])(sum+=mod-g[a[i]])%=mod,g[a[i]]=0;
			else{
				(sum+=mod-g[a[j]])%=mod;(g[a[j]]+=sum)%=mod,(sum+=g[a[j]])%=mod;
			}
		}
		// cout<<f[i]<<"\n";
	}
	printf("%lld\n",f[n+1]);
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