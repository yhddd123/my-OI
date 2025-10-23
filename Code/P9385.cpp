// Problem: P9385 [THUPC 2023 决赛] 阴阳阵法
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9385
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-22 10:32:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,m,mod;
int f[maxn][maxn],g[maxn][maxn][2][2],h[maxn][maxn][2],l[maxn][maxn][2][2][2][2];
void work(){
	n=read();m=read();mod=read();
	f[0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int o=0;o<2;o++){
				for(int o1=0;o1<2;o1++)if(g[i][j][o][o1]){
					for(int o2=0;o2<2;o2++){
						if(o1&o2)continue;
						(g[i+(!o2)][j+o2][o][o2]+=g[i][j][o][o1]*(o2?m-j:n-i))%=mod;
					}
					if(o&o1)continue;
					(f[i][j]+=g[i][j][o][o1])%=mod;
				}
			}
			for(int o1=0;o1<2;o1++)if(h[i][j][o1]){
				for(int o2=0;o2<2;o2++){
					if(o1&o2)continue;
					(h[i+(!o2)][j+o2][o2]+=h[i][j][o1]*(o2?m-j:n-i))%=mod;
					(l[i+(!o2)][j+o2][o2][o2][!o2][o2]+=h[i][j][o1]*(o2?m-j:n-i))%=mod;
				}
			}
			for(int o=0;o<2;o++){
				for(int o1=0;o1<2;o1++){
					for(int c0=0;c0<2;c0++){
						for(int c1=0;c1<2;c1++)if(l[i][j][o][o1][c0][c1]){
							for(int o2=0;o2<2;o2++){
								if(o1&o2)continue;
								(l[i+(!o2)][j+o2][o][o2][c0^(!o2)][c1^o2]+=l[i][j][o][o1][c0][c1]*(o2?m-j:n-i))%=mod;
							}
							if(o&o1)continue;
							if(c0&c1)continue;
							(f[i][j]+=l[i][j][o][o1][c0][c1])%=mod;
						}
					}
				}
			}
			if(i<n){
				for(int o=0;o<2;o++){
					(g[i+1][j][o][0]+=f[i][j]*(o?j:i))%=mod;
				}
				(h[i+1][j][0]+=f[i][j])%=mod;
				(l[i+1][j][0][0][1][0]+=f[i][j])%=mod;
			}
			else{
				for(int o=0;o<2;o++){
					(g[i][j+1][o][1]+=f[i][j]*(o?j:i))%=mod;
				}
				(h[i][j+1][1]+=f[i][j])%=mod;
				(l[i][j+1][1][1][0][1]+=f[i][j])%=mod;
			}
			// cout<<f[i][j]<<" ";
		}
		// cout<<"\n";
	}
	printf("%lld\n",f[n][m]);
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