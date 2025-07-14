// Problem: 树上的 mex
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/showproblem.php?pid=7443
// Memory Limit: 524 MB
// Time Limit: 15000 ms
// Written by yhm.
// Start codeing:2024-07-24 16:55:46
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=70010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
vector<int> e[maxn];
vector<int> id[maxn];
struct sqr{
	int x,xx,y,yy;
};
vector<sqr> ask[maxn];
int dfn[maxn],siz[maxn],idx;
void dfs(int u,int fa){
	dfn[u]=++idx;siz[u]=1;
	id[a[u]].push_back(u);
	for(int v:e[u]){
		if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
	}
}
bool in(int u,int v){
	return dfn[u]<=dfn[v]&&dfn[v]<=dfn[u]+siz[u]-1;
}
bool vis[maxn];
namespace sgt{
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	int cnt[maxn<<2],tag[maxn<<2];
	void build(int nd,int l,int r){
		tag[nd]=0;cnt[nd]=r-l+1;
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			tag[nd]+=w;
			return ;
		}
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		cnt[nd]=(!tag[ls])*cnt[ls]+(!tag[rs])*cnt[rs];
	}
}
vector<pii> add[maxn],del[maxn];
int check(int val){
	int ans=0;
	sgt::build(1,1,n);
	for(int i=1;i<=n+1;i++)add[i].clear(),del[i].clear();
	for(int i=0;i<val;i++){
		for(auto [x,xx,y,yy]:ask[i]){
			if(x>xx||y>yy||min(x,y)<=0||max(xx,yy)>n)continue;
			add[x].push_back({y,yy});
			del[xx+1].push_back({y,yy});
		}
	}
	for(int i=1;i<=n;i++){
		for(auto [l,r]:add[i])sgt::updata(1,1,n,l,r,1);
		for(auto [l,r]:del[i])sgt::updata(1,1,n,l,r,-1);
		ans+=sgt::tag[1]?0:sgt::cnt[1];
	}
	return ans;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)e[i].clear(),vis[i]=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=0;i<=n;i++)id[i].clear(),ask[i].clear();
	idx=0;dfs(1,0);
	// for(int i=1;i<=n;i++)cout<<i<<" "<<dfn[i]<<"\n";
	for(int i=0;i<=n;i++){
		if(!id[i].size()){
			ask[i].push_back({1,n,1,n});
			continue;
		}
		int pos=0;
		for(int j=1;j<id[i].size();j++){
			int u=id[i][j];
			if(!in(id[i][j-1],u))pos=u;
			for(int v:e[u]){
				if(vis[v]||dfn[v]<dfn[u])continue;
				if(j!=id[i].size()-1&&in(v,id[i][j+1])){
					int p=id[i][j+1];
					ask[i].push_back({dfn[v],dfn[p]-1,dfn[v],dfn[p]-1});
					ask[i].push_back({dfn[v],dfn[p]-1,dfn[p]+siz[p],dfn[v]+siz[v]-1});
					ask[i].push_back({dfn[p]+siz[p],dfn[v]+siz[v]-1,dfn[v],dfn[p]-1});
					ask[i].push_back({dfn[p]+siz[p],dfn[v]+siz[v]-1,dfn[p]+siz[p],dfn[v]+siz[v]-1});
				}
				else{
					ask[i].push_back({dfn[v],dfn[v]+siz[v]-1,dfn[v],dfn[v]+siz[v]-1});
					vis[v]=1;
				}
			}
		}
		int u=id[i][0];
		if(!pos||in(u,pos)){
			ask[i].push_back({1,dfn[u]-1,1,dfn[u]-1});
			ask[i].push_back({1,dfn[u]-1,dfn[u]+siz[u],n});
			ask[i].push_back({dfn[u]+siz[u],n,1,dfn[u]-1});
			ask[i].push_back({dfn[u]+siz[u],n,dfn[u]+siz[u],n});
			// cout<<i<<" "<<u<<" "<<dfn[u]<<" "<<siz[u]<<"\n";
		}
		else{
			ask[i].push_back({1,dfn[u]-1,1,dfn[u]-1});
			ask[i].push_back({1,dfn[u]-1,dfn[u]+siz[u],dfn[pos]-1});
			ask[i].push_back({1,dfn[u]-1,dfn[pos]+siz[pos],n});
			ask[i].push_back({dfn[u]+siz[u],dfn[pos]-1,1,dfn[u]-1});
			ask[i].push_back({dfn[u]+siz[u],dfn[pos]-1,dfn[u]+siz[u],dfn[pos]-1});
			ask[i].push_back({dfn[u]+siz[u],dfn[pos]-1,dfn[pos]+siz[pos],n});
			ask[i].push_back({dfn[pos]+siz[pos],n,1,dfn[u]-1});
			ask[i].push_back({dfn[pos]+siz[pos],n,dfn[u]+siz[u],dfn[pos]-1});
			ask[i].push_back({dfn[pos]+siz[pos],n,dfn[pos]+siz[pos],n});
		}
		for(int v:e[u]){
			if(vis[v]||dfn[v]<dfn[u])continue;
			if(id[i].size()!=1&&in(v,id[i][1])){
				int p=id[i][1];
				ask[i].push_back({dfn[v],dfn[p]-1,dfn[v],dfn[p]-1});
				ask[i].push_back({dfn[v],dfn[p]-1,dfn[p]+siz[p],dfn[v]+siz[v]-1});
				ask[i].push_back({dfn[p]+siz[p],dfn[v]+siz[v]-1,dfn[v],dfn[p]-1});
				ask[i].push_back({dfn[p]+siz[p],dfn[v]+siz[v]-1,dfn[p]+siz[p],dfn[v]+siz[v]-1});
			}
			else if(pos&&in(v,pos)){
				int p=pos;
				ask[i].push_back({dfn[v],dfn[p]-1,dfn[v],dfn[p]-1});
				ask[i].push_back({dfn[v],dfn[p]-1,dfn[p]+siz[p],dfn[v]+siz[v]-1});
				ask[i].push_back({dfn[p]+siz[p],dfn[v]+siz[v]-1,dfn[v],dfn[p]-1});
				ask[i].push_back({dfn[p]+siz[p],dfn[v]+siz[v]-1,dfn[p]+siz[p],dfn[v]+siz[v]-1});
			}
			else{
				ask[i].push_back({dfn[v],dfn[v]+siz[v]-1,dfn[v],dfn[v]+siz[v]-1});
				vis[v]=1;
			}
		}
	}
	// for(int i=0;i<=n;i++){
		// cout<<i<<"\n";
		// for(auto [x,xx,y,yy]:ask[i])if(x<=xx&&y<=yy&&min(x,y)>=1&&max(xx,yy)<=n)cout<<x<<" "<<y<<" "<<xx<<" "<<yy<<"\n";
	// }
	int l=1,r=n,res=0;
	while(l<=r){
		if(check(mid))res=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld %lld\n",res,check(res));
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
