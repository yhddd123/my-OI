// Problem: P7831 [CCO2021] Travelling Merchant
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7831
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-19 08:58:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,w,lim;
}e[maxn];
void add(int u,int v,int w,int l){e[++tot]={head[u],v,w,l};head[u]=tot;}
pii g[maxn];bool vis[maxn];
int d[maxn];
queue<int> q;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),c=read(),p=read();
		g[i]={c,i};add(v,u,p,c);d[u]++;
	}
	sort(g+1,g+m+1);
	for(int i=1;i<=n;i++)ans[i]=inf;
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	for(int j=m;j;j--){
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(vis[i])continue;vis[i]=1;
				if(ans[u]<inf)ans[v]=min(ans[v],max(ans[u]-e[i].w,e[i].lim));
				d[v]--;if(!d[v])q.push(v);
			}
		}
		if(!vis[g[j].se]){
			vis[g[j].se]=1;
			int u=e[g[j].se].to;
			ans[u]=min(ans[u],e[g[j].se].lim);
			d[u]--;if(!d[u])q.push(u);
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]==inf?-1:ans[i]);
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
