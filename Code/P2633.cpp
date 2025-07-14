#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int b[maxn],len,mp[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int rt[maxn],tree[maxn*25],cnt;
int ls[maxn*25],rs[maxn*25];
void build(int &nd,int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	build(ls[nd],l,mid);build(rs[nd],mid+1,r);
}
void updata(int &nd,int l,int r,int pre,int ql,int w){
	nd=++cnt;tree[nd]=tree[pre];
	ls[nd]=ls[pre];rs[nd]=rs[pre];
	if(l==r){
		tree[nd]+=w;
		return ;
	}
	int mid=l+r>>1;
	if(ql<=mid)updata(ls[nd],l,mid,ls[pre],ql,w);
	else updata(rs[nd],mid+1,r,rs[pre],ql,w);
	tree[nd]=tree[ls[nd]]+tree[rs[nd]];
}
int dep[maxn],f[maxn][21];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;f[u][0]=fa;
	for(int i=1;i<=20;i++)f[u][i]=f[f[u][i-1]][i-1];
	updata(rt[u],1,len,rt[f[u][0]],a[u],1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=20;i>=0;i--){
		if(dep[f[u][i]]>=dep[v])u=f[u][i];
	}
	if(u==v)return u;
	for(int i=20;i>=0;i--){
		if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}
int query(int nd,int fnd,int nd1,int nd2,int l,int r,int num){
	if(l==r)return l;
	int mid=l+r>>1;
	if(tree[ls[nd1]]+tree[ls[nd2]]-tree[ls[nd]]-tree[ls[fnd]]>=num)return query(ls[nd],ls[fnd],ls[nd1],ls[nd2],l,mid,num);
	else return query(rs[nd],rs[fnd],rs[nd1],rs[nd2],mid+1,r,num-(tree[ls[nd1]]+tree[ls[nd2]]-tree[ls[nd]]-tree[ls[fnd]]));
}
int u,v,k,tp,ans;

int T;
signed main(){
//		freopen("P2633_1.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i];
	sort(b+1,b+n+1);
	len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		u=a[i];
		a[i]=lower_bound(b+1,b+len+1,a[i])-b;
		mp[a[i]]=u;
	}
	for(int i=1;i<n;i++){
		u=read();v=read();
		add(u,v);add(v,u);
	}
	build(rt[0],1,len);
	dfs(1,0);
	while(m--){
		u=read()^ans;v=read();k=read();
		tp=lca(u,v);
		ans=mp[query(rt[tp],rt[f[tp][0]],rt[u],rt[v],1,len,k)];
		printf("%lld\n",ans);
	}
}
