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
const int maxn=5010;
const int inf=1e9;
bool Mbe;

int n,k,a[maxn],ans;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dp[maxn][7][1<<7][2],f[7][1<<7][2],siz[maxn],sum[1<<7];
void dfs(int u,int fa){
    for(int i=0;i<k;i++)dp[u][i][0][0]=1;
    siz[u]=1;
    for(int ii=head[u];ii;ii=e[ii].nxt){
        int v=e[ii].to;if(v==fa)continue;
        dfs(v,u);siz[u]+=siz[v];
        for(int i=0;i<k;i++){
            for(int s=0;s<(1<<k);s++)if(!(s&(1<<i))){
                for(int op:{0,1})if(dp[u][i][s][op]){
                    int ss=(1<<k)-1-s;
                    for(int j=0;j<k;j++){
                        for(int t=ss;;t=(t-1)&ss)if(!(t&(1<<i))){
                            if(i==j){
                                for(int fl:{0,1})if(!(op&fl)){
                                    (f[i][s|t][op|fl]+=dp[u][i][s][op]*dp[v][j][t][fl])%=mod;
                                }
                            }
                            else if((t&(1<<j))&&!(op&(j>i))){
                                for(int fl:{0,1})if(fl+(i>j)==(j<k-1)){
                                    (f[i][s|t][op|(j>i)]+=dp[u][i][s][op]*dp[v][j][t][fl])%=mod;
                                }
                            }
                            if(!t)break;
                        }
                    }
                }
            }
        }
        for(int i=0;i<k;i++){
            for(int s=0;s<(1<<k);s++)if(!(s&(1<<i))){
                for(int op:{0,1}){
                    dp[u][i][s][op]=f[i][s][op],f[i][s][op]=0;
                }
            }
        }
    }
    for(int i=0;i<k;i++){
        for(int s=0;s<(1<<k);s++)if(!(s&(1<<i))){
            for(int op:{0,1})if(dp[u][i][s][op]){
                if(siz[u]>sum[s|(1<<i)])dp[u][i][s][op]=0;
                else if(siz[u]==sum[s|(1<<i)])dp[u][i][s|(1<<i)][op]=dp[u][i][s][op],dp[u][i][s][op]=0;
            }
        }
    }
    // for(int i=0;i<k;i++){
    //     for(int s=0;s<(1<<k);s++){
    //         for(int op:{0,1})if(dp[u][i][s][op]){
    //             cout<<u<<" "<<i<<" "<<s<<" "<<op<<" "<<dp[u][i][s][op]<<"\n";
    //         }
    //     }
    // }
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    k=read()+1;
    for(int i=1;i<k;i++)a[i]=read();
    a[0]=n,a[k]=0;
    for(int i=0;i<k;i++)a[i]=a[i]-a[i+1];
    // for(int i=0;i<k;i++)cout<<a[i]<<" ";cout<<"\n";
    for(int s=1;s<(1<<k);s++)sum[s]=sum[s^(s&(-s))]+a[__lg(s&(-s))];
    dfs(1,0);
    for(int i=0;i<k;i++)(ans+=dp[1][i][(1<<k)-1][i<k-1])%=mod;
    printf("%lld\n",ans);
}

bool Med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&Mbe-&Med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}