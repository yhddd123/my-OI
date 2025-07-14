// Problem: P4069 [SDOI2016] 游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4069
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-10-18 11:03:39
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=123456789123456789ll;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dep[maxn],fa[maxn],siz[maxn],son[maxn],dis[maxn];
void dfs(int u){
	siz[u]=1,dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u,dis[v]=dis[u]+e[i].w;dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],tim,tp[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++tim]=u,tp[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs(v,v);
	}
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int k,b;
}line[maxn];int idx;
int calc(int id,int x){return line[id].k*x+line[id].b;}
int tree[maxn<<2],p[maxn<<2],L[maxn<<2],R[maxn<<2];
void build(int nd,int l,int r){
	tree[nd]=inf;p[nd]=0,L[nd]=dis[rnk[l]],R[nd]=dis[rnk[r]];
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int id){
	if(l==r){
		if(calc(id,L[nd])<calc(p[nd],L[nd])){
			p[nd]=id;
			tree[nd]=calc(p[nd],L[nd]);
		}
		return ;
	}
	int mm=(L[nd]+R[nd]>>1);
	if(calc(id,mm)<calc(p[nd],mm))swap(p[nd],id);
	if(calc(id,L[nd])<calc(p[nd],L[nd]))modif(ls,l,mid,id);
	else modif(rs,mid+1,r,id);
	tree[nd]=min({tree[ls],tree[rs],calc(p[nd],L[nd]),calc(p[nd],R[nd])});
}
void updata(int nd,int l,int r,int ql,int qr,int id){
	if(l>=ql&&r<=qr)return modif(nd,l,r,id);
	if(ql<=mid)updata(ls,l,mid,ql,qr,id);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,id);
	tree[nd]=min({tree[ls],tree[rs],calc(p[nd],L[nd]),calc(p[nd],R[nd])});
	// cout<<l<<" "<<r<<" "<<tree[nd]<<" "<<p[nd]<<" u\n";
}
int query(int nd,int l,int r,int ql,int qr){
	int val=min(calc(p[nd],dis[rnk[max(l,ql)]]),calc(p[nd],dis[rnk[min(r,qr)]]));
	// cout<<l<<" "<<r<<" "<<val<<" "<<p[nd]<<" "<<tree[nd]<<" q\n";
	if(l>=ql&&r<=qr)return min(val,tree[nd]);
	if(ql<=mid)val=min(val,query(ls,l,mid,ql,qr));
	if(qr>mid)val=min(val,query(rs,mid+1,r,ql,qr));
	return val;
}
int lca(int u,int v){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	return v;
}
void upd(int u,int v,int id){
	while(tp[u]!=tp[v]){
		updata(1,1,n,dfn[tp[u]],dfn[u],id);
		u=fa[tp[u]];
	}
	if(u!=v)updata(1,1,n,dfn[v]+1,dfn[u],id);
}
int que(int u,int v){
	int ans=inf;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		ans=min(ans,query(1,1,n,dfn[tp[u]],dfn[u]));
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	ans=min(ans,query(1,1,n,dfn[v],dfn[u]));
	return ans;
}
void work(){
	n=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs(1),dfs(1,1);line[0]={0,inf};build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),v=read(),a=read(),b=read(),tp=lca(u,v);
			line[++idx]={-a,dis[u]*a+b};
			upd(u,tp,idx);updata(1,1,n,dfn[tp],dfn[tp],idx);
			line[++idx]={a,(dis[u]-2*dis[tp])*a+b};
			// cout<<line[idx].k<<" "<<line[idx].b<<" "<<dis[3]<<"\n";
			upd(v,tp,idx);
		}
		else{
			int u=read(),v=read();
			printf("%lld\n",que(u,v));
		}
		// cout<<query(1,1,n,2,2)<<" "<<query(1,1,n,3,3)<<"\n";
	}
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
	
	T=1;
	while(T--)work();
}
