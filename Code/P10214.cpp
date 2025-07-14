// Problem: P10214 [CTS2024] 投票游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10214
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-09-18 15:06:39
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
int fa[maxn],a[maxn],b[maxn];
int sum[maxn],dp[maxn];
vector<int> e[maxn];
mt19937 rnd(1);
int w[maxn],lc[maxn],rc[maxn];
int val[maxn],mn[maxn];
void up(int x){//mn[i] 为 dp[i]+sum[i-1] 的前缀 min
	val[x]=val[lc[x]]+val[rc[x]]+b[x];
	mn[x]=min({mn[lc[x]],val[lc[x]]+dp[x],val[lc[x]]+b[x]+mn[rc[x]]});
}
pii split(int x,pii p){//按 {dp[i],i} 排序 
	if(!x)return {0,0};
	if(mkp(dp[x],x)>p){
		pii t=split(rc[x],p);
		rc[x]=t.fi;up(x);
		return {x,t.se};
	}
	else{
		pii t=split(lc[x],p);
		lc[x]=t.se;up(x);
		return {t.fi,x};
	}
}
int merge(int x,int y){
	if(!x||!y)return x|y;
	if(w[x]<w[y]){
		rc[x]=merge(rc[x],y),up(x);
		return x;
	}
	else{
		lc[y]=merge(x,lc[y]),up(y);
		return y;
	}
}
int query(int x,int k){//二分 mn[i]<k 的 k-s[i-1]
	if(!x)return k;
	if(mn[lc[x]]<k)return query(lc[x],k);
	else if(val[lc[x]]+dp[x]<k)return k-val[lc[x]];
	else return query(rc[x],k-val[lc[x]]-b[x]);
}
int rt[maxn];
void ins(int u,int v){//插入 u 的轻儿子 v
	pii t=split(rt[u],{dp[v],v});
	w[v]=rnd(),mn[v]=dp[v],val[v]=b[v],lc[v]=rc[v]=0;
	rt[u]=merge(t.fi,merge(v,t.se));
}
void del(int u,int v){//删除 u 的轻儿子 v
	// cout<<u<<" "<<v<<" "<<dp[v]<<endl;
	pii t=split(rt[u],{dp[v],v});
	pii tt=split(t.se,{dp[v],v-1});
	lc[tt.fi]=rc[tt.fi]=0;
	rt[u]=merge(t.fi,tt.se);
}
struct node{//分段常函数 <k?x:y
	int k,x,y;
	int calc(int w){return w<k?x:y;}
}c[maxn],tree[maxn<<2];
node merge(node u,node v){return {v.k,u.calc(v.x),u.calc(v.y)};}
int siz[maxn],son[maxn];
node que(int u){
	if(!son[u])return {0,0,a[u]};
	int v=query(rt[u],a[u]+sum[u]);
	return {v,v,query(rt[u],a[u]+sum[u]-b[son[u]])};
}
void dfs(int u){
	siz[u]=1;
	for(int v:e[u])if(fa[v]==u){
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	for(int v:e[u])if(v!=son[u])ins(u,v);
	c[u]=que(u),dp[u]=c[u].calc(dp[son[u]]);
}
int dfn[maxn],rnk[maxn],idx,tp[maxn],dwn[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;
	if(!son[u]){dwn[u]=u;return ;}
	dfs(son[u],lst),dwn[u]=dwn[son[u]];
	for(int v:e[u])if(fa[v]==u&&v!=son[u])dfs(v,v);
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
void build(int nd,int l,int r){
	if(l==r){tree[nd]=c[rnk[l]];return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	tree[nd]=merge(tree[ls],tree[rs]);
	// cout<<l<<" "<<r<<" "<<tree[nd].k<<" "<<tree[nd].x<<" "<<tree[nd].y<<"\n";
}
void updata(int nd,int l,int r,int p){
	if(l==r){tree[nd]=c[rnk[l]];return ;}
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
	tree[nd]=merge(tree[ls],tree[rs]);
}
node query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int get(int u){
	return query(1,1,n,dfn[u],dfn[dwn[u]]).calc(0);
}
void upd(int x){
	while(x){
		// cout<<x<<" "<<tp[x]<<" "<<dp[x]<<endl;
		c[x]=que(x),updata(1,1,n,dfn[x]);
		// cout<<c[x].k<<" "<<c[x].x<<" "<<c[x].y<<endl;
		x=tp[x];if(x==1)return ;
		// cout<<x<<" "<<fa[x]<<" "<<dp[x]<<" "<<endl;
		del(fa[x],x),dp[x]=get(x),ins(fa[x],x);
		// cout<<x<<" "<<fa[x]<<" "<<dp[x]<<" "<<endl;
		x=fa[x];
	}
}
void work(){
	n=read();q=read();
	for(int i=2;i<=n;i++)fa[i]=read(),e[fa[i]].pb(i);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read(),sum[fa[i]]+=b[i];
	mn[0]=inf;dfs(1);dfs(1,1);build(1,1,n);
	// for(int i=1;i<=n;i++)cout<<dfn[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<get(i)<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<c[i].k<<" "<<c[i].x<<" "<<c[i].y<<"\n";
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),x=read(),y=read();
			a[u]=x;upd(u);
			if(u>1){
				sum[fa[u]]+=y-b[u];
				if(u==son[fa[u]])b[u]=y;
				else del(fa[u],u),b[u]=y,dp[u]=get(u),ins(fa[u],u);
				upd(fa[u]);
			}
		}
		else{
			int u=read(),v=read();
			int valu=get(u),valv=get(v);
			// cout<<valu<<" "<<valv<<"\n";
			if(mkp(valu,u)>mkp(valv,v))puts("0");
			else puts("1");
		}
		// cout<<"run"<<endl;
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
