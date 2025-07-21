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
const int maxn=1010;
const int inf=1e9;

int n,m;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn*maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int d[maxn],dep[maxn],fa[maxn];
int dfn[maxn],idx;
void dfs(int u){
    dep[u]=dep[fa[u]]+1;dfn[u]=++idx;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(dfn[v])continue;
        d[u]++,d[v]++;fa[v]=u;dfs(v);
    }
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1);
    vector<int> id;
    for(int i=2;i<=n;i++)if(d[i]==1)id.pb(i);
    sort(id.begin(),id.end(),[&](int u,int v){return dfn[u]<dfn[v];});
    if(id.size()>=n/3){
        puts("2");
        for(int i=0;i<n/3;i++)printf("%d ",id[i]);
    }
    else{
        puts("1");
        id.pb(1);
        for(int i=0;i<(id.size()+1)/2;i++){
            int u=id[i],v=id[min(id.size()-1,i+id.size()/2)];
            vector<int> id1,id2;
            while(dep[u]>dep[v])id1.pb(u),u=fa[u];
            while(dep[v]>dep[u])id2.pb(v),v=fa[v];
            while(u!=v)id1.pb(u),u=fa[u],id2.pb(v),v=fa[v];
            id1.pb(u);
            reverse(id2.begin(),id2.end());
            for(int u:id2)id1.pb(u);
            printf("%d ",id1.size());for(int u:id1)printf("%d ",u);puts("");
        }
        int pos=0;
        for(int i=(id.size()+1)/2+1;i<=(n+5)/6;i++){
            ++pos;
            printf("1 %d\n",pos);
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}