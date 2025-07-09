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
const int maxn=110;
const int inf=1e9;

int n,m,a,b,res=inf;
int head[maxn],tot=1;
struct nd{
    int nxt,to,w,c;
}e[maxn*maxn*2];
void add(int u,int v,int w,int c){
    e[++tot]={head[u],v,w,c};head[u]=tot;
    e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int s,t,flow,ans;
int dep[maxn],cur[maxn];
queue<int> q;
bool vis[maxn];
bool bfs(){
    for(int i=1;i<=t;i++)dep[i]=inf,cur[i]=head[i];
    vis[s]=1,q.push(s);dep[s]=0;
    while(!q.empty()){
        int u=q.front();q.pop();vis[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].w&&dep[v]>dep[u]+e[i].c){
                dep[v]=dep[u]+e[i].c;
                if(!vis[v])vis[v]=1,q.push(v);
            }
        }
    }
    return dep[t]!=inf;
}
int dfs(int u,int lim){
    if(u==t)return lim;
    int val=0;vis[u]=1;
    for(int i=cur[u];i;i=e[i].nxt){
        int v=e[i].to;cur[u]=i;
        if(e[i].w&&dep[v]==dep[u]+e[i].c&&!vis[v]){
            int out=dfs(v,min(e[i].w,lim));
            e[i].w-=out,e[i^1].w+=out;
            lim-=out,val+=out;
            ans+=out*e[i].c;
            if(!lim)break;
        }
    }
    vis[u]=0;
    return val;
}
bool c[maxn][maxn],d[maxn][maxn];
char S[maxn];
int id(pii p){return (p.fi-1)*m+p.se;}
void work(){
    n=read();m=read();a=read();b=read();
    for(int i=1;i<=n;i++){
        scanf("%s",S+1);
        for(int j=1;j<=m;j++)c[i][j]=S[j]=='M';
    }
    for(int i=1;i<=n;i++){
        scanf("%s",S+1);
        for(int j=1;j<=m;j++)d[i][j]=S[j]=='M';
    }
    vector<pii> p[2];
    int num=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(c[i][j]!=d[i][j])p[c[i][j]].pb({i,j}),++num;
    }
    s=n*m+1,t=n*m+2;
    for(int i=1;i<=t;i++)head[i]=0;tot=1;
    for(pii p1:p[0])add(s,id(p1),1,0);
    for(pii p2:p[1])add(id(p2),t,1,0);
    for(pii p1:p[0]){
        for(pii p2:p[1]){
            add(id(p1),id(p2),1,abs(p1.fi-p2.fi)+abs(p1.se-p2.se));
        }
    }
    flow=ans=0;res=num*a;
    while(bfs()&&num){
        num-=2;
        flow+=dfs(s,1);
        res=min(res,ans*b+num*a);
    }
    printf("%lld\n",res);
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