#include<bits/stdc++.h>
#define ll long long
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=250010;
const ll inf=1e18;
bool mbe;

int n;ll ans[maxn];
struct node{
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
ll dis[maxn];
int dfn[maxn],st[18][maxn],idx;
inline int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
void dfs(int u,int fa){
	st[0][dfn[u]=++idx]=fa;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dis[v]=dis[u]+e[i].w;dfs(v,u);
	}
}
inline int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
inline ll calc(int u,int v){return dis[u]+dis[v]-2*dis[lca(u,v)];}

int sz[maxn], mx[maxn], fa[maxn]; 
bool vis[maxn];
int allsz, root;

void getroot(int u, int f) {
    sz[u] = 1; mx[u] = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if(v == f || vis[v]) continue;
        getroot(v, u);
        sz[u] += sz[v];
        mx[u] = max(mx[u], sz[v]);
    }
    mx[u] = max(mx[u], allsz - sz[u]);
    if(root == 0 || mx[u] < mx[root]) root = u;
}

void getsz(int x, int fa) {
    sz[x] = 1; allsz++;
    for(int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to;
        if(v == fa || vis[v]) continue;
        getsz(v, x);
        sz[x] += sz[v];
    }
}

void build(int u,int f) {
    root = 0; allsz = 0;
    getsz(u, 0);
    getroot(u, 0);
    int cen = root;
    vis[cen] = 1;
    fa[cen] = f; 
    for(int i = head[cen]; i; i = e[i].nxt) {
        int v = e[i].to;
        if(vis[v]) continue;
        build(v, cen);
    }
}

void init(){
	dfs(1,0);
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	build(1,0);
}
}t1,t2;
const int maxm=1<<25;
struct hsh_table{
	int head[maxm],tot;
	struct nd{
		int nxt;
		ll key;
		ll val;
	}e[maxm];
	inline ll &operator[](ll key){
		int u=(key^(key>>32))&(maxm-1);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,inf};head[u]=tot;
		return e[tot].val;
	}
	inline void clear(){
		for(int i=1;i<=tot;i++)e[i].val=inf;
	}
}f;
int id1[20],id2[20],cnt1,cnt2;
ll d1[20],d2[20];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		t1.add(u,v,w),t1.add(v,u,w);
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		t2.add(u,v,w),t2.add(v,u,w);
	}
	t1.init(),t2.init();
	for(int i=1;i<=n;i++)ans[i]=inf;
	for(int i=1;i<=n;i++){
		cnt1=cnt2=0;
		int u=i;while(u)id1[++cnt1]=u,u=t1.fa[u];
		u=i;while(u)id2[++cnt2]=u,u=t2.fa[u];
		for(int j=1;j<=cnt1;j++)d1[j]=t1.calc(i,id1[j]);
		for(int j=1;j<=cnt2;j++)d2[j]=t2.calc(i,id2[j]);
		for(int j=1;j<=cnt1;j++){
			for(int k=1;k<=cnt2;k++){
				ll tmp=f[1ll*id1[j]*n+id2[k]]+d1[j]+d2[k];
				if(tmp<ans[i])ans[i]=tmp;
			}
		}
		for(int j=1;j<=cnt1;j++){
			for(int k=1;k<=cnt2;k++){
				ll &val=f[1ll*id1[j]*n+id2[k]];
				ll tmp=d1[j]+d2[k];
				if(tmp<val)val=tmp;
			}
		}
	}
	f.clear();
	for(int i=n;i;i--){
		cnt1=cnt2=0;
		int u=i;while(u)id1[++cnt1]=u,u=t1.fa[u];
		u=i;while(u)id2[++cnt2]=u,u=t2.fa[u];
		for(int j=1;j<=cnt1;j++)d1[j]=t1.calc(i,id1[j]);
		for(int j=1;j<=cnt2;j++)d2[j]=t2.calc(i,id2[j]);
		for(int j=1;j<=cnt1;j++){
			for(int k=1;k<=cnt2;k++){
				ll tmp=f[1ll*id1[j]*n+id2[k]]+d1[j]+d2[k];
				if(tmp<ans[i])ans[i]=tmp;
			}
		}
		for(int j=1;j<=cnt1;j++){
			for(int k=1;k<=cnt2;k++){
				ll &val=f[1ll*id1[j]*n+id2[k]];
				ll tmp=d1[j]+d2[k];
				if(tmp<val)val=tmp;
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen("frame.in","r",stdin);
	// freopen("frame.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}