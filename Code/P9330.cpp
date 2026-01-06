// Problem: P9330 [JOIST 2023] JOI 国的节日 2 / Festivals in JOI Kingdom 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9330
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2026-01-06 18:38:47
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=310;
const int inf=1e9;
bool mbe;

int n,mod;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn<<1],inv[maxn<<1];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int f[maxn<<1][maxn][maxn][4];
int calc(int n){return 1ll*fac[2*n]*inv[n]%mod*ksm(ksm(2,n))%mod;}
void work(){
	n=read();mod=read();init(2*n);
	f[0][0][0][0]=1;
	for(int i=1;i<=2*n+1;i++){
		for(int j=0;j<i&&j<=n;j++){
			for(int k=0;j+k<i&&k<=n;k++){
				// for(int o=0;o<=3;o++){
					// if(f[i-1][j][k][o])cout<<i-1<<" "<<j<<" "<<k<<" "<<o<<" "<<f[i-1][j][k][o]<<"\n";
				// }
				if(f[i-1][j][k][0]){
					int ff=f[i-1][j][k][0];
					inc(f[i][j][k+1][0],ff);
					if(j)inc(f[i][j-1][k][0],1ll*ff*j%mod);
					if(k){
						inc(f[i][j+k-1][0][0],ff);
						inc(f[i][j+k-1][0][1],1ll*ff*(k-1)%mod);
					}
				}
				if(f[i-1][j][k][1]){
					int ff=f[i-1][j][k][1];
					inc(f[i][j][k+1][2],ff);
					if(j){
						inc(f[i][j-1][k][0],ff);
						inc(f[i][j-1][k][1],1ll*ff*(j-1)%mod);
					}
				}
				if(f[i-1][j][k][2]){
					int ff=f[i-1][j][k][2];
					inc(f[i][j][k+1][2],ff);
					if(j){
						inc(f[i][j-1][k][3],ff);
						inc(f[i][j-1][k][2],1ll*ff*(j-1)%mod);
					}
				}
				if(f[i-1][j][k][3]){
					int ff=f[i-1][j][k][3];
					inc(f[i][j][k+1][0],ff);
					if(j)inc(f[i][j-1][k][3],1ll*ff*j%mod);
				}
			}
		}
	}
	printf("%lld\n",(calc(n)+mod-f[2*n][0][0][0])%mod);
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