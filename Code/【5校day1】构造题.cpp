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
const int maxn=10010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
pii a[maxn];
int id[maxn];
vector<int> e[maxn];
int col[maxn];
bool bk[maxn],vis[maxn];
void dfs(int u,int s){
	bk[u]=1;
	for(int v:e[u])if(vis[v]&&!bk[v]&&(s&(1<<col[v])))dfs(v,s);
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()},id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]>a[v];});
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	for(int i=1;i<=n;i++){
		int u=id[i];vis[u]=1;
		// cout<<u<<" "<<a[u].fi<<" "<<a[u].se<<"\n";
		int s=0;for(int v:e[u])if(vis[v])s|=(1<<col[v]);
		if(s!=30){
			for(int j=1;j<=4;j++)if(!(s&(1<<j)))col[u]=j;
			// cout<<s<<" "<<u<<" "<<col[u]<<"\n";
			continue;
		}
		int v1=0,v2=0,v3=0,v4=0;
		for(int v:e[u])if(vis[v]){
			if(a[u].fi==a[v].fi)v1=v;
			if(a[u].fi-a[u].se==a[v].fi-a[v].se)v2=v;
			if(a[u].se==a[v].se)v3=v;
			if(a[u].fi+a[u].se==a[v].fi+a[v].se)v4=v;
		}
		mems(bk,0);
		dfs(v1,(1<<col[v1])|(1<<col[v3]));
		if(bk[v3]){
			mems(bk,0);
			dfs(v2,(1<<col[v2])|(1<<col[v4]));
			int c1=col[v2],c2=col[v4];
			for(int j=1;j<=n;j++)if(vis[j]&&bk[j]){
				if(col[j]==c1)col[j]=c2;
				else col[j]=c1;
			}
			col[u]=c1;
		}
		else{
			int c1=col[v1],c2=col[v3];
			for(int j=1;j<=n;j++)if(vis[j]&&bk[j]){
				if(col[j]==c1)col[j]=c2;
				else col[j]=c1;
			}
			col[u]=c1;
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",col[i]);
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
