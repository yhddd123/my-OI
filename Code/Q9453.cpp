#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=100010;
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
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int d[maxn],id[maxn],rnk[maxn];
vector<int> ans[maxn];
int fa[maxn],siz[maxn];
bool vis[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)d[i]=head[i]=0,ans[i].clear();tot=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++)id[i]=i,siz[i]=1;
	sort(id+1,id+n+1,[&](int u,int v){return d[u]>d[v];});
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	for(int u=1;u<=n;u++){
		fa[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(rnk[v]<rnk[u]&&(!fa[u]||rnk[v]>rnk[fa[u]]))fa[u]=v;
		}
		if(fa[u])ans[fa[u]].pb(u);
		// cout<<u<<" "<<fa[u]<<"\n";
	}
	for(int i=1;i<=n;i++)f[i]=i;
	for(int ii=n;ii;ii--){
		int u=id[ii];
		// cout<<siz[u]<<" "<<m<<"\n";
		for(int v:ans[u])f[v]=u,siz[u]+=siz[v];
		int num=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(fd(v)==u)++num;
		}
		if(num!=siz[u]){puts("No");return ;}
		m-=siz[u]-1;
	}
	if(m){puts("No");return ;}
	puts("Yes");
	for(int i=n;i;i--){
		printf("%lld %lld ",id[i],ans[id[i]].size());
		for(int j:ans[id[i]])printf("%lld ",j);puts("");
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
	
	T=read();
	while(T--)work();
}
