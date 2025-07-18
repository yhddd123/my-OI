#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=100010;
const int inf=2e9;
bool mbe;

int n,m;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
struct bcj{
    int f[maxn];
    int fd(int x){
        if(f[x]==x)return x;
        return f[x]=fd(f[x]);
    }
    bool merge(int u,int v){
        u=fd(u),v=fd(v);
        if(u==v)return 0;
        f[u]=v;
        return 1;
    }
    void init(){
        for(int i=1;i<=n;i++)f[i]=i;
    }
}t1,t2;
int f[maxn];
pii st[maxn];int tp;
mt19937 rnd(time(0));
void dfs(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);f[u]^=f[v];
    }
    if(fa&&!f[u])st[++tp]={u,fa};
}
void work(){
    n=read();m=read();
    t1.init(),t2.init();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        if(t1.merge(u,v))add(u,v),add(v,u);
        else if(t2.merge(u,v)){
            int w=rnd()%inf;
            f[u]^=w,f[v]^=w;
        }
    }
    for(int i=1;i<=n;i++)if(t1.fd(i)==i)dfs(i,0);
    for(int i=1;i<=tp;i++)printf("%d %d\n",st[i].fi,st[i].se);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);

    // cerr<<(&mbe-&med)/1024.0/1024.0<<" MB\n";
    
    T=1;
    while(T--)work();
}