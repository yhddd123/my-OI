int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1;son[u]=0;dep[u]=dep[fa[u]]+1;
	for(int v:e[u])if(v!=fa[u]){
		fa[v]=u,dfs(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],idx,rnk[maxn],top[maxn],st[19][maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u,st[0][idx]=fa[u];top[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
int kth(int u,int k){
	while(dep[u]-dep[fa[top[u]]]<=k){
		k-=dep[u]-dep[fa[top[u]]];
		u=fa[top[u]];
	}
	return rnk[dfn[u]-k];
}
int go(int u,int v,int k){
	int tp=lca(u,v);
	if(dep[u]-dep[tp]>=k)return kth(u,k);
	return kth(v,dep[u]+dep[v]-2*dep[tp]-k);
}
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
int get(int u,int v,int p){//p->path(u,v)
	if(in(p,u)&&in(p,v))return lca(u,v);
	if((in(p,u)&&in(v,p))||(in(p,v)&&in(u,p)))return p;
	int p1=lca(u,p),p2=lca(v,p);
	if(dep[p1]>dep[p2])swap(p1,p2);
	p1=lca(u,v);
	if(dep[p1]>dep[p2])swap(p1,p2);
	return p2;
}