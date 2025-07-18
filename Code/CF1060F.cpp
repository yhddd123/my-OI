#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=510;
const int inf=1e9;

int n;
int head[maxn],tot=1;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
db C[maxn][maxn];
db dp[maxn][maxn];int siz[maxn];
db f[maxn],g[maxn],suf[maxn];
void dfs(int u,int fa){
    siz[u]=1;dp[u][1]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);
        suf[siz[v]+1]=0;for(int j=siz[v];j;j--)suf[j]=suf[j+1]+dp[v][j];
        for(int j=0;j<=siz[v];j++)g[j]=dp[v][j]*j+suf[j+1]/2.0;
        for(int j=1;j<=siz[u];j++){
            for(int k=0;k<=siz[v];k++){
                f[j+k]+=dp[u][j]*g[k]*C[j-1+k][k]*C[siz[u]-j+siz[v]-k][siz[v]-k];
            }
        }
        siz[u]+=siz[v];
        for(int j=1;j<=siz[u];j++)dp[u][j]=f[j],f[j]=0;
    }
    // cout<<u<<"\n";
    // for(int i=1;i<=siz[u];i++)cout<<dp[u][i]<<" ";cout<<"\n";
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    for(int i=0;i<=n;i++){
        C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    for(int i=1;i<=n;i++){
        dfs(i,0);
        db ans=dp[i][1];
        for(int j=1;j<n;j++)ans=ans/j;
        printf("%.10Lf\n",ans);
    }
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}