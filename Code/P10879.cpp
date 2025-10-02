// Problem: P10879 「KDOI-07」对树链剖分的爱
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10879
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2025-10-02 20:15:28
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
const int maxn=5010;
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
int n,q,ans[maxn];
int l[maxn],r[maxn],ni[maxn];
int dp[maxn][maxn],f[maxn];
void work(){
	n=read();
	for(int i=2;i<=n;i++){
		l[i]=read(),r[i]=read();
		ni[i]=ksm(r[i]-l[i]+1);
	}
	q=read();
	while(q--){
		int u=read(),v=read(),w=read();
		if(u>v)swap(u,v);
		(dp[u][v]+=w)%=mod;
	}
	for(int u=n;u;u--){
		for(int v=n;v>u;v--){
			(f[v]+=f[v+1])%=mod;
			(dp[u][v]+=f[v])%=mod;
			(f[r[v]]+=dp[u][v]*ni[v])%=mod,(f[l[v]-1]+=mod-dp[u][v]*ni[v]%mod)%=mod;
			(ans[v]+=dp[u][v])%=mod;
		}
		for(int v=u;v;v--)(f[v]+=f[v+1])%=mod,(dp[v][u]+=f[v])%=mod;
		for(int v=1;v<=n;v++)f[v]=0;
	}
	for(int i=2;i<=n;i++)printf("%lld ",ans[i]);
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