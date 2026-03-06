// Problem: AT_agc055_d [AGC055D] ABC Ultimatum
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc055_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-03-05 17:18:10
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=17;
bool mbe;

int n,ans;
char s[maxn*3];
int f[maxn*3][maxn][maxn][2][2];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();scanf("%s",s+1);
	for(int mxa=0;mxa<=n;mxa++){
		for(int mxb=0;mxa+mxb<=n;mxb++){
			int mxc=n-mxa-mxb;
			mems(f[0][0][0],0);f[0][0][0][mxa==0][mxb==0]=1;
			for(int i=1;i<=3*n+1;i++){
				for(int j=0;j<=i&&j<=n;j++){
					for(int k=0;j+k<=i&&k<=n;k++)mems(f[i][j][k],0);
				}
				for(int j=0;j<i&&j<=n;j++){
					for(int k=0,v;j+k<i&&k<=n;k++){
						for(int o1:{0,1}){
							for(int o2:{0,1})if(v=f[i-1][j][k][o1][o2]){
								// cout<<i-1<<" "<<j<<" "<<k<<" "<<o1<<" "<<o2<<"\n";
								if(s[i]=='A'||s[i]=='?'){
									if(j-(i-1-j-k)+1<=mxa){
										inc(f[i][j+1][k][(j-(i-1-j-k)+1==mxa)|o1][o2],v);
									}
								}
								if(s[i]=='B'||s[i]=='?'){
									if(k-j+1<=mxb){
										inc(f[i][j][k+1][o1][(k-j+1==mxb)|o2],v);
									}
								}
								if(s[i]=='C'||s[i]=='?'){
									if((i-1-j-k)-k+1<=mxc){
										inc(f[i][j][k][o1][o2],v);
									}
								}
							}
						}
					}
				}
			}
			inc(ans,f[3*n][n][n][1][1]);
			// cout<<mxa<<" "<<mxb<<" "<<mxc<<" "<<ans<<"\n";
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