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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
vector<int> e[maxn],g[maxn];
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
void tar(int u){
    dfn[u]=lw[u]=++idx;st[++tp]=u;
    for(int v:e[u]){
        if(!dfn[v])tar(v),lw[u]=min(lw[u],lw[v]);
        else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
    }
    if(dfn[u]==lw[u]){
        scc[st[tp]]=++scct;
        while(st[tp--]!=u)scc[st[tp]]=scct;
    }
}
bool vis[maxn],ins[maxn];
bool chk(int u){
    vis[u]=ins[u]=1;
    for(int v:e[u]){
        if(vis[v]){
            if(!ins[v])return 1;
        }
        else if(chk(v))return 1;
    }
    ins[u]=0;
    return 0;
}
unordered_map<int,int> s[maxn];
int d[maxn];
int f[maxn];
int fd(int x){
    if(f[x]==x)return x;
    return f[x]=fd(f[x]);
}
int fa[maxn],dep[maxn],num[maxn],val1[maxn],val2[maxn],val3[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1;vis[u]=1;st[++tp]=u;
    for(int v:e[u])if(scc[u]==scc[v]){
        if(vis[v])continue;
        fa[v]=u;dfs(v);
    }
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)e[i].clear(),g[i].clear(),a[i]=0;
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        e[u].pb(v);
    }
    for(int i=1;i<=n;i++)dfn[i]=scc[i]=0;idx=tp=scct=0;
    for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
    for(int i=1;i<=scct;i++)d[i]=0;
    for(int u=1;u<=n;u++){
        for(int v:e[u])if(scc[u]!=scc[v])d[scc[v]]++;
    }
    int cnt=0;for(int i=1;i<=scct;i++)cnt+=!d[i];
    // cout<<scct<<" "<<cnt<<"\n";
    if(cnt>=2){
        for(int i=1;i<=n;i++)putchar('3');puts("");
        return ;
    }
    int id=0;for(int i=1;i<=scct;i++)if(!d[i])id=i;
    // cout<<id<<"\n";
    for(int i=1;i<=n;i++)d[i]=0,f[i]=i;
    queue<int> q;
    for(int u=1;u<=n;u++)s[u].clear();
    for(int u=1;u<=n;u++)if(scc[u]==id){
        for(int v:e[u])if(scc[v]==id)s[u][v]++,d[v]++,g[v].pb(u);
    }
    int rt=0;
    for(int u=1;u<=n;u++)if(scc[u]==id&&!d[u])rt=u;
    if(!rt){
        for(int u=1;u<=n;u++)if(d[u]==1)q.push(u);
        while(!q.empty()){
            int u=q.front();q.pop();
            if(d[u]!=1||f[u]!=u)continue;
            assert(g[u].size());
            while(g[u].size()&&fd(g[u].back())==u)g[u].pop_back();
            int v=fd(g[u].back());
            g[u].pop_back();
            while(g[u].size()&&fd(g[u].back())==u)g[u].pop_back();
            assert(!g[u].size());
            // cout<<u<<" "<<v<<"\n";
            s[v].erase(u);
            d[v]-=s[u][v],s[u].erase(v);
            if(d[v]==1)q.push(v);
            if(s[u].size()>s[v].size())swap(s[u],s[v]);
            for(auto[x,val]:s[u])s[v][x]+=val;
            f[u]=v;
        }
        for(int i=1;i<=n;i++)if(scc[i]==id&&f[i]==i){rt=i;break;}
    }
    // cout<<rt<<"\n";
    // for(int u=1;u<=n;u++)if(scc[u]==id){
	    // for(int i=1;i<=n;i++)vis[i]=ins[i]=0;
	    // if(!chk(u)){rt=u;break;}
    // }
    for(int i=1;i<=n;i++)vis[i]=ins[i]=0;
    if(chk(rt)){
    	// cout<<"run\n";
        for(int i=1;i<=n;i++)putchar(scc[i]==id?'2':'3');puts("");
        return ;
    }
    for(int u=1;u<=n;u++)g[u].clear();
    for(int u=1;u<=n;u++){
    	for(int v:e[u])g[v].pb(u);
    }
    a[rt]=1;
    for(int i=1;i<=n;i++)vis[i]=0;tp=0;
    fa[rt]=0;dfs(rt);
    // cout<<rt<<"\n";
    // for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
    for(int i=1;i<=tp;i++)num[st[i]]=val1[st[i]]=val2[st[i]]=val3[st[i]]=0;
    for(int u=1;u<=n;u++)if(scc[u]==id){
        for(int v:e[u])if(scc[v]==id&&dep[v]<dep[u]){
            num[u]++,num[v]--;
            val1[u]^=v,val1[v]^=v;
            val2[u]^=u,val2[v]^=u;
        }
    }
    for(int i=tp;i;i--){
        int u=st[i];
        num[fa[u]]+=num[u],val1[fa[u]]^=val1[u],val2[fa[u]]^=val2[u];
    }
    for(int i=2;i<=tp;i++){
        int u=st[i];
        if(num[u]==1){
            if(a[val1[u]]==1)a[u]=1;
        }
    }
    // for(int i=1;i<=n;i++)cout<<(a[i]?"1":"3");cout<<"\n";
    for(int i=1;i<=tp;i++)num[st[i]]=0;
	map<pii,bool> mp;
    for(int i=2;i<=tp;i++){
        int u=st[i];
        if(a[u]==1){
        	if(mp[{val2[u],val1[u]}])continue;
        	mp[{val2[u],val1[u]}]=1;
            num[val2[u]]++,num[val1[u]]--;
            val3[val1[u]]^=val1[u],val3[val2[u]]^=val1[u];
        }
    }
    for(int i=tp;i;i--){
        int u=st[i];
        num[fa[u]]+=num[u],val3[fa[u]]^=val3[u];
    }
    for(int i=1;i<=tp;i++){
        int u=st[i];
        f[u]=u;
        if(fa[u]&&(a[u]||num[u]))f[u]=fd(fa[u]);
    }
    for(int i=1;i<=tp;i++){
        int u=st[i];
        if(!a[u]&&num[u]==1){
        	if(a[val3[u]])a[u]=2;
        }
        // else if(!a[u]){
	        // if(!num[u]){
	        	// cout<<u<<" "<<dep[u]<<"\n";
	        // }
        // }
        if(a[u]){
	        for(int v:g[u])if(scc[v]==id&&dep[v]>dep[u]){
	            for(int p=fd(v);dep[p]>dep[u];p=fd(p)){
	                a[p]=2;
	                f[p]=fd(fa[p]);
	                // cout<<u<<" "<<p<<" "<<num[p]<<" "<<val3[p]<<"\n";
	            }
	        }
        }
    }
    for(int i=1;i<=n;i++)if(!a[i])a[i]=3;
    for(int i=1;i<=n;i++)printf("%d",a[i]);puts("");
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    read();T=read();
    while(T--)work();
}