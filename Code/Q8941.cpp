#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
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

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dep[maxn],fa[maxn],siz[maxn],son[maxn],val[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1;siz[u]=1;son[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];val[v]=e[i].w;
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;
	if(!son[u])return ;
	dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs(v,v);
	}
}
// #define mid (l+r>>1)
// #define ls nd<<1
// #define rs nd<<1|1
// int tree[maxn<<2][2];
// void build(int nd,int l,int r){
	// if(l==r){
		// tree[nd][0]=tree[nd][1]=0;
		// tree[nd][val[dfn[l]]&1]=val[dfn[l]];
		// return ;
	// }
	// build(ls,l,mid),build(rs,mid+1,r);
	// tree[nd][0]=max(tree[ls][0],tree[rs][0]);
	// tree[nd][1]=max(tree[ls][1],tree[rs][1]);
// }
// int query(int nd,int l,int r,int ql,int qr,bool fl){
	// if(l>=ql&&r<=qr)return tree[nd][fl];
	// if(qr<=mid)return query(ls,l,mid,ql,qr,fl);
	// if(ql>mid)return query(rs,mid+1,r,ql,qr,fl);
	// return max(query(ls,l,mid,ql,qr,fl),query(rs,mid+1,r,ql,qr,fl));
// }
int mx[2][18][maxn];
void init(){
	for(int i=1;i<=n;i++)mx[val[i]&1][0][dfn[i]]=val[i],mx[(val[i]&1)^1][0][dfn[i]]=0;
	for(int fl=0;fl<2;fl++){
		for(int j=1;j<=17;j++){
			for(int i=1;i+(1<<j)-1<=n;i++)mx[fl][j][i]=max(mx[fl][j-1][i],mx[fl][j-1][i+(1<<j-1)]);
		}
	}
}
int query(int l,int r,int fl){
	if(l>r)return 0;
	int k=log2(r-l+1);
	return max(mx[fl][k][l],mx[fl][k][r-(1<<k)+1]);
}
int que(int u,int v,bool fl){
	int res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res=max(res,query(dfn[tp[u]],dfn[u],fl));
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	res=max(res,query(dfn[v]+1,dfn[u],fl));
	return res;
}
struct edge{
	int u,v,w;
	bool operator<(const edge&tmp)const{return w<tmp.w;}
}g[maxn<<2];
int f[maxn],vis[maxn<<2];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)g[i]={read(),read(),read()},vis[i]=0;
	sort(g+1,g+m+1);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)head[i]=fa[i]=0;tot=0;
	int ans0=0,ans1=0,num=0;
	for(int i=1;i<=m;i++){
		int u=fd(g[i].u),v=fd(g[i].v);
		if(u==v)continue;
		else{
			vis[i]=1;f[u]=v;
			add(g[i].u,g[i].v,g[i].w),add(g[i].v,g[i].u,g[i].w);
			ans0+=g[i].w;
			++num;
		}
	}
	if(num!=n-1){
		printf("-1 -1\n");
		return ;
	}
	if(ans0&1)ans1=ans0,ans0=inf;
	else ans1=inf;
	idx=0;dfs(1),dfs(1,1);
	init();
	for(int i=1;i<=m;i++)if(!vis[i]){
		int val=que(g[i].u,g[i].v,(g[i].w&1)^1);
		if(!val)continue;
		// cout<<g[i].w<<" "<<val<<"\n";
		if(ans0>ans1)ans0=min(ans0,ans1+g[i].w-val);
		else ans1=min(ans1,ans0+g[i].w-val);
	}
	if(ans0==inf)ans0=-1;
	if(ans1==inf)ans1=-1;
	printf("%lld %lld\n",ans0,ans1);
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
