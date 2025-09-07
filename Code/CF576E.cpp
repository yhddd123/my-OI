#include<bits/stdc++.h>
// #define int long long
#define tup tuple<int,int,int>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=500010;
const int maxk=50;
bool mbe;

int n,m,k,q;
pii st[maxn<<1];int tp;
struct bcj{
    int id,f[maxn<<1],siz[maxn<<1];
    int fd(int x){
        if(f[x]==x)return x;
        return fd(f[x]);
    }
    void merge(int u,int v){
        u=fd(u),v=fd(v);
        if(u==v)return ;
        if(siz[u]>siz[v])swap(u,v);
        siz[v]+=siz[u],f[u]=v,st[++tp]={id,u};
    }
    void init(int _i){
    	id=_i;
        for(int i=1;i<=2*n;i++)f[i]=i,siz[i]=1;
    }
    void del(int u){
        siz[f[u]]-=siz[u],f[u]=u;
    }
}t[maxk];
int lst[maxn],pre[maxn],nxt[maxn];
tup ask[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<int> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int w){
	// if(nd==1)cout<<ql<<" "<<qr<<" "<<(get<0>(w))<<" "<<(get<1>(w))<<" "<<(get<2>(w))<<" upd\n";
    if(ql>qr)return ;
    if(l>=ql&&r<=qr){tree[nd].pb(w);return ;}
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void dfs(int nd,int l,int r){
    int lst=tp;
    // cout<<l<<" "<<r<<" "<<tree[nd].size()<<"\n";
    for(int id:tree[nd]){
    	auto[u,v,w]=ask[id];
    	t[w].merge(u,v+n),t[w].merge(v,u+n);
    }
    if(l==r){
        auto[u,v,w]=ask[l];
        // cout<<l<<" "<<u<<" "<<v<<" "<<w<<" "<<t[w].fd(u)<<" "<<t[w].fd(v)<<"\n";
        // for(int i=1;i<=2*n;i++)cout<<t[w].fd(i)<<" ";cout<<"\n";
        if(t[w].fd(u)!=t[w].fd(v))pre[l]=l,puts("YES");
        else pre[l]=pre[pre[l]],puts("NO");
        if(pre[l])updata(1,1,q,l+1,nxt[l]-1,pre[l]);
    }
    else dfs(ls,l,mid),dfs(rs,mid+1,r);
    while(tp>lst)t[st[tp].fi].del(st[tp].se),tp--;
}
int u[maxn],v[maxn];
void work(){
    n=read();m=read();k=read();q=read();
    for(int i=1;i<=m;i++)u[i]=read(),v[i]=read();
    for(int i=1;i<=q;i++){
        int id=read(),c=read()-1;ask[i]={u[id],v[id],c};
        pre[i]=lst[id],lst[id]=i;
    }
    for(int i=1;i<=q;i++)nxt[pre[i]]=i;
    for(int i=1;i<=q;i++)if(!nxt[i])nxt[i]=q+1;
    for(int i=0;i<k;i++)t[i].init(i);
    dfs(1,1,q);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}