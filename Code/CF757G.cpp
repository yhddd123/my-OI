#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];ll ans;
int head[maxn],tot;
struct nd{
    int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int fa[maxn],dep[maxn],siz[maxn],son[maxn];ll dis[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u,dis[v]=dis[u]+e[i].w;dfs(v),siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],tim,tp[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++tim]=u;tp[u]=lst;
    if(!son[u])return ;dfs(son[u],lst);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
    }
}
ll sum[maxn],pre[maxn];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
const int maxm=maxn*180;
int lc[maxm],rc[maxm],idx,rt[maxn],tmp;
int tag[maxm];ll tree[maxm];
void updata(int &nd,int l,int r,int ql,int qr){
    int lst=nd;
    if(lst<=tmp)nd=++idx,tree[nd]=tree[lst],tag[nd]=tag[lst],ls=lc[lst],rs=rc[lst];
    if(l>=ql&&r<=qr){tag[nd]++,tree[nd]+=sum[r]-sum[l-1];return ;}
    if(ql<=mid)updata(ls,l,mid,ql,qr);
    if(qr>mid)updata(rs,mid+1,r,ql,qr);
    tree[nd]=tree[ls]+tree[rs]+(sum[r]-sum[l-1])*tag[nd];
}
ll query(int nd,int l,int r,int ql,int qr){
	if(!nd)return 0;
    if(l>=ql&&r<=qr)return tree[nd];
    ll res=(sum[min(r,qr)]-sum[max(l,ql)-1])*tag[nd];
    if(ql<=mid)res+=query(ls,l,mid,ql,qr);
    if(qr>mid)res+=query(rs,mid+1,r,ql,qr);
    return res;
}
void upd(int id,int u){
	tmp=idx;
    while(u){
        updata(rt[id],1,n,dfn[tp[u]],dfn[u]);
        // cout<<u<<" "<<tp[u]<<" "<<tree[rt[id]]<<"\n";
        u=fa[tp[u]];
    }
}
ll que(int id,int u){
    ll res=0;
    while(u){
        res+=query(rt[id],1,n,dfn[tp[u]],dfn[u]);
        // cout<<u<<" "<<tp[u]<<" "<<reRs<<"\n";
        u=fa[tp[u]];
    }
    return res;
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    dfs(1),dfs(1,1);
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+dis[rnk[i]]-dis[fa[rnk[i]]];
    for(int i=1;i<=n;i++)pre[i]=pre[i-1]+dis[a[i]];
    for(int i=1;i<=n;i++)rt[i]=rt[i-1],upd(i,a[i]);
    while(q--){
        int op=read();
        if(op==1){
            int l=read()^ans,r=read()^ans,x=read()^ans;
            ans=dis[x]*(r-l+1)+pre[r]-pre[l-1]-2*(que(r,x)-que(l-1,x));
            // cout<<dis[x]<<" "<<pre[r]-pre[l-1]<<"\n";
            write(ans),puts("");ans&=(1<<30)-1;
        }
        else{
            int x=read()^ans;swap(a[x],a[x+1]);
            pre[x]=pre[x-1]+dis[a[x]];
            if(idx>=maxn*179){
            	while(idx)tree[idx]=tag[idx]=lc[idx]=rc[idx]=0,idx--;
    			for(int i=1;i<=n;i++)rt[i]=rt[i-1],upd(i,a[i]);
            }
            else{
	            rt[x]=rt[x-1];upd(x,a[x]);
            }
        }
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}