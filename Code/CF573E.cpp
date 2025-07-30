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
bool mbe;

int n,a[maxn],ans;
int val[maxn],sum[maxn],tag[maxn];
#define ls lc[u]
#define rs rc[u]
int lc[maxn],rc[maxn],idx,rt,w[maxn],siz[maxn];
void upd(int u,int w){val[u]+=w,tag[u]+=w;}
void down(int u){upd(ls,tag[u]),upd(rs,tag[u]);tag[u]=0;}
void up(int u){siz[u]=siz[ls]+siz[rs]+1,sum[u]=sum[ls]+sum[rs]+val[u];}
int merge(int u,int v){
    if(!u||!v)return u|v;
    down(u),down(v);
    if(w[u]<w[v]){
        rs=merge(rs,v);
        up(u);return u;
    }
    else{
        lc[v]=merge(u,lc[v]);
        up(v);return v;
    }
}
pii split(int u,int i,int w){
    if(!u)return {0,0};
    down(u);
    // cout<<u<<" "<<w<<" "<<siz[ls]<<" "<<val[u]<<"\n";
    if(w*(i+siz[ls]+1)>val[u]){
        pii t=split(ls,i,w);
        ls=t.se;up(u);
        return {t.fi,u};
    }
    else{
        pii t=split(rs,i+siz[ls]+1,w);
        rs=t.fi;up(u);
        return {u,t.se};
    }
}
mt19937 rnd(1);
int newnode(int v){
    int u=++idx;
    siz[u]=1,w[u]=rnd();val[u]=sum[u]=v;
    return u;
}
int f[maxn],m;
void dfs(int u){
    down(u);
    if(ls)dfs(ls);
    f[++m]=val[u];
    if(rs)dfs(rs);
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++){
        auto[x,y]=split(rt,0,a[i]);
        // cout<<siz[x]<<" "<<siz[y]<<"\n";
        y=merge(newnode(siz[x]*a[i]),y);
        upd(y,a[i]);
        rt=merge(x,y);
        // m=0;dfs(rt);
        // for(int j=1;j<=m;j++)f[j]+=f[j-1];
        // for(int j=1;j<=m;j++)cout<<f[j]<<" ";cout<<"\n";
    }
    m=0;dfs(rt);
    for(int i=1;i<=m;i++)f[i]+=f[i-1];
    // for(int i=1;i<=m;i++)cout<<f[i]<<" ";cout<<"\n";
    for(int i=1;i<=m;i++)ans=max(ans,f[i]);
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}