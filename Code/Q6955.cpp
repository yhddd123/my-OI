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
const int maxn=110;
const int maxk=15;
const int inf=1e9;

int n,m;
int a[maxn],b[maxn],w[maxn][maxn];
int f[maxn][maxn][maxk],g[maxn][maxk];
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)b[i]=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)w[i][j]=read();
    }
    memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
    for(int i=n;i;i--){
        f[i][i][0]=0;
        for(int j=i+1;j<=n;j++){
            for(int k=0;k<=m;k++){
                if(b[i]==b[j])f[i][j][k]=min(f[i][j][k],f[i][j-1][k]);
                else if(k)f[i][j][k]=min(f[i][j][k],f[i][j-1][k-1]);
                for(int p=i;p<j;p++){
                    for(int kk=0;kk<=k;kk++)f[i][j][k]=min(f[i][j][k],f[i][p][kk]+f[p+1][j][k-kk]+w[b[p+1]][j-p]);
                }
            }
        }
    }
    g[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int k=0;k<=m;k++){
            if(a[i]==b[i])g[i][k]=min(g[i][k],g[i-1][k]);
            else if(k)g[i][k]=min(g[i][k],g[i-1][k-1]);
            for(int j=0;j<i;j++){
                for(int kk=0;kk<=k;kk++)g[i][k]=min(g[i][k],g[j][kk]+f[j+1][i][k-kk]+w[b[j+1]][i-j]);
            }
        }
    }
    for(int i=0;i<=m;i++)printf("%lld ",g[n][i]);puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}