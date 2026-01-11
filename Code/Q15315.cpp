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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,s,a[maxn],ss;
vector<int> e[maxn];
bool vis[maxn];
int st[maxn],tp,dep[maxn];
vector<int> ans;
void dfs(int u,int fa){
	st[++tp]=u;vis[u]=1;dep[u]=dep[fa]+1;
	for(int v:e[u]){
		if(!vis[v]){
			ans.pb(v),a[v]^=1;
			dfs(v,u);
			ans.pb(u),a[u]^=1;
			if(a[v])ans.pb(v),ans.pb(u),a[v]^=1,a[u]^=1;
		}
		else if(ss&&dep[v]<=dep[u]&&((dep[u]-dep[v]+1)&1)){
			for(int i=dep[v];i<=dep[u];i++)a[st[i]]^=1,ans.pb(st[i]);
			ss=0;
		}
	}
	tp--;
}
void work(){
	n=read();m=read();s=read();ss=0;ans.clear();
	for(int i=1;i<=n;i++)a[i]=read()&1,ss^=a[i];
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	for(int i=1;i<=n;i++)vis[i]=0;
	dfs(s,0);
	if(ss){puts("No");return ;}
	for(int i=1;i<=n;i++)if(a[i]){puts("No");return ;}
	puts("Yes");
	printf("%lld\n",ans.size());
	for(int u:ans)printf("%lld ",u);puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}