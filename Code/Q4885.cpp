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
const int maxn=300010;
const int inf=1e18;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0;char c=getchar();while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define put() putchar(' ')
#define endl puts("")
bool Mbe;

int id,n,m,q;
pii a[maxn];
bool fl[maxn];
int vis[maxn];
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){
	if(m<n||m<0||n<0)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	// cout<<u<<" "<<v<<"\n";
	e[++tot]={head[u],v};head[u]=tot;
}
vector<pii> g[maxn];
int d[maxn];
int num[maxn],dep[maxn];
int to[maxn][20];
void dfs(int u,int fa){
	to[u][0]=fa;dep[u]=dep[fa]+1;num[u]=num[fa]+(u>n);
	for(int i=1;i<=19;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=19;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=19;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
void work(){
	n=read();m=read();int idx=n;
	fac[0]=1;for(int i=1;i<maxn;i++)fac[i]=fac[i-1]*i%mod;
	inv[maxn-1]=ksm(fac[maxn-1]);for(int i=maxn-2;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		d[u]++,d[v]++;
		a[i]={u,v};
	}
	for(int i=1;i<=m;i++){
		int u=a[i].fi,v=a[i].se;
		if(d[u]>d[v]||(d[u]==d[v]&&u>v))g[u].pb({v,i});
		else g[v].pb({u,i});
	}
	for(int u=1;u<=n;u++){
		for(pii v:g[u])vis[v.fi]=v.se;
		for(pii v:g[u]){
			for(pii w:g[v.fi])if(vis[w.fi]){
				// cout<<u<<" "<<v.fi<<" "<<w.fi<<"\n";
				fl[v.se]=fl[w.se]=fl[vis[w.fi]]=1;
				++idx;
				add(idx,u),add(u,idx);
				add(idx,v.fi),add(v.fi,idx);
				add(idx,w.fi);add(w.fi,idx);
			}
		}
		for(pii v:g[u])vis[v.fi]=0;
	}
	for(int i=1;i<=m;i++)if(!fl[i])add(a[i].fi,a[i].se),add(a[i].se,a[i].fi);
	dfs(1,0);
	q=read();
	while(q--){
		int u=read(),v=read(),w=read(),tp=lca(u,v);
		// cout<<u<<" "<<v<<" "<<tp<<" "<<num[u]+num[v]-2*num[tp]+(tp>n)<<" "<<dep[u]+dep[v]-2*dep[tp]-w<<"\n";
		write(C(num[u]+num[v]-2*num[tp]+(tp>n),dep[u]+dep[v]-2*dep[tp]-w));puts("");
	}
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("chtholly.in","r",stdin);
	// freopen("chtholly.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
