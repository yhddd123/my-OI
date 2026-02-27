// Problem: AT_agc046_d [AGC046D] Secret Passage
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc046_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-27 17:07:55
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
const int maxn=310;
const int inf=1e9;
bool mbe;

int n,ans;
char s[maxn];
bool f[maxn][maxn][maxn];
int g[maxn][maxn][maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	if(n<=1){puts("1");return ;}
	f[1][0][0]=1;
	for(int i=1;i<=n+1;i++){
		for(int j=i-1;~j;j--){
			for(int k=i-1-j;~k;k--)if(f[i][j][k]){
				if(j)f[i][j-1][k]=1;
				if(k)f[i][j][k-1]=1;
				if(j||k)f[i+1][j][k]=1;
				if(i<n){
					if(s[i]=='0'||s[i+1]=='0')f[i+2][j+1][k]=1;
					if(s[i]=='1'||s[i+1]=='1')f[i+2][j][k+1]=1;
				}
				if(s[i]=='0'&&k)f[i+1][j+1][k-1]=1;
				if(s[i]=='1'&&j)f[i+1][j-1][k+1]=1;
			}
		}
	}
	g[n+1][0][0]=1;
	for(int i=n+1;i;i--){
		for(int j=0;j<i;j++){
			for(int k=0;j+k<i;k++)if(g[i][j][k]){
				inc(g[i-1][j][k],g[i][j][k]);
				if(s[i-1]!='0')inc(g[i][j+1][k],g[i][j][k]);
				if(s[i-1]!='1')inc(g[i][j][k+1],g[i][j][k]);
				// if(f[i][j][k])cout<<i<<" "<<j<<" "<<k<<" "<<g[i][j][k]<<"\n";
				if(f[i][j][k])inc(ans,g[i][j][k]);
			}
		}
	}
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}