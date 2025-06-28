// Problem: AT_agc013_d [AGC013D] Piling Up
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc013_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-04-07 22:15:06
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 1000000007ll
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
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n,m,ans;
int f[2][maxn],g[2][maxn],cur;
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();m=read();
	for(int j=1;j<=n;j++)f[0][j]=1;g[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=n;j++)f[i&1][j]=g[i&1][j]=0;
		for(int j=0;j<=n;j++){
			if(j){
				inc(f[i&1][j],f[cur][j-1]);
				inc(g[i&1][j],g[cur][j-1]);
				if(j==1)inc(g[i&1][j],f[cur][j]);
				else inc(f[i&1][j],f[cur][j]);
				inc(g[i&1][j],g[cur][j]);
			}
			if(j<n){
				if(!j)inc(g[i&1][j],f[cur][j+1]);
				else inc(f[i&1][j],f[cur][j+1]);
				inc(g[i&1][j],g[cur][j+1]);
				if(j)inc(f[i&1][j],f[cur][j]);
				inc(g[i&1][j],g[cur][j]);
			}
		}
		cur^=1;
	}
	for(int i=0;i<=n;i++)inc(ans,g[m&1][i]);
	printf("%d\n",ans);
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