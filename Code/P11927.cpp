// Problem: P11927 [PA 2025] 重金属 / Heavy Metal
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11927
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-03-27 16:51:54
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=110;
const int inf=1e9;
const int B=100000;
bool mbe;

int n,m,a[maxn],ans;
vector<tuple<int,int,int>> edge;
vector<pii> e[maxn];
int f[maxn][B+10],g[maxn][inf/B+10];
bool vis[maxn];
void work(){
	n=read();m=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)e[i].clear();
	edge.clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		edge.pb({u,v,w}),e[u].pb({v,w});
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=B;j++)f[i][j]=0;
	}
	f[1][1]=1;
	for(int w=1;w<=B;w++){
		queue<int> q;
		for(int i=1;i<=n;i++)if(f[i][w])q.push(i);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(auto[v,ww]:e[u]){
				if(w*ww<=B&&w*ww<=a[v]&&!f[v][w*ww]){
					f[v][w*ww]=1;
					if(ww==1)q.push(v);
				}
			}
		}
	}
	for(int i=1;i<=n;i++)e[i].clear();
	for(auto[u,v,w]:edge)e[v].pb({u,w});
	for(int i=1;i<=n;i++){
		for(int j=1;j<=inf/B;j++)g[i][j]=0;
	}
	g[n][1]=a[n];
	for(int w=1;w<=inf/B;w++){
		for(int i=1;i<=n;i++)vis[i]=0;
		priority_queue<pii> q;
		for(int i=1;i<=n;i++)if(g[i][w])q.push({-g[i][w],i});
		while(!q.empty()){
			int u=q.top().se;q.pop();
			if(vis[u])continue;vis[u]=1;
			for(auto[v,ww]:e[u]){
				if(w*ww<=inf/B&&g[v][w*ww]<min(g[u][w]/ww,a[v])){
					g[v][w*ww]=min(g[u][w]/ww,a[v]);
					if(ww==1)q.push({-g[v][w*ww],v});
				}
			}
		}
	}
	// for(int u=1;u<=n;u++){
		// for(int w=1;w<=B;w++)if(f[u][w])cout<<u<<" "<<w<<"\n";
	// }
	// for(int u=1;u<=n;u++){
		// for(int w=1;w<=inf/B;w++)if(g[u][w])cout<<u<<" "<<w<<" "<<g[u][w]<<"\n";
	// }
	for(auto[u,v,w]:edge){
		for(int i=1,j=inf/B;i<=B;i++)if(f[u][i]){
			while(j&&g[v][j]<i*w)j--;
			ans=max(ans,i*w*j);
			if(!j)break;
			// cout<<u<<" "<<v<<" "<<i<<" "<<w<<" "<<j<<"\n";
		}
	}
	if(n>1&&!ans)ans=-1;
	printf("%lld\n",ans);
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