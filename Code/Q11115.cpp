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

int n,m;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
vector<int> g[maxn];int scct;
int st[maxn],tp;
int dfn[maxn],lw[maxn],idx;
void tar(int u){
    dfn[u]=lw[u]=++idx;st[++tp]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(!dfn[v]){
            tar(v);
            lw[u]=min(lw[u],lw[v]);
            if(lw[v]>=dfn[u]){
                g[++scct].clear();
                g[scct].pb(st[tp]),g[st[tp]].pb(scct);
                while(st[tp--]!=v){
                    g[scct].pb(st[tp]),g[st[tp]].pb(scct);
                }
                g[scct].pb(u),g[u].pb(scct);
            }
        }
        else lw[u]=min(lw[u],dfn[v]);
    }
}
int siz[maxn];
void dfs(int u,int fa){
    siz[u]=(u<=n);
    for(int v:g[u]){
        if(v==fa)continue;
        dfs(v,u);siz[u]+=siz[v];
    }
}
int f[maxn];
int fd(int x){
    if(f[x]==x)return x;
    return f[x]=fd(f[x]);
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)head[i]=dfn[i]=0,g[i].clear();tot=0;
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
        f[fd(u)]=fd(v);
    }
    idx=tp=0;scct=n;tar(1);
    int num=0;for(int i=1;i<=n;i++)if(f[i]==i)++num;
    if(num>2){puts("No");return ;}
    if(num==2){
        num=0;for(int i=1;i<=n;i++)if(fd(i)==fd(1))++num;
        if(num%3==2){puts("Yes");return ;}
        else{puts("No");return ;}
    }
    dfs(1,0);
    for(int u=n+1;u<=scct;u++){
        for(int v:g[u])if(siz[v]<=siz[u]&&siz[v]%3==2){puts("Yes");return ;}
        if((n-siz[u])%3==2){puts("Yes");return ;}
        int num=0;for(int v:g[u])if(siz[v]<=siz[u])num+=(siz[v]%3==1);
        num+=((n-siz[u])%3==1);
        if(num>=4){puts("Yes");return ;}
    }
    puts("No");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}