#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=62;
const int inf=1e9;
bool mbe;

int n,mod;
int f[2][maxn][maxn][maxn][maxn],g[2][maxn][maxn][maxn][maxn],cur;
int sf[maxn][maxn][maxn][maxn],sg[maxn][maxn][maxn][maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void updf(int j,int kl,int kr,int a,int b,int w){
	if(kl<=kr)inc(sf[j][kl][a][b],w),inc(sf[j][kr+1][a][b],mod-w);
}
void updg(int j,int kl,int kr,int a,int b,int w){
	if(kl<=kr)inc(sg[j][kl][a][b],w),inc(sg[j][kr+1][a][b],mod-w);
}
int ans[maxn][maxn];
void work(){
    n=read();mod=read();
    f[1][1][0][0][0]=1,g[1][0][1][1][0]=1,cur=1;
    for(int i=2;i<=n;i++){
    	// for(int j=1;j<=i;j++){
    		// for(int k=0;k<=i-j;k++){
    			// for(int a=0;a<=i;a++){
    				// for(int b=0;b<i;b++)f[i&1][j][k][a][b]=0;
    			// }
    		// }
    	// }
    	// for(int j=0;j<i;j++){
    		// for(int k=1;k<=i-j;k++){
    			// for(int a=0;a<=i;a++){
    				// for(int b=0;b<i;b++)g[i&1][j][k][a][b]=0;
    			// }
    		// }
    	// }
        for(int j=1;j<i;j++){
            for(int k=0;k<i-j;k++){
                for(int a=0;a<i;a++){
                    for(int b=0;b<i-1;b++){
                    	int v=f[cur][j][k][a][b];if(v){
                    		// cout<<i-1<<" "<<j<<" "<<k<<" "<<a<<" "<<b<<" "<<v<<" f\n";
                        // for(int l=1;l<=k;l++)(f[i&1][j+1][l-1][a][b+1]+=f[cur][j][k][a][b])%=mod;
                    	updf(j+1,0,k-1,a,b+1,v);
                        // for(int l=k+1;l<=i-j;l++)(f[i&1][j+1][l-1][a][b]+=f[cur][j][k][a][b])%=mod;
                        updf(j+1,k,i-j-1,a,b,v);
                        // for(int l=1;l<=i-j;l++)(g[i&1][j][l][a+1][b]+=f[cur][j][k][a][b])%=mod;
                        updg(j,1,i-j,a+1,b,v);
                        if(i-j-1){
                        // for(int l=1;l<=k;l++)(f[i&1][j+2][l-1][a][b+1]+=f[cur][j][k][a][b])%=mod;
                        updf(j+2,0,k-1,a,b+1,v);
                        // for(int l=k+1;l<=i-j-1;l++)(f[i&1][j+2][l-1][a][b]+=f[cur][j][k][a][b])%=mod;
                        updf(j+2,k,i-j-1-1,a,b,v);
                        // for(int l=1;l<=i-j-1;l++)(g[i&1][j+1][l][a+1][b]+=f[cur][j][k][a][b])%=mod;
                        updg(j+1,1,i-j-1,a+1,b,v);
                        }
	                    }
                    }
                }
            }
        }
        for(int j=0;j<i-1;j++){
            for(int k=1;k<i-j;k++){
                for(int a=0;a<i;a++){
                    for(int b=0;b<i-1;b++){
                    	int v=g[cur][j][k][a][b];if(v){
                    		// cout<<i-1<<" "<<j<<" "<<k<<" "<<a<<" "<<b<<" "<<v<<" g\n";
                        // for(int l=1;l<=i-j;l++)(f[i&1][j+1][l-1][a][b+1]+=g[cur][j][k][a][b])%=mod;
                        updf(j+1,0,i-j-1,a,b+1,v);
                        // for(int l=1;l<=k;l++)(g[i&1][j][l][a+1][b+1]+=g[cur][j][k][a][b])%=mod;
                        updg(j,1,k,a+1,b+1,v);
                        // for(int l=k+1;l<=i-j;l++)(g[i&1][j][l][a+1][b]+=g[cur][j][k][a][b])%=mod;
                        updg(j,k+1,i-j,a+1,b,v);
                        // for(int l=1;l<=i-j-1;l++)(f[i&1][j+2][l-1][a][b+1]+=g[cur][j][k][a][b])%=mod;
                        updf(j+2,0,i-j-1-1,a,b+1,v);
                        // for(int l=1;l<k;l++)(g[i&1][j+1][l][a+1][b+1]+=g[cur][j][k][a][b])%=mod;
                        updg(j+1,1,k-1,a+1,b+1,v);
                        // for(int l=k;l<i-j;l++)(g[i&1][j+1][l][a+1][b]+=g[cur][j][k][a][b])%=mod;
                        updg(j+1,k,i-j-1,a+1,b,v);
                    	}
                    }
                }
            }
        }
    	for(int j=1;j<=i;j++){
    		for(int k=1;k<=i-j;k++){
    			for(int a=0;a<=i;a++){
    				for(int b=0;b<i;b++)inc(sf[j][k][a][b],sf[j][k-1][a][b]);
    			}
    		}
    	}
    	for(int j=0;j<i;j++){
    		for(int k=2;k<=i-j;k++){
    			for(int a=0;a<=i;a++){
    				for(int b=0;b<i;b++)inc(sg[j][k][a][b],sg[j][k-1][a][b]);
    			}
    		}
    	}
    	for(int j=1;j<=i;j++){
    		for(int k=0;k<=i-j;k++){
    			for(int a=0;a<=i;a++){
    				for(int b=0;b<i;b++)f[i&1][j][k][a][b]=sf[j][k][a][b],sf[j][k][a][b]=0;
    			}
    		}
			for(int a=0;a<=i;a++){
				for(int b=0;b<i;b++)sf[j][i-j+1][a][b]=0;
			}
    	}
    	for(int j=0;j<i;j++){
    		for(int k=1;k<=i-j;k++){
    			for(int a=0;a<=i;a++){
    				for(int b=0;b<i;b++)g[i&1][j][k][a][b]=sg[j][k][a][b],sg[j][k][a][b]=0;
    			}
    		}
			for(int a=0;a<=i;a++){
				for(int b=0;b<i;b++)sg[j][i-j+1][a][b]=0;
			}
    	}
        cur^=1;
    }
    for(int a=0;a<n;a++){
        for(int b=0;b<n;b++){
            for(int k=0;k<n;k++)(ans[a][b]+=f[n&1][n][k][a][b])%=mod;
        }
    }
    for(int a=0;a<n;a++){
        for(int b=0;b<n;b++)printf("%lld ",ans[a][b]);puts("");
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}