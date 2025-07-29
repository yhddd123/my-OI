#include<bits/stdc++.h>
// #define int long long
#define mod 10007ll
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
const int maxn=30010;
const int maxm=128;

int n,m,q,a[maxn];
int ans[2][maxm];
char op[10];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1;siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u;dfs(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],tim,tp[maxn],dw[maxn];
int f[maxn][2][maxm],g[maxn][maxm],w[maxn][maxm];
int ni[maxn];
pii h[maxn][maxm];
void add(pii &u,int v){
    if(v&&v!=mod)u.fi=u.fi*v%mod;
    else u.se++;
}
void del(pii &u,int v){
    if(v&&v!=mod)u.fi=u.fi*ni[v]%mod;
    else u.se--;
}
int val(pii u){return u.se?0:u.fi;}
void dfs(int u,int lst){
    rnk[dfn[u]=++tim]=u;tp[u]=lst;dw[u]=u;
    for(int i=0;i<m;i++)add(h[u][i],w[u][i]);
    if(son[u])dfs(son[u],lst),dw[u]=dw[son[u]];
    for(int ii=head[u];ii;ii=e[ii].nxt){
        int v=e[ii].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
        for(int i=0;i<m;i++){
            (g[u][i]+=f[v][0][i]+f[v][1][i])%=mod;
            add(h[u][i],f[v][1][i]+1);
        }
    }
    for(int i=0;i<m;i++){
        f[u][0][i]=(g[u][i]+f[son[u]][0][i]+f[son[u]][1][i])%mod;
        f[u][1][i]=1ll*val(h[u][i])*(f[son[u]][1][i]+1)%mod;
    }
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct mat{
    int a00,a01,a02,a11,a12,a22;
    mat(){a00=a01=a02=a11=a12=a22=0;}
};
mat operator*(const mat &u, const mat &v){
    mat res;
    res.a00 = (u.a00 * v.a00) % mod;
    res.a01 = (u.a00 * v.a01 + u.a01 * v.a11) % mod;
    res.a02 = (u.a00 * v.a02 + u.a01 * v.a12 + u.a02 * v.a22) % mod;
    res.a11 = (u.a11 * v.a11) % mod;
    res.a12 = (u.a11 * v.a12 + u.a12 * v.a22) % mod;
    res.a22 = (u.a22 * v.a22) % mod;
    return res;
}
mat tree[maxn<<2][maxm];
int lc[maxn<<2],rc[maxn<<2];
int rt[maxn],idx;
void build(int &nd,int l,int r){
	if(!nd)nd=++idx;
    if(l==r){
        int u=rnk[l];
        for(int i=0;i<m;i++){
            tree[nd][i].a00=tree[nd][i].a01=1,tree[nd][i].a02=g[u][i];
            tree[nd][i].a11=tree[nd][i].a12=val(h[u][i]);
            tree[nd][i].a22=1;
        }
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    for(int i=0;i<m;i++)tree[nd][i]=tree[ls][i]*tree[rs][i];
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        int u=rnk[l];
        for(int i=0;i<m;i++){
            tree[nd][i].a00=tree[nd][i].a01=1,tree[nd][i].a02=g[u][i];
            tree[nd][i].a11=tree[nd][i].a12=val(h[u][i]);
            tree[nd][i].a22=1;
        }
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    for(int i=0;i<m;i++)tree[nd][i]=tree[ls][i]*tree[rs][i];
}
void que(int u){
    for(int i=0;i<m;i++){
    	// cout<<tree[rt[u]][i].a[0][0]<<" "<<tree[rt[u]][i].a[0][1]<<" "<<tree[rt[u]][i].a[0][2]<<"\n";
    	// cout<<tree[rt[u]][i].a[1][0]<<" "<<tree[rt[u]][i].a[1][1]<<" "<<tree[rt[u]][i].a[1][2]<<"\n";
    	// cout<<tree[rt[u]][i].a[2][0]<<" "<<tree[rt[u]][i].a[2][1]<<" "<<tree[rt[u]][i].a[2][2]<<"\n";
        f[u][0][i]=tree[rt[u]][i].a02;
        f[u][1][i]=tree[rt[u]][i].a12;
    }
}
void upd(int u){
	modif(rt[tp[u]],dfn[tp[u]],dfn[dw[u]],dfn[u]);
}
void fwt(int *a,int n,int fl=1){
    for(int l=2;l<=n;l<<=1){
        int k=l>>1;
        for(int i=0;i<n;i+=l){
            for(int j=i;j<i+k;j++){
                int u=a[j],v=a[j+k];
                a[j]=(u+v)*fl%mod,a[j+k]=(u+mod-v)*fl%mod;
            }
        }
    }
}
void work(){
    n=read();m=read();
    ni[0]=ni[1]=1;for(int i=2;i<mod;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
    for(int i=1;i<=n;i++)a[i]=read(),w[i][a[i]]=1,fwt(w[i],m);
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++)h[i][j].fi=1;
    }
    dfs(1),dfs(1,1);
    for(int u=1;u<=n;u++)if(tp[u]==u)build(rt[u],dfn[u],dfn[dw[u]]);
    for(int i=1;i<=n;i++){
    	for(int j=0;j<m;j++)assert(h[i][j].fi);
    }
    q=read();
    while(q--){
        scanf("%s",op);
        if(op[0]=='Q'){
            int k=read();
            que(1);
		    for(int i=0;i<m;i++)ans[0][i]=f[1][0][i],ans[1][i]=f[1][1][i];
		    fwt(ans[0],m,(mod+1)/2),fwt(ans[1],m,(mod+1)/2);
		    printf("%d\n",(ans[0][k]+ans[1][k])%mod);
        }
        else{
            int u=read();
            for(int i=0;i<m;i++)del(h[u][i],w[u][i]);
            for(int i=0;i<m;i++)w[u][i]=0;
            a[u]=read();w[u][a[u]]=1;
            fwt(w[u],m,1);
            for(int i=0;i<m;i++)add(h[u][i],w[u][i]);
            upd(u);u=tp[u];
            while(fa[u]){
                for(int i=0;i<m;i++){
                    (g[fa[u]][i]+=2*mod-f[u][0][i]-f[u][1][i])%=mod;
                    del(h[fa[u]][i],f[u][1][i]+1);
                }
                que(u);
                for(int i=0;i<m;i++){
                    (g[fa[u]][i]+=f[u][0][i]+f[u][1][i])%=mod;
                    add(h[fa[u]][i],f[u][1][i]+1);
                }
                upd(fa[u]);
                u=tp[fa[u]];
            }
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}