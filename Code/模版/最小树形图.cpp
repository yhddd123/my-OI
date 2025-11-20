
int fa[maxn],val[maxn],rt,idx;
namespace dmst{
struct bcj{
	int f[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void merge(int u,int v){f[fd(u)]=fd(v);}
	void init(){
		for(int i=1;i<=n;i++)f[i]=i;
	}
}f1,f2;
priority_queue<pii,vector<pii>,greater<pii>> q[maxn];int tag[maxn];
void merge(int u,int v){
	if(q[u].size()<q[v].size())swap(q[u],q[v]),swap(tag[u],tag[v]);
	while(!q[v].empty()){
		pii p=q[v].top();q[v].pop();
		q[u].push({p.fi+tag[v]-tag[u],p.se});
	}
}
void sovle(){
	for(int i=1;i<=n;i++)q[i].push({inf,i%n+1});
	f1.init(),f2.init();
	queue<int> qq;
	for(int i=1;i<=n;i++)qq.push(i);
	while(!qq.empty()){
		int u=f1.fd(qq.front());qq.pop();
		while(q[u].size()&&u==f1.fd(q[u].top().se))q[u].pop();
		if(!q[u].size()){rt=u;break;}
		auto[w,v]=q[u].top();
		v=f1.fd(v),w+=tag[u];
		if(f2.fd(u)!=f2.fd(v)){
			f2.merge(u,v);
			fa[u]=v,val[u]=w;
		}
		else{
			++idx;qq.push(idx);f1.f[idx]=f2.f[idx]=idx;
			while(v!=u){
				tag[v]-=val[v];merge(idx,v);
				f1.merge(v,idx);
				int nw=f1.fd(fa[v]);
				fa[v]=idx;v=nw;
			}
			fa[u]=idx,val[u]=w;
			tag[u]-=val[u];merge(idx,u);
			f1.merge(u,idx);
			f2.merge(idx,u);
		}
	}
	// for(int i=1;i<=idx;i++)cout<<fa[i]<<" ";cout<<"\n";
	// for(int i=1;i<=idx;i++)cout<<f1.fd(i)<<" ";cout<<"\n";
	// for(int i=1;i<=idx;i++)cout<<f2.fd(i)<<" ";cout<<"\n";
	// cout<<rt<<"\n";
}
}