#include<bits/stdc++.h>
#include <iostream>
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
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n,ans;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],f[maxn][maxn],g[maxn][maxn<<1][2];
int tmpf[maxn],tmpg[maxn<<1][2];
void dfs(int u,int fa){
    siz[u]=1,f[u][1]=1,g[u][-1+maxn][0]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);
        for(int j=1;j<=siz[u];j++){
            for(int k=1;k<=siz[v];k++)(tmpf[j+k]+=f[u][j]*f[v][k])%=mod;
        }
        for(int j=1;j<=siz[u]+siz[v];j++)(f[u][j]+=tmpf[j])%=mod,tmpf[j]=0;
        for(int j=-siz[u];j<=siz[u];j++){
            for(int k=1;k<=siz[v];k++){
                (tmpg[j+maxn-k][0]+=g[u][j+maxn][0]*f[v][k])%=mod;
                (tmpg[j+maxn-k][1]+=g[u][j+maxn][1]*f[v][k])%=mod;
                (tmpg[j+maxn+k][1]+=g[u][j+maxn][0]*f[v][k])%=mod;
            }
            for(int k=-siz[v];k<=siz[v];k++){
                (tmpg[j+maxn+k][1]+=g[u][j+maxn][0]*g[v][k+maxn][1])%=mod;
            }
        }
        for(int j=-siz[u]-siz[v];j<=siz[u]+siz[v];j++){
            (g[u][j+maxn][0]+=tmpg[j+maxn][0])%=mod,(g[u][j+maxn][1]+=tmpg[j+maxn][1])%=mod;
            tmpg[j+maxn][0]=tmpg[j+maxn][1]=0;
        }
        siz[u]+=siz[v];
    }
    for(int i=1;i<=siz[u];i++)(ans+=f[u][i])%=mod;
    (ans+=mod-g[u][maxn][1])%=mod;
    // cout<<u<<" "<<siz[u]<<" "<<g[u][maxn][1]<<" d\n";
    // for(int i=1;i<=siz[u];i++)cout<<f[u][i]<<" ";cout<<"\n";
}
void work(){
    n=read();ans=0;
    for(int i=1;i<=n;i++)head[i]=0;tot=0;
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1,0);
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=siz[i];j++)f[i][j]=0;
        for(int j=-siz[i];j<=siz[i];j++)g[i][j+maxn][0]=g[i][j+maxn][1]=0;
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}