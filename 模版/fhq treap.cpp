struct fhq{
	int w[maxn],ls[maxn],rs[maxn],idx,rt;
	int siz[maxn],sz[maxn];
	void up(int u){
		siz[u]=siz[ls[u]]+siz[rs[u]]+sz[u];
	}
	int merge(int u,int v){
		if(!u||!v)return u|v;
		if(w[u]<w[v]){
			rs[u]=merge(rs[u],v);
			up(u);
			return u;
		}
		else{
			ls[v]=merge(u,ls[v]);
			up(v);
			return v;
		}
	}
	pii split(int u,int k){
		if(!u)return {0,0};
		if(siz[ls[u]]+sz[u]>k){
			pii t=split(ls[u],k);
			ls[u]=t.se;
			up(u);
			return {t.fi,u};
		}
		else{
			pii t=split(rs[u],k-siz[ls[u]]-sz[u]);
			rs[u]=t.fi;
			up(u);
			return {u,t.se};
		}
	}
	int newnode(int s,int v){
		w[++idx]=rnd();siz[idx]=sz[idx]=s,val[idx]=num[idx]=v;
		return idx;
	}
}t;