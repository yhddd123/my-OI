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
const int maxn=200010;
const int inf=1e9;

int n,m,ans;
char s[maxn];
int to[maxn][27],idx=1;
int du[maxn],edp[maxn],id[maxn],dep[maxn];
int fr[maxn],fa[maxn];
vector<int> e[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1;
    for(int v:e[u])fa[v]=u,dfs(v);
}
int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]>dep[v])u=fa[u];
    while(u!=v)u=fa[u],v=fa[v];
    return u;
}
int x[maxn],y[maxn];
int hd[maxn],tl[maxn],siz[maxn],pre[maxn],nxt[maxn],st[maxn],ed[maxn];
int a[maxn],tp;
void dfs1(int u){
    if(id[u])a[++tp]=id[u];
    vector<int> son;
    for(int v:e[u])if(hd[v]==v)son.pb(v);
    sort(son.begin(),son.end(),[&](int v1,int v2){
        return ((v1==st[u])?-1:(tl[v1]==ed[u]?1:0))<((v2==st[u])?-1:(tl[v2]==ed[u]?1:0));
    });
    for(int v:son){
        for(int vv=hd[v];vv;vv=nxt[vv])dfs1(vv);
    }
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);int m=strlen(s+1);s[++m]='z'+1;
        int u=1;for(int j=1;j<=m;j++){
            int c=s[j]-'a';
            if(!to[u][c])to[u][c]=++idx,dep[to[u][c]]=dep[u]+1,du[u]++;
            u=to[u][c];
        }
        edp[i]=u,id[u]=i;
    }
    for(int i=1;i<=idx;i++)if(du[i]>=2)ans+=dep[i]*dep[i]*(du[i]-1);
    printf("%lld\n",ans);
    for(int i=idx;i>1;i--){
        if(du[i]==1){
            for(int j=0;j<=26;j++)if(to[i][j])fr[i]=fr[to[i][j]];
        }
        else{
            fr[i]=i;
            for(int j=0;j<=26;j++)if(to[i][j])e[i].pb(fr[to[i][j]]);
        }
    }
    for(int j=0;j<=26;j++)if(to[1][j])e[1].pb(fr[to[1][j]]);
    dfs(1);
    for(int i=1;i<=m;i++)x[i]=read(),y[i]=read();
    for(int i=1;i<=idx;i++)hd[i]=tl[i]=i,siz[i]=1;
    vector<int> id;
    for(int i=m;i;i--){
        int u=edp[x[i]],v=edp[y[i]],tp=lca(u,v),x=u,y=v;
        bool fl=1;
        while(fa[x]!=tp){
            if(ed[fa[x]]&&ed[fa[x]]!=x)fl=0;
            if(nxt[x])fl=0;
            if(st[fa[x]]==hd[x]&&siz[x]<du[fa[x]])fl=0;
            x=fa[x];
        }
        while(fa[y]!=tp){
            if(st[fa[y]]&&st[fa[y]]!=y)fl=0;
            if(pre[y])fl=0;
            if(ed[fa[y]]==tl[y]&&siz[y]<du[fa[y]])fl=0;
            y=fa[y];
        }
        if(nxt[x]&&nxt[x]!=y)fl=0;
        if(pre[y]&&pre[y]!=x)fl=0;
        if(x==ed[tp]||y==st[tp])fl=0;
        if(!nxt[x]){
            if(hd[x]==hd[y])fl=0;
            if(hd[x]==st[tp]&&tl[y]==ed[tp]&&siz[x]+siz[y]<du[tp])fl=0;
        }
        if(fl){
            id.pb(i);
            x=u,y=v;
            while(fa[x]!=tp){
                ed[fa[x]]=x;
                x=fa[x];
            }
            while(fa[y]!=tp){
                st[fa[y]]=y;
                y=fa[y];
            }
            if(nxt[x]!=y){
                int hh=hd[x],tt=tl[y],ss=siz[x]+siz[y];
                nxt[x]=y,pre[y]=x;for(int p=hd[x];p;p=nxt[p])hd[p]=hh,tl[p]=tt,siz[p]=ss;
            }
        }
    }
    reverse(id.begin(),id.end());
    printf("%lld ",id.size());for(int u:id)printf("%lld ",u);puts("");
    dfs1(1);
    for(int i=1;i<=n;i++)printf("%lld ",a[i]);puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}