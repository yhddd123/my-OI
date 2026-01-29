vector<int> e[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    for(int v:e[u])if(v!=fa[u]){
        fa[v]=u;dfs(v),siz[u]+=siz[v];
        if(siz[v]>=siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;
    if(!son[u])return ;dfs(son[u],lst);
    for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int lca(int u,int v){
    while(tp[u]!=tp[v]){
        if(dep[tp[u]]<dep[tp[v]])swap(u,v);
        u=fa[tp[u]];
    }
    if(dep[u]<dep[v])swap(u,v);
    return v;
}
