// Problem: P14381 【MX-S9-T4】「LAOI-16」顽疾
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14381
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-11-28 18:51:42
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
const int maxn=55;
const int maxm=1010;
const int maxt=6;
const int inf=1e9;
bool mbe;

int n,m,w,t,sq,ans,id[maxm];
int f[maxn][maxn][maxt][maxt],g[maxn][maxn][maxt];
int fac[maxt]={1,1,2,6,24,120},inv[maxt]={1,1,500000004,166666668,41666667,808333339};
void work(){
	n=read();m=read();w=read();t=read();sq=sqrt(w);
	for(int i=1;i<=m;i++)id[i]=i;
	sort(id+1,id+m+1,[&](int u,int v){
		if(min(u,w/u)!=min(v,w/v))return min(u,w/u)<min(v,w/v);
		if(u>sq&&v>sq)return u>v;
		return u<v;
	});
	f[0][1][0][0]=1;
	for(int i=1;i<=m;i++){
		mems(g,0);
		if(id[i]<=sq){
			for(int j=0;j<n;j++){
				for(int k=1;k<=j+1;k++){
					for(int x=0;x<=t;x++){
						(g[j+1][k+1][x]+=g[j][k][x]*k)%=mod;
						for(int y=0;y<=t;y++){
							(g[j+1][k+1][x]+=f[j][k][y][x]*k*fac[t]%mod*inv[t-y])%=mod;
						}
					}
				}
			}
		}
		else{
			for(int j=0;j<n;j++){
				for(int k=j+1;k;k--){
					for(int x=0;x<=t;x++){
						(g[j+1][k-1][x]+=g[j][k][x]*k)%=mod;
						for(int y=0;y<=t;y++){
							(g[j+1][k-1][x]+=f[j][k][x][y]*k*fac[t]%mod*inv[t-y])%=mod;
						}
					}
				}
			}
		}
		for(int j=1;j<=n;j++){
			for(int k=0;k<=j+1;k++){
				for(int x=t;~x;x--){
					for(int y=t;~y;y--)if(f[j][k][x][y]){
						if(id[i]<=sq){
							if(j==n&&k==n+1)continue;
							for(int p=1;p<=t-x;p++)(f[j][k][x+p][y]+=f[j][k][x][y]*inv[p])%=mod;
						}
						else{
							if(k==j+1)continue;
							for(int p=1;p<=t-y;0++)(f[j][k][x][y+p]+=f[j][k][x][y]*inv[p])%=mod;
						}
					}
				}
			}
		}
		for(int j=0;j<=n;j++){
			for(int k=0;k<=j+1;k++){
				for(int x=0;x<=t;x++){
					for(int y=0;y<=t;y++){
						if(id[i]<=sq){
							(f[j][k][y][x]+=g[j][k][x]*inv[y])%=mod;
						}
						else{
							(f[j][k][x][y]+=g[j][k][x]*inv[y])%=mod;
						}
					}
				}
			}
		}
		// for(int j=0;j<=n;j++){
			// for(int k=1;k<=j+1;k++){
				// for(int x=0;x<=t;x++){
					// for(int y=0;y<=t;y++)if(f[j][k][x][y]){
						// cout<<i<<" "<<j<<" "<<k<<" "<<x<<" "<<y<<" "<<f[j][k][x][y]<<"\n";
					// }
				// }
			// }
		// }
	}
	for(int i=0;i<=n+1;i++){
		for(int j=0;j<=t;j++)(ans+=f[n][i][j][t-j]*fac[t])%=mod;
	}
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