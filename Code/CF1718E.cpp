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
const int maxn=200010;
const int inf=1e9;

int n,m;
vector<pii> e[maxn],g[maxn];
int id1[maxn],num1[maxn],idx1;
void dfs1(int u){
    num1[id1[u]=idx1]+=(u<=n);
    for(auto[w,v]:e[u])if(!id1[v])dfs1(v);
}
int id2[maxn],num2[maxn],idx2;
void dfs2(int u){
    num2[id2[u]=idx2]+=(u<=n);
    for(auto[w,v]:g[u])if(!id2[v])dfs2(v);
}
int p[maxn];
bool vis[maxn];
int st[maxn],tp;
bool dfs(int u){
    st[++tp]=u;vis[p[u]]=1;
    if(e[u].size()!=g[p[u]].size())return 0;
    for(int i=0;i<e[u].size();i++){
        auto [w1,v1]=e[u][i];
        auto [w2,v2]=g[p[u]][i];
        // cout<<u<<" "<<w1<<" "<<v1<<" "<<w2<<" "<<v2<<"\n";
        if(w1!=w2)return 0;
        if(p[v1]||vis[v2]){
            if(p[v1]!=v2)return 0;
            continue;
        }
        p[v1]=v2;
        if(!dfs(v1))return 0;
    }
    return 1;
}
void work(){
    n=read();m=read();
    bool fl=n>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int v=read();
            if(!v)continue;
            if(fl)e[j].pb({v,i+m}),e[i+m].pb({v,j});
            else e[i].pb({v,j+n}),e[j+n].pb({v,i});
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int v=read();
            if(!v)continue;
            if(fl)g[j].pb({v,i+m}),g[i+m].pb({v,j});
            else g[i].pb({v,j+n}),g[j+n].pb({v,i});
        }
    }
    if(fl)swap(n,m);
    for(int i=1;i<=n+m;i++)sort(e[i].begin(),e[i].end()),sort(g[i].begin(),g[i].end());
    for(int i=1;i<=n;i++)if(!id1[i])++idx1,dfs1(i);
    for(int i=1;i<=n;i++)if(!id2[i])++idx2,dfs2(i);
    for(int i=1;i<=n;i++)if(!p[i]){
        for(int j=1;j<=n;j++)if(!vis[j]&&num1[id1[i]]==num2[id2[j]]){
            p[i]=j;tp=0;
            // cout<<i<<" "<<j<<"\n";
            if(dfs(i))break;
            while(tp)vis[p[st[tp]]]=0,p[st[tp]]=0,tp--;
        }
        if(!p[i]){puts("-1");return ;}
    }
    vector<tuple<int,int,int>> ans;
    for(int i=n+1;i<=n+m;i++)if(!vis[i])st[++tp]=i;
    for(int i=n+1;i<=n+m;i++)if(!p[i])p[i]=st[tp--];
    // for(int i=1;i<=n;i++)cout<<p[i]<<" ";cout<<"\n";
    // for(int i=n+1;i<=n+m;i++)cout<<p[i]<<" ";cout<<"\n";
    for(int i=1;i<=n;i++)if(p[i]!=i){
        ans.pb({fl,i,p[i]});
        swap(p[i],p[p[i]]);
        i--;
    }
    for(int i=n+1;i<=n+m;i++)if(p[i]!=i){
        ans.pb({fl^1,i-n,p[i]-n});
        swap(p[i],p[p[i]]);
        i--;
    }
    printf("%d\n",ans.size());
    for(auto[op,u,v]:ans)printf("%d %d %d\n",op+1,u,v);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}