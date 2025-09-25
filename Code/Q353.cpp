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
const int inf=1e9;
bool mbe;

int n,m,ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],rnk[maxn],idx,st[19][maxn];
int fa[maxn],dep[maxn],siz[maxn];
void dfs(int u){
	rnk[dfn[u]=++idx]=u;st[0][dfn[u]]=fa[u];
	dep[u]=dep[fa[u]]+1;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
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
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
struct node{
	int x,y,tp,w;
}a[maxn];
vector<int> pos[maxn];
int f[maxn],sum[maxn],g[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){while(x<=n)tree[x]+=w,x+=lb(x);}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void dfsf(int u){
	f[u]=sum[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		dfsf(v);sum[u]+=f[v];
	}
	f[u]=sum[u];
	for(int id:pos[u]){
		a[id].w+=sum[u]-que(dfn[a[id].x])-que(dfn[a[id].y]);
		f[u]=max(f[u],a[id].w);
	}
	upd(dfn[u],f[u]-sum[u]),upd(dfn[u]+siz[u],-f[u]+sum[u]);
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2];
void modif(int nd,int l,int r,int p,int w){
	mx[nd]=max(mx[nd],w);
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(l>=ql&&r<=qr)return mx[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void dfsg(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		g[v]=g[u]+sum[u]-f[v];
		for(int id:pos[u])if(!in(v,a[id].x)&&!in(v,a[id].y)){
			g[v]=max(g[v],g[u]+a[id].w-f[v]);
			break;
		}
		g[v]=max(g[v],query(1,1,n,dfn[u],dfn[v]-1)-f[v]);
		g[v]=max(g[v],query(1,1,n,dfn[v]+siz[v],dfn[u]+siz[u]-1)-f[v]);
	}
	for(int id:pos[u]){
		modif(1,1,n,dfn[a[id].x],g[u]+a[id].w);
		modif(1,1,n,dfn[a[id].y],g[u]+a[id].w);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		dfsg(v);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1);
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		a[i]={u,v,lca(u,v),w};
		pos[a[i].tp].pb(i);
	}
	dfsf(1);
	for(int i=1;i<=n;i++)sort(pos[i].begin(),pos[i].end(),[&](int u,int v){return a[u].w>a[v].w;});
	dfsg(1);
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<g[i]<<" ";cout<<"\n";
	for(int u=1;u<=n;u++){
		int num=n*n;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==fa[u])continue;
			num-=siz[v]*siz[v];
		}
		num-=(n-siz[u])*(n-siz[u]);
		// cout<<num<<"\n";
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==fa[u])continue;
			int num1=num-2*siz[v]*(n-siz[v]);
			// cout<<u<<" "<<v<<" "<<f[v]<<" "<<num1<<" a\n";
			(ans+=(num1%mod)*(f[v]%mod))%=mod;
		}
	}
	for(int u=1;u<=n;u++){
		int num=siz[u]*siz[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==fa[u])continue;
			num-=siz[v]*siz[v];
		}
		(ans+=(num%mod)*(g[u]%mod))%=mod;
	}
	ans=(n*n%mod*(f[1]%mod)+mod-ans)%mod;
	printf("%lld\n",ans);
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