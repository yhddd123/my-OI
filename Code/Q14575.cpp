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
const int inf=1e18;
bool mbe;

int op,n,m;
namespace sub1{
	vector<pii> e[maxn];
	bool vis[maxn];
	int a[maxn];
	int dfn[maxn],idx;
	void dfs(int u,int fa){
		dfn[u]=++idx;
		for(auto[v,w]:e[u]){
			if(!dfn[v])dfs(v,u);
			else if(dfn[v]<dfn[u])a[u]+=w;
		}
	}
	int f[maxn],s[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void sovle(){
		for(int i=1;i<=n;i++)f[i]=i,s[i]=0;
		while(m--){
			int u=read(),v=read(),w=read();
			e[u].pb({v,w}),e[v].pb({u,w});
			u=fd(u),v=fd(v);
			if(u!=v)s[u]+=s[v]+w,f[v]=u;
			else s[u]+=w;
		}
		pii mn={inf,0};
		for(int i=1;i<=n;i++)if(f[i]==i)mn=min(mn,{s[i],i});
		dfs(mn.se,0);
		for(int i=1;i<=n;i++)printf("%lld ",a[i]);
	}
}
namespace sub2{
	vector<pii> e[maxn];
	bool vis[maxn];
	queue<int> q;
	int a[maxn];
	int f[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void sovle(){
		for(int i=1;i<=n;i++)f[i]=i;
		while(m--){
			int u=read(),v=read(),w=read();
			e[u].pb({v,w}),e[v].pb({u,w});
			a[u]-=w,a[v]-=w;
			f[fd(u)]=fd(v);
		}
		for(int i=1;i<=n;i++)a[i]+=read();
		for(int i=1;i<=n;i++)if(a[i]>=0)q.push(i),vis[i]=1;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(auto[v,w]:e[u])if(!vis[v]){
				a[v]+=w;
				if(a[v]>=0)q.push(v),vis[v]=1;
			}
		}
		for(int i=1;i<=n;i++)vis[fd(i)]&=vis[i];
		for(int i=1;i<=n;i++)if(i==f[i]&&vis[i]){puts("YES");return ;}
		puts("NO");
	}
}
void work(){
	op=read();n=read();m=read();
	if(op==1)return sub1::sovle();
	else return sub2::sovle();
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