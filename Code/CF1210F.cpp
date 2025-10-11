// Problem: CF1210F2 Marek and Matching (hard version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1210F2
// Memory Limit: 250 MB
// Time Limit: 15000 ms
// Written by yhm.
// Start codeing:2025-10-10 20:59:27
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
const int maxn=7;
const int inf=1e9;
const int ni=570000004ll;
bool mbe;

int n,m,e[maxn][maxn];
int no[1<<maxn][1<<maxn],ok[1<<maxn][1<<maxn];
int f[1<<maxn][1<<maxn],g[1<<maxn][1<<maxn];
int sz[1<<maxn];
void work(){
	n=m=read();
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)e[i][j]=read()*ni%mod;
	}
	for(int s=0;s<(1<<n);s++){
		for(int t=0;t<(1<<m);t++){
			no[s][t]=1;
			for(int i=0;i<n;i++)if(s&(1<<i)){
				for(int j=0;j<m;j++)if(t&(1<<j))no[s][t]=no[s][t]*(1-e[i][j]+mod)%mod;
			}
			ok[s][t]=1;
			for(int j=0;j<m;j++)if(t&(1<<j)){
				ok[s][t]=ok[s][t]*(1-no[s][1<<j]+mod)%mod;
			}
		}
	}
	for(int s=0;s<(1<<max(n,m));s++)sz[s]=__builtin_popcount(s);
	for(int s=0;s<(1<<n);s++){
		for(int t=0;t<(1<<m);t++){
			if(sz[s]>sz[t]){
				g[s][t]=ok[s][t];
				for(int s1=s;s1;s1=(s1-1)&s){
					for(int t1=t;;t1=(t1-1)&t){
						if((s1!=s||t1!=t)&&sz[s1]-sz[t1]>=sz[s]-sz[t]){
							(g[s][t]+=mod-g[s1][t1]*no[s1][t^t1]%mod*f[s^s1][t^t1]%mod)%=mod;
						}
						if(!t1)break;
					}
				}
			}
			else{
				f[s][t]=ok[s][t];
				for(int s1=s&(s-1);s1;s1=(s1-1)&s){
					for(int t1=t&(t-1);;t1=(t1-1)&t){
						if(s1!=s||t1!=t)(f[s][t]+=mod-g[s1][t1]*no[s1][t^t1]%mod*f[s^s1][t^t1]%mod)%=mod;
						if(!t1)break;
					}
				}
			}
		}
	}
	printf("%lld\n",f[(1<<n)-1][(1<<m)-1]);
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