#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=55;
const int inf=1e9;
bool mbe;

int op,n,m,a,b,c;
pii operator+(pii u,pii v){return {(u.fi+v.fi)%mod,(u.se+v.se)%mod};}
pii operator-(pii u,pii v){return {(u.fi+mod-v.fi)%mod,(u.se+mod-v.se)%mod};}
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,(u.fi*v.se+u.se*v.fi)%mod};}
pii mkp(int u,int v){return make_pair(u,u*v%mod);}
pii f[maxn][maxn],g[maxn][maxn],h[maxn][maxn];
pii sf[maxn][maxn],sg[maxn][maxn][maxn];
int C[maxn][maxn];
void work(){
    op=read();n=read();m=read();a=read();b=read();c=read();
    for(int i=0;i<maxn;i++){
        C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    f[1][0]={1,0};
    for(int i=1;i<=n;i++){
    	for(int j=i-1;j<=m;j++){
	        for(int k=1;k<i;k++){
	            for(int l=k-1;l<j;l++)sf[i][j]=sf[i][j]+mkp(C[i][k]*C[j-1][l]%mod,0)*mkp(k*k,0)*mkp(j,a)*f[k][l]*sf[i-k][j-l-1];
	        }
    	}
        for(int j=i;j<=m;j++){
			f[i][j]=f[i][j-1]*mkp(i*(i+1)/2,b)+sf[i][j-1]*mkp((mod+1)/2,c);
            // cout<<i<<" "<<j<<" "<<f[i][j].fi<<" "<<f[i][j].se<<"\n";
        }
        for(int j=i-1;j<=m;j++)sf[i][j]=sf[i][j]+mkp(i*i,0)*f[i][j];
    }
    if(op==1){printf("%lld\n",f[n][m].se);return ;}
    for(int i=1;i<=n;i++){
    	for(int j=i-1;j<=m;j++){
    		g[i][j]=f[i][j];
    		for(int k=1;k<i;k++){
    			for(int l=(k==1?0:k);l<j;l++){
    				for(int d=1,pw=k;k+d<=i&&l+d<=j;d++,pw=pw*k%mod){
    					g[i][j]=g[i][j]+mkp(C[i-1][k-1]*C[j][l]%mod*C[j-l][d]%mod,0)*mkp(pw,d*a%mod)*f[k][l]*sg[i-k][j-l-d][d];
    				}
    			}
    		}
    		sg[i][j][1]=sg[i][j][1]+g[i][j]*mkp(i,0);
    	}
    	for(int j=0;j<=m;j++){
    		for(int d=2;d<=i;d++){
    			for(int k=1;k<i;k++){
    				for(int l=k-1;l<=j;l++){
    					sg[i][j][d]=sg[i][j][d]+mkp(C[i][k]*C[j][l]%mod,0)*mkp(k,0)*g[k][l]*sg[i-k][j-l][d-1];
    				}
    			}
    		}
    	}
    }
    // printf("%lld\n",g[n][m].se);
    h[0][0]={1,0};
    for(int i=1;i<=n;i++){
    	for(int j=0;j<=m;j++){
    		for(int k=1;k<=i;k++){
    			for(int l=k-1;l<=j;l++)h[i][j]=h[i][j]+mkp(C[i-1][k-1]*C[j][l]%mod,0)*g[k][l]*h[i-k][j-l];
    		}
    	}
    }
    printf("%lld\n",h[n][m].se);
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