#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=510;
const int maxk=110;
const int maxm=5010;
const int inf=1e9;
bool mbe;

int ans[maxn][maxm];
int n,m,K=70,cur;
int f[2][maxk][maxm][2];
void work(){
    n=500,m=5000;
    f[0][0][0][0]=1;
    for(int i=1;i<=n;i++){
        memset(f[i&1],0,sizeof(f[i&1]));
        for(int j=0;j<=K;j++){
            for(int k=0;k+j<=m;k++){
                for(int op=0;op<2;op++)if(f[cur][j][k][op]){
                    (f[i&1][j+1][k+j][op]+=f[cur][j][k][op])%=mod;
                    (f[i&1][j][k+j][op^1]+=f[cur][j][k][op])%=mod;
                    (f[i&1][j][k+j][op]+=f[cur][j][k][op]*2*j)%=mod;
                    if(j)(f[i&1][j-1][k+j][op]+=f[cur][j][k][op]*j*(j-1))%=mod;
                    if(j)(f[i&1][j-1][k+j][op^1]+=f[cur][j][k][op]*j)%=mod;
                }
            }
        }
        ans[i][0]=f[i&1][0][0][0];
        for(int k=1;k<=m;k++)ans[i][k]=(ans[i][k-1]+f[i&1][0][k][0])%mod;
        cur^=1;
    }
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    work();
    T=read();
    while(T--){
        n=read(),m=read();
        printf("%lld\n",ans[n][m]);
    }
}