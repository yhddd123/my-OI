#include<bits/stdc++.h>
// #define int long long
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
const int maxn=210;
const int maxm=5010;

int n,m;
pii a[maxm];
int head[maxn*2],tot=1;
struct node{
    int nxt,to,w;
}e[maxn*4+maxm*2];
void add(int u,int v,int w){
    e[++tot]={head[u],v,w};head[u]=tot;
    e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int dep[maxn*2],cur[maxn*2];
bool bfs(){
    queue<int> q;
    for(int i=1;i<=t;i++)dep[i]=0,cur[i]=head[i];
    q.push(s);dep[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(!dep[v]&&e[i].w)dep[v]=dep[u]+1,q.push(v);
        }
    }
    return dep[t];
}
int to[maxn],fr[maxn];
void upd(int id,int w){e[id].w+=w,e[id^1].w-=w;}
int dfs(int u,int lim){
    if(u==t)return lim;
    int res=0;
    for(int i=cur[u];i;i=e[i].nxt){
        int v=e[i].to;cur[u]=i;
        if(dep[v]==dep[u]+1&&e[i].w){
            int out=dfs(v,min(lim,e[i].w));
            upd(i,-out);
            if(u<=n&&v-n<=n&&!e[i].w)to[u]=v-n,fr[v-n]=u;
            res+=out;lim-=out;
            if(!lim)break;
        }
    }
    return res;
}
vector<int> g[maxn];
int st[maxn*maxm],tp;
void dfs(int u){
    while(g[u].size()){
        int v=g[u].back();g[u].pop_back();
        dfs(v);
    }
    st[++tp]=u;
}
bool vis[maxm];
void work(){
    n=read();m=read();s=2*n+1,t=2*n+2;
    for(int i=1;i<=t;i++)head[i]=0;tot=1;
    for(int i=1;i<=n;i++)add(s,i,1);
    for(int i=1;i<=n;i++)add(i+n,t,1);
    map<pii,int> mp;
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        add(x,y+n,1);
        a[i]={x,y};
        mp[{x,y}]=i;
    }
    for(int i=1;i<=n;i++)vis[i]=0;
    queue<int> q;vis[1]=1,q.push(1);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to-n;
            if(!vis[v]&&v<=n)vis[v]=1,q.push(v);
        }
    }
    for(int i=1;i<=n;i++)if(!vis[i]){cout<<"IMPOSSIBLE\n";return ;}
    flow=0;while(bfs())flow+=dfs(s,n);
    if(flow!=n){cout<<"IMPOSSIBLE\n";return ;}
    for(int i=1;i<=n;i++)g[i].clear();
    for(int i=1;i<=m;i++)vis[i]=0;
    // for(int i=1;i<=n;i++)cout<<to[i]<<" ";cout<<"\n";
    for(int j=1;j<=n;j++)vis[mp[{j,to[j]}]]=1,g[j].pb(to[j]);
    for(int i=1;i<=m;i++)if(!vis[i]){
        auto [u,v]=a[i];
        if(to[u]==v)continue;
        int uu=fr[v],vv=to[u];
        upd(4*n+2*mp[{u,vv}],1),upd(4*n+2*mp[{uu,v}],1);
        upd(2*uu,1),upd(2*n+2*vv,1);
        upd(4*n+2*i,-1);flow--;
        to[u]=v,fr[v]=u,to[uu]=fr[vv]=0;
        e[2*u+1].w=e[2*n+2*v+1].w=e[4*n+2*i+1].w=0;
        while(bfs())flow+=dfs(s,n);
        e[2*u+1].w=e[2*n+2*v+1].w=e[4*n+2*i+1].w=1;
        // for(int j=1;j<=n;j++)cout<<to[j]<<" ";cout<<"\n";
        // assert(to[u]==v);
        if(flow!=n){cout<<"IMPOSSIBLE\n";return ;}
        for(int j=1;j<=n;j++)vis[mp[{j,to[j]}]]=1,g[j].pb(to[j]);
    }
    tp=0;dfs(1);
    printf("%d\n",tp);
    reverse(st+1,st+tp+1);
    for(int i=1;i<tp;i++)printf("%d ",st[i]);printf("%d\n",st[tp]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    for(int t=1;t<=T;t++){
        cout<<"Case #"<<t<<": ";
        work();
    }
}