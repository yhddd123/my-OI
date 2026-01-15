// Problem: P12703 [KOI 2022 Round 2] 外环路
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12703
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2026-01-15 18:23:37
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int maxq=250010;
const int inf=1e18;
bool mbe;

int n,k,q;
int ans[maxq];
vector<pii> e[maxn],g[maxn];
int in[maxn],out[maxn],id[maxn];
void dfs(int u,int fa){
	if(e[u].size()==1)id[k]=u,in[u]=k++;
	for(auto[v,w]:e[u])if(v!=fa){
		dfs(v,u);
	}
	out[u]=k-1;
}
int siz[maxn],ww[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1;ww[u]=0;
	for(auto[v,w]:e[u]){
		if(v==fa||!vis[v])continue;
		getrt(v,u);
		siz[u]+=siz[v];ww[u]=max(ww[u],siz[v]);
	}
	ww[u]=max(ww[u],sum-siz[u]);
	if(ww[u]<=sum/2)rt=u;
}
bool bk[maxn];
void dij(int s,vector<int> &id,int *dis){
	for(int u:id)bk[u]=0;
	priority_queue<pii> q;
	dis[s]=0;q.push({-dis[s],s});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(bk[u])continue;bk[u]=1;
		for(auto[v,w]:e[u])if(vis[v]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({-dis[v],v});
			}
		}
		for(auto[v,w]:g[u])if(vis[v]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({-dis[v],v});
			}
		}
	}
}
int d1[maxn],d2[maxn],d3[maxn];
int dfn[maxn],rnk[maxn],idx;
void dfs1(int u,int fa){
	rnk[dfn[u]=++idx]=u;
	siz[u]=1;
	for(auto[v,w]:e[u])if(v!=fa&&vis[v]){
		dfs1(v,u);
		siz[u]+=siz[v];
	}
}
void sovle(int u,vector<int> &id,vector<tuple<int,int,int>> &ask){
	if(!ask.size()){
		for(int u:id)vis[u]=0;
		return ;
	}
	idx=0;dfs1(u,0);
	vector<int> son;
	for(auto[v,w]:e[u])if(vis[v])son.pb(v);
	vector<int> idl={u},idr={u};
	int s=0;
	int p1=u,p2=u;
	for(int i=0;i<son.size();i++){
		int v=son[i];
		if(s+siz[v]>sum/2){
			// cout<<i<<" "<<s<<" "<<siz[v]<<endl;
			if(s>=sum/4){
				for(int j=0;j<i;j++){
					int v=son[j];
					for(int k=dfn[v];k<dfn[v]+siz[v];k++){
						int u=rnk[k];
						idl.pb(u);
						for(auto[v,w]:g[u]){
							if(vis[v]&&dfn[v]>=dfn[son[i-1]]+siz[son[i-1]]){
								if(p1==rt)p1=v;
								else p2=v;
							}
						}
					}
				}
				for(int j=i;j<son.size();j++){
					int v=son[j];
					for(int k=dfn[v];k<dfn[v]+siz[v];k++)idr.pb(rnk[k]);
				}
			}
			else{
				s+=siz[v];
				for(int j=0;j<=i;j++){
					int v=son[j];
					for(int k=dfn[v];k<dfn[v]+siz[v];k++){
						int u=rnk[k];
						idl.pb(u);
						for(auto[v,w]:g[u]){
							if(vis[v]&&dfn[v]>=dfn[son[i]]+siz[son[i]]){
								if(p1==rt)p1=v;
								else p2=v;
							}
						}
					}
				}
				for(int j=i+1;j<son.size();j++){
					int v=son[j];
					for(int k=dfn[v];k<dfn[v]+siz[v];k++)idr.pb(rnk[k]);
				}
			}
			break;
		}
		s+=siz[v];
	}
	// cout<<u<<" "<<id.size()<<" "<<idl.size()<<" "<<idr.size()<<" "<<p1<<" "<<p2<<" s"<<endl;
	// for(int x:idl)cout<<x<<" ";cout<<endl;
	// for(int x:idr)cout<<x<<" ";cout<<endl;
	dij(u,id,d1);
	if(p1!=u)dij(p1,id,d2);
	if(p2!=u)dij(p2,id,d3);
	for(auto[u,v,id]:ask){
		ans[id]=min({ans[id],d1[u]+d1[v],d2[u]+d2[v],d3[u]+d3[v]});
	}
	for(int u:id)d1[u]=d2[u]=d3[u]=inf;
	for(int u:id)vis[u]=0;
	for(int u:idl)vis[u]=1;
	vector<tuple<int,int,int>> askl,askr;
	for(auto[u,v,id]:ask){
		if(u==rt||v==rt)continue;
		if(vis[u]==vis[v]){
			if(vis[u])askl.pb({u,v,id});
			else askr.pb({u,v,id});
		}
	}
	sum=idl.size();getrt(u,0);sovle(rt,idl,askl);
	for(int u:idr)vis[u]=1;
	sum=idr.size();getrt(u,0);sovle(rt,idr,askr);
}
void work(){
	n=read();
	for(int i=2;i<=n;i++){
		int u=read(),w=read();
		e[u].pb({i,w}),e[i].pb({u,w});
	}
	dfs(1,0);
	for(int i=0;i<k;i++){
		int w=read();
		g[id[i]].pb({id[(i+1)%k],w}),g[id[(i+1)%k]].pb({id[i],w});
	}
	q=read();
	vector<tuple<int,int,int>> ask;
	for(int i=1;i<=q;i++){
		int u=read(),v=read();
		ask.pb({u,v,i});ans[i]=inf;
	}
	vector<int> id(n);
	for(int i=1;i<=n;i++)vis[i]=1,id[i-1]=i;
	for(int i=1;i<=n;i++)d1[i]=d2[i]=d3[i]=inf;
	sum=n;getrt(1,0);sovle(rt,id,ask);
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}