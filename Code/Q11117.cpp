#include<bits/stdc++.h>
// #define int long long
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

int n,a[maxn],b[maxn],ans;
int f[maxn][maxn][maxn][maxn],g[maxn][maxn][maxn][maxn],h[maxn][maxn][maxn][maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
    for(int i=1;i<=n;i++)f[i][i][a[i]][b[i]]=h[i][i][a[i]][b[i]]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            for(int l=1;l<=i;l++){
                for(int r=j;r<=n;r++)if(h[i][j][l][r]){
                    // cout<<i<<" "<<j<<" "<<l<<" "<<r<<" "<<h[i][j][l][r]<<"\n";
                    for(int p=j+1;p<=n;p++)inc(h[i][p][min(l,a[p])][max(r,b[p])],h[i][j][l][r]);
                }
            }
        }
    }
    for(int i=n;i;i--){
        for(int j=i;j<=n;j++){
            for(int l=1;l<=i;l++){
                for(int r=j;r<=n;r++){
                    for(int p=j;p<=r;p++)g[j][l][r][p]=0;
                }
            }
        }
        for(int jj=i;jj<=n;jj++){
            for(int j=i;j<jj;j++){
                for(int l=1;l<=i;l++){
                    for(int r=j;r<=n;r++){
                        for(int p=j;p<=r;p++)if(g[j][l][r][p]){
                            for(int ii=j+1;ii<=jj;ii++){
                                for(int ll=1;ll<=ii;ll++){
                                    for(int rr=jj;rr<=n;rr++)if(f[ii][jj][ll][rr]){
                                        if(p<ii||ll>j){
                                            inc(g[jj][min(l,ll)][max(r,rr)][rr],1ll*g[j][l][r][p]*f[ii][jj][ll][rr]%mod);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for(int l=1;l<=i;l++){
                for(int r=jj;r<=n;r++){
                    f[i][jj][l][r]=h[i][jj][l][r];
                    for(int p=jj;p<=r;p++){
                        inc(f[i][jj][l][r],mod-g[jj][l][r][p]);
                    }
                    if(f[i][jj][l][r]){
                        // cout<<i<<" "<<jj<<" "<<l<<" "<<r<<" "<<f[i][jj][l][r]<<"\n";
                        inc(g[jj][l][r][r],f[i][jj][l][r]);
                        inc(ans,f[i][jj][l][r]);
                    }
                }
            }
        }
    }
    printf("%d\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}