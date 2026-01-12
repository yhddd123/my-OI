#include<bits/stdc++.h>
// #define int long long
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
const int maxn=80010;
const int inf=1e9;
const int B=300;
bool mbe;

int n,q;
bool z[maxn];
bitset<maxn> a[maxn],W;
vector<int> e[maxn];
int fa[maxn],dfn[maxn],rnk[maxn],st[17][maxn],idx;
bitset<maxn> vis;
void dfs(int u,int fa){
	::fa[u]=fa;
	st[0][dfn[u]=++idx]=fa;rnk[idx]=u;
	for(int v:e[u])if(v!=fa)dfs(v,u);
}
int mn[17][maxn],mx[17][maxn];
int quemn(int l,int r){
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
int quemx(int l,int r){
	int k=__lg(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int llca(int l,int r){
	int u=rnk[quemn(l,r)],v=rnk[quemx(l,r)];
	return lca(u,v);
}
vector<int> upd[maxn],mdf[maxn],que[maxn];
void dfs1(int u,int fa){
	vis.set(u);
	for(int id:upd[u])a[id]^=vis;
	for(int v:e[u])if(v!=fa)dfs1(v,u);
	vis.reset(u);
}
bool op[maxn];
pii ask[maxn];
int pre[maxn],cnt;
bool bk[maxn];
int gg[maxn];
void dfs2(int d,int x,int mul){
	// for(int j=1;j<=n;j++)cout<<vis[j];cout<<"\n";
	for(int id:que[x])a[id]&=vis;
	for(int i=d;i<=cnt&&1ll*pre[i]*x<=n;i++){
		int nw=(i==d?mul:1)*pre[i];
		for(int j=nw;j<=n;j+=nw)vis[j]=z[gg[j]*=pre[i]];
		dfs2(i,x*pre[i],nw);
		for(int j=nw;j<=n;j+=nw)vis[j]=z[gg[j]/=pre[i]];
	}
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)z[i]=read()&1;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)mn[0][i]=mx[0][i]=dfn[i];
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
			mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
			st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
		}
	}
	for(int i=1;i<=q;i++){
		int op=read();
		::op[i]=(op==2);
		if(op==1){
			int l=read(),r=read();ask[i]={l,r};
			int p=(l+B-1)/B*B;
			if(p<=r)upd[p].pb(i);
			else{
				vis.reset();
				for(int j=l;j<=r;j++){
					int p=j;
					while(p&&!vis[p])vis.set(p),p=fa[p];
				}
				swap(a[i],vis);
			}
		}
		else{
			int l=read(),r=read(),u=read();ask[i]={l,r};
			que[u].pb(i);
		}
	}
	for(int i=B;i<=n;i+=B){
		for(int id:upd[i]){
			auto[l,r]=ask[id];
			mdf[l].pb(id),mdf[r].pb(id);
		}
		vis.reset();
		for(int j=i;j<=n;j++){
			int p=j;
			while(p&&!vis[p])vis.set(p),p=fa[p];
			for(int id:mdf[j])a[id]|=vis;
			mdf[j].clear();
		}
		vis.reset();
		for(int j=i-1;j;j--){
			int p=j;
			while(p&&!vis[p])vis.set(p),p=fa[p];
			for(int id:mdf[j])a[id]|=vis;
			mdf[j].clear();
		}
		upd[i].clear();
	}
	for(int i=1;i<=q;i++)if(!op[i]){
		auto[l,r]=ask[i];
		upd[fa[llca(l,r)]].pb(i);
	}
	vis.reset();
	dfs1(1,0);
	for(int i=1;i<=q;i++){
		if(!op[i]){
			W^=a[i];
		}
		else{
			a[i]=W;
		}
	}
	for(int i=2;i<=n;i++){
		if(!bk[i])pre[++cnt]=i;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			bk[i*pre[j]]=1;
			if(i%pre[j]==0)break;
		}
	}
	for(int i=1;i<=n;i++)gg[i]=1;
	if(z[1])vis.set();
	else vis.reset();
	dfs2(1,1,1);
	for(int i=1;i<=q;i++)if(op[i]){
		auto[l,r]=ask[i];
		a[i]>>=l;a[i]<<=maxn-(r-l+1);
		int sz=a[i].count();
		printf("%lld\n",(1ll*sz*19901991+(r-l+1-sz))%20242024);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("1.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}