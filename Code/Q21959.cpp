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
const int maxn=30010;
const int inf=1e9;
bool mbe;

int n,m;
vector<pii> e[maxn];
int siz[maxn],ww[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,ww[u]=0;
	for(auto[v,w]:e[u]){
		if(v==fa||vis[v])continue;
		getrt(v,u);siz[u]+=siz[v];
		ww[u]=max(ww[u],siz[v]);
	}
	ww[u]=max(ww[u],sum-siz[u]);
	if(ww[u]<=sum/2)rt=u;
}
int dis[maxn];
int dfn[maxn],rnk[maxn],idx;
void dfs(int u,int fa){
	siz[u]=1;rnk[dfn[u]=++idx]=u;
	for(auto[v,w]:e[u]){
		if(v==fa||vis[v])continue;
		dis[v]=dis[u]+w;
		dfs(v,u);siz[u]+=siz[v];
	}
}
bool bk[10000010];
int que[maxn];
bool ans[maxn];
void sovle(int u){
	vis[u]=1;idx=dis[u]=0;dfs(u,0);
	bk[0]=1;
	for(auto[v,w]:e[u]){
		if(vis[v])continue;
		for(int j=dfn[v];j<dfn[v]+siz[v];j++){
			int p=rnk[j];
			for(int k=1;k<=m;k++)if(!ans[k]){
				if(que[k]>=dis[p]&&bk[que[k]-dis[p]])ans[k]=1;
			}
		}
		for(int j=dfn[v];j<dfn[v]+siz[v];j++){
			int p=rnk[j];
			if(dis[p]<=10000000)bk[dis[p]]=1;
		}
	}
	for(int i=1;i<=idx;i++){
		int p=rnk[i];
		if(dis[p]<=10000000)bk[dis[p]]=0;
	}
	for(auto[v,w]:e[u]){
		if(vis[v])continue;
		sum=siz[v];getrt(v,u);
		sovle(rt);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		e[u].pb({v,w}),e[v].pb({u,w});
	}
	for(int i=1;i<=m;i++)que[i]=read();
	sum=n;getrt(1,0);sovle(rt);
	for(int i=1;i<=m;i++)puts(ans[i]?"Yes":"No");
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