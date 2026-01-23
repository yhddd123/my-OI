// Problem: P12462 [Ynoi Easy Round 2018] 星野爱久爱海
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12462
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-23 19:17:12
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
const int maxn=300010;
const int maxm=3010;
const int k=100;
const int inf=1e9;
bool mbe;

int n,q;
vector<pii> e[maxn];
int dfn[maxn],idx,st[19][maxn],siz[maxn];
int dis[maxn];
void dfspre(int u,int fa){
	st[0][dfn[u]=++idx]=fa;siz[u]=1;
	for(auto[v,w]:e[u]){
		if(v==fa)continue;
		dis[v]=dis[u]+w;
		dfspre(v,u);siz[u]+=siz[v];
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int calc(int u,int v){return dis[u]+dis[v]-2*dis[lca(u,v)];}
int pl[maxm],pr[maxm],num,bel[maxn];
vector<int> idd[12][maxm];
vector<int> merge(vector<int> u,vector<int> v){
	vector<int> res(u.size()+v.size());
	for(int i=0;i<u.size();i++)res[i]=u[i];
	for(int i=0;i<v.size();i++)res[i+u.size()]=v[i];
	return res;
}
vector<pii> g[maxn];
int stk[maxn],tp;
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
int mxd[maxn],son[maxn],fa[maxn];
void dfs(int u,int fa){
	mxd[u]=0;son[u]=0;::fa[u]=fa;
	for(auto[v,w]:g[u]){
		if(v==fa)continue;
		dfs(v,u);
		if(mxd[v]+w>mxd[u])mxd[u]=mxd[v]+w,son[u]=v;
	}
}
int dd[maxn];
void dfs1(int u,int fa){
	for(auto[v,w]:g[u]){
		if(v==fa)continue;
		if(v==son[u])dd[v]=dd[u]+w;
		else dd[v]=w;
		dfs1(v,u);
	}
}
pair<vector<int>,int> redo(vector<int> id,int kk=k){
	sort(id.begin(),id.end(),[&](int u,int v){return dfn[u]<dfn[v];});id.erase(unique(id.begin(),id.end()),id.end());
	vector<int> pos;
	for(int i=0;i<id.size();i++)pos.pb(lca(id[i],id[(i+1)%id.size()]));
	for(int u:id)pos.pb(u);
	sort(pos.begin(),pos.end(),[&](int u,int v){return dfn[u]<dfn[v];}),pos.erase(unique(pos.begin(),pos.end()),pos.end());
	for(int u:pos)g[u].clear();
	tp=0;for(int u:pos){
		while(tp&&!in(stk[tp],u))tp--;
		if(tp){
			int dd=calc(stk[tp],u);
			g[stk[tp]].pb({u,dd}),g[u].pb({stk[tp],dd});fa[u]=stk[tp];
		}
		stk[++tp]=u;
	}
	fa[pos[0]]=0;
	dd[pos[0]]=0;
	pii mx={0,0};
	for(int u:pos){
		for(auto[v,w]:g[u])if(v!=fa[u])dd[v]=dd[u]+w;
		mx=max(mx,{dd[u],u});
	}
	int rt=mx.se;
	dfs(rt,0);
	dd[rt]=0;dfs1(rt,0);
	vector<int> res;
	for(int u:id)if(!son[u])res.pb(u);
	sort(res.begin(),res.end(),[&](int u,int v){return dd[u]>dd[v];});
	res.resize(min(kk-1,(int)res.size()));
	res.pb(rt);
	int sum=0;for(int i=0;i<min((int)res.size()-1,kk-1);i++)sum+=dd[res[i]];
	return {res,sum};
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		e[u].pb({v,w}),e[v].pb({u,w});
	}
	dfspre(1,0);
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+k-1,n);pl[++num]=l,pr[num]=r;
		for(int i=l;i<=r;i++)bel[i]=num;
		idd[0][num].resize(r-l+1);
		for(int i=l;i<=r;i++)idd[0][num][i-l]=i;
	}
	for(int j=1;j<12;j++){
		for(int i=1;i+(1<<j)-1<=num;i++)idd[j][i]=redo(merge(idd[j-1][i],idd[j-1][i+(1<<j-1)])).fi;
	}
	q=read();
	while(q--){
		int l=read(),r=read(),kk=read();
		vector<int> id;
		if(bel[l]==bel[r]){
			for(int i=l;i<=r;i++)id.pb(i);
		}
		else{
			for(int i=l;i<=pr[bel[l]];i++)id.pb(i);
			for(int i=pl[bel[r]];i<=r;i++)id.pb(i);
			int ll=bel[l]+1,rr=bel[r]-1;
			if(ll<=rr){
				int k=__lg(rr-ll+1);
				id=merge(id,idd[k][ll]);
				id=merge(id,idd[k][rr-(1<<k)+1]);
			}
		}
		auto[nw,res]=redo(id,kk);
		printf("%lld\n",res);
		// for(int u:nw)cout<<u<<" ";cout<<"\n";
	}
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