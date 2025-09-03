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
const int maxn=1000010;
const int inf=1e9;

int n,a[maxn];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],idx,st[20][maxn];
void dfs(int u,int fa){
    st[0][dfn[u]=++idx]=fa;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);
    }
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
    if(u==v)return u;
    u=dfn[u],v=dfn[v];
    if(u>v)swap(u,v);u++;
    int k=__lg(v-u+1);
    return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int f[maxn];
void dfs1(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs1(v,u);f[u]+=f[v];
    }
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)head[i]=0;tot=0;
    for(int i=2;i<=n;i++){
        int p=read();
        add(p,i),add(i,p);
    }
    for(int i=2;i<=n;i++)a[i]=read();
    idx=0;dfs(1,0);
    for(int j=1;j<20;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    for(int i=1;i<=n;i++)f[i]=0;
    for(int i=2;i<=n;i++){
        int u=read(),v=i;
        f[u]++,f[v]++,f[lca(u,v)]-=2;
    }
    dfs1(1,0);
    int ans=0;for(int i=2;i<=n;i++)if(f[i]>=2&&a[i])++ans;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}