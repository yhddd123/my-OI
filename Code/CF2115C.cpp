#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db double
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=22;
const int maxm=4010;
const int maxh=410;
const int inf=1e9;

int n,m;db p,ans;
int a[maxn];
db f[maxh][maxn][maxm],g[maxh][maxm],h[maxm][maxm];
void work(){
    n=read();m=read();p=read()/100.0;ans=0;
    for(int i=1;i<=n;i++)a[i]=read()-1;
    int x=a[1];for(int i=2;i<=n;i++)x=min(x,a[i]);
    int y=0;for(int i=1;i<=n;i++)y+=a[i]-x;
    if(x+y>m){puts("0");return ;}
    // cout<<x<<" "<<y<<"\n";
    for(int i=0;i<=x;i++)for(int j=0;j<=y;j++)g[i][j]=0;
    g[x][y]=1;
    for(int i=x;i;i--){
        for(int j=y;j;j--){
            g[i-1][j]+=g[i][j]*p;
            g[i][j-1]+=g[i][j]*(1-p);
        }
    }
    for(int i=0;i<=m;i++){
        h[i][0]=1;
        for(int j=1;j<=i;j++)h[i][j]=h[i-1][j]*p+h[i-1][j-1]*(1-p);
    }
    for(int i=0;i<=y;i++)ans+=h[m-(x+y-i)][i]*g[0][i];
    for(int j=0;j<=n;j++)for(int k=0;k<=m-y;k++)f[0][j][k]=h[k][j];
    for(int i=0;i<=x;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<i+j;k++)f[i][j][k]=0;
        }
    }
    for(int i=1;i<=x;i++){
        for(int k=i;k<=m-y;k++){
            f[i][0][k]=f[i-1][0][k-1]*p+max(f[i][0][k-1],f[i-1][n-1][k-1])*(1-p);
        }
        for(int j=1;j<n;j++){
            for(int k=i+j;k<=m-y;k++){
                f[i][j][k]=f[i-1][j][k-1]*p+f[i][j-1][k-1]*(1-p);
            }
        }
    }
    for(int i=1;i<=x;i++)ans+=f[i][0][m-(x+y-i)]*g[i][0];
    printf("%.10lf\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}