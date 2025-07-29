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
const int maxn=120010;
const int inf=1e9;
bool mbe;

int n,a[maxn],q;
int lc[maxn],rc[maxn],siz[maxn],w[maxn],rt,idx;
bool fl[maxn];
int val[maxn],mn[maxn],mx[maxn],smn[maxn],smx[maxn];
mt19937 rnd(time(0));
int newnode(int v){
    int u=++idx;
    siz[u]=1;w[u]=rnd();
    val[u]=mn[u]=mx[u]=v,smn[u]=n+1,smx[u]=0;
    return idx;
}
int findr(int u,int v){
    if(mx[u]<=v)return 0;
    if(mx[rc[u]]>v)return findr(rc[u],v);
    if(val[u]>v)return val[u];
    return findr(lc[u],v);
}
int findl(int u,int v){
    if(mn[u]>=v)return n+1;
    if(mn[lc[u]]<v)return findl(lc[u],v);
    if(val[u]<v)return val[u];
    return findl(rc[u],v);
}
void up(int u){
    siz[u]=siz[lc[u]]+siz[rc[u]]+1;
    fl[u]=fl[lc[u]]|fl[rc[u]]|(smn[lc[u]]<mx[rc[u]])|(mn[lc[u]]<smx[rc[u]]);
    fl[u]|=(mn[lc[u]]<val[u]&&val[u]<mx[rc[u]])|(smn[lc[u]]<val[u])|(val[u]<smx[rc[u]]);
    mn[u]=min({mn[lc[u]],val[u],mn[rc[u]]});
    mx[u]=max({mx[lc[u]],val[u],mx[rc[u]]});
    if(fl[u])return ;
    smn[u]=min(smn[lc[u]],smn[rc[u]]);
    if(val[u]>mn[lc[u]])smn[u]=min(smn[u],val[u]);
    int v=findr(rc[u],min(mn[lc[u]],val[u]));
    if(v)smn[u]=min(smn[u],v);
    smx[u]=max(smx[lc[u]],smx[rc[u]]);
    if(val[u]<mx[rc[u]])smx[u]=min(smx[u],val[u]);
    v=findl(lc[u],max(mx[rc[u]],val[u]));
    if(v<=n)smx[u]=max(smx[u],v);
}
int merge(int u,int v){
    if(!u||!v)return u|v;
    if(w[u]<w[v]){
        rc[u]=merge(rc[u],v);
        up(u);return u;
    }
    else{
        lc[v]=merge(u,lc[v]);
        up(v);return v;
    }
}
pii split(int u,int k){
    if(!u)return {0,0};
    if(siz[lc[u]]+1<=k){
        pii t=split(rc[u],k-siz[lc[u]]-1);
        rc[u]=t.fi;up(u);return {u,t.se};
    }
    else{
        pii t=split(lc[u],k);
        lc[u]=t.se;up(u);return {t.fi,u};
    }
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    mn[0]=smn[0]=n+1;
    for(int i=1;i<=n;i++)rt=merge(rt,newnode(a[i]));
    q=read();
    while(q--){
        int l=read(),r=read(),k=read(),a,b,c,d;
        pii t=split(rt,r);c=t.fi,d=t.se;
        t=split(c,r-k);b=t.fi,c=t.se;
        t=split(b,l-1);a=t.fi,b=t.se;
        rt=merge(a,merge(c,merge(b,d)));
        puts(fl[rt]?"YES":"NO");
    }
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