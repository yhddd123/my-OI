#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=400010;
const int inf=1e9;


int n,rt,a[maxn],ans;
int lsh[maxn],len;
vector<int> pos[maxn];
int ni[maxn];
bool b[maxn];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1;siz[u]=1;son[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u;dfs(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],tim,tp[maxn],dw[maxn];
int f[maxn],fb[maxn],fg[maxn],g[maxn],sum[maxn],cnt[maxn];
bool vis[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++tim]=u;tp[u]=lst;dw[u]=u;
    if(!son[u])return ;
    dfs(son[u],lst),dw[u]=dw[son[u]];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
    }
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void dfs1(int u){
	vis[u]=b[u]=1;
    if(son[u])dfs1(son[u]);
    f[u]=g[u]=sum[u]=fg[u]=fb[u]=cnt[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs1(v);
        inc(g[u],sum[v]);
        inc((vis[v]?fg[u]:fb[u]),f[v]);
    }
    f[u]=(1ll*ni[cnt[u]+1]*fg[u]+1ll*ni[cnt[u]]*fb[u]+1ll*ni[cnt[u]+vis[son[u]]]*f[son[u]]+1)*b[u]%mod;
    inc(sum[u]=f[u],g[u]);inc(sum[u],sum[son[u]]);
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct mat{
	int e[3][3];
	mat(){memset(e,0,sizeof(e));}
}tree[maxn<<2];
int lc[maxn<<2],rc[maxn<<2];
int trt[maxn],idx;
mat operator*(mat u,mat v){
    mat res;
    res.e[0][0]=(1ll*u.e[0][0]*v.e[0][0])%mod;
    res.e[0][1]=(1ll*u.e[0][0]*v.e[0][1]+1ll*u.e[0][1]*v.e[1][1])%mod;
    res.e[0][2]=(1ll*u.e[0][0]*v.e[0][2]+1ll*u.e[0][1]*v.e[1][2]+1ll*u.e[0][2]*v.e[2][2])%mod;
    res.e[1][1]=(1ll*u.e[1][1]*v.e[1][1])%mod;
    res.e[1][2]=(1ll*u.e[1][1]*v.e[1][2]+1ll*u.e[1][2]*v.e[2][2])%mod;
    res.e[2][2]=(1ll*u.e[2][2]*v.e[2][2])%mod;
    return res;
}
void build(int &nd,int l,int r){
	if(!nd)nd=++idx;
    if(l==r){
        int u=rnk[l];
        tree[nd]=mat();
        tree[nd].e[0][0]=1;
        tree[nd].e[0][1]=ni[cnt[u]+vis[son[u]]]*b[u];
        tree[nd].e[0][2]=((1ll*ni[cnt[u]+1]*fg[u]+1ll*ni[cnt[u]]*fb[u]+1)*b[u]+g[u])%mod;
        tree[nd].e[1][1]=ni[cnt[u]+vis[son[u]]]*b[u];
        tree[nd].e[1][2]=(1ll*ni[cnt[u]+1]*fg[u]+1ll*ni[cnt[u]]*fb[u]+1)*b[u]%mod;
        tree[nd].e[2][2]=1;
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]*tree[rs];
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        int u=rnk[l];
        tree[nd]=mat();
        tree[nd].e[0][0]=1;
        tree[nd].e[0][1]=ni[cnt[u]+vis[son[u]]]*b[u];
        tree[nd].e[0][2]=((1ll*ni[cnt[u]+1]*fg[u]+1ll*ni[cnt[u]]*fb[u]+1)*b[u]+g[u])%mod;
        tree[nd].e[1][1]=ni[cnt[u]+vis[son[u]]]*b[u];
        tree[nd].e[1][2]=(1ll*ni[cnt[u]+1]*fg[u]+1ll*ni[cnt[u]]*fb[u]+1)*b[u]%mod;
        tree[nd].e[2][2]=1;
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    tree[nd]=tree[ls]*tree[rs];
}
mat query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return query(ls,l,mid,ql,qr)*query(rs,mid+1,r,ql,qr);
}
void que(int u){
	mat res=tree[trt[u]];
	sum[u]=res.e[0][2],f[u]=res.e[1][2];
}
void upd(int u){
	modif(trt[tp[u]],dfn[tp[u]],dfn[dw[u]],dfn[u]);
}
void modif(int u){
	upd(u);
	u=tp[u];
	while(fa[u]){
		inc(g[fa[u]],mod-sum[u]);
		inc((vis[u]?fg[fa[u]]:fb[fa[u]]),mod-f[u]);
		que(u);
		inc(g[fa[u]],sum[u]);
		inc((vis[u]?fg[fa[u]]:fb[fa[u]]),f[u]);
		upd(fa[u]);
		u=tp[fa[u]];		
	}
}
void work(){
    n=read();rt=read();ans=0;
    for(int i=1;i<=n;i++)a[i]=read();
    len=0;for(int i=1;i<=n;i++)lsh[++len]=a[i];
    sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
    for(int i=1;i<=len;i++)pos[i].clear();
    for(int i=1;i<=n;i++)pos[a[i]].pb(i);
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
    for(int i=1;i<=n;i++)head[i]=fa[i]=0;tot=0;
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    tim=0;dfs(rt),dfs(rt,rt);
	dfs1(rt);
	for(int i=1;i<=n;i++)trt[i]=0;
	while(idx)lc[idx]=rc[idx]=0,idx--;
	for(int u=1;u<=n;u++)if(tp[u]==u)build(trt[u],dfn[u],dfn[dw[u]]);
    for(int i=1;i<=len;i++){
    	que(rt);
    	// cout<<sum[rt]<<" "<<lsh[i]<<"\n";
    	inc(ans,1ll*sum[rt]*(lsh[i]-lsh[i-1])%mod);
    	for(int u:pos[i]){
    		b[u]=0;modif(u);
    		while(vis[u]){
    			vis[u]=0;cnt[fa[u]]++;
    			if(u!=son[fa[u]]){
    				inc(fg[fa[u]],mod-f[u]);
    				inc(fb[fa[u]],f[u]);
    			}
    			modif(fa[u]);
    			u=fa[u];
    		}
    	}
    }
    printf("%d\n",ans);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}