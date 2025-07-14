// Problem: P9402 [POI 2020/2021 R3] Droga do domu
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9402
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-10-10 12:47:14
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=60010;
const ll inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,s,t,idx;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn*3];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
map<pii,ll> mp;
ll dis[maxn][110];
priority_queue<pair<ll,pii>> q;
int a[maxn];
ll x[maxn],y[maxn];
bool vis[maxn][110];
void work(){
	n=read();m=read();s=read();k=read()+1;t=read();idx=n;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		mp[{u,v}]=mp[{v,u}]=w;
	}
	for(int i=1;i<=s;i++){
		int num=read(),yy=read(),xx=read();
		for(int j=1;j<=num;j++){
			a[j]=read();x[idx+j]=xx;
			add(a[j],idx+j,0);add(idx+j,a[j],0);
		}
		y[idx+1]=yy;
		for(int j=2;j<=num;j++){
			add(idx+j-1,idx+j,mp[{a[j-1],a[j]}]);
			y[idx+j]=y[idx+j-1]+mp[{a[j-1],a[j]}];
		}
		idx+=num;
	}
	mems(dis,0x3f);dis[1][0]=t;q.push({-dis[1][0],{1,-0}});
	while(!q.empty()){
		int u=q.top().se.fi,id=-q.top().se.se;q.pop();
		if(vis[u][id])continue;vis[u][id]=1;
		// cout<<u<<" "<<id<<" "<<dis[u][id]<<endl;
		if(u<=n){
			if(id==k)continue;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				ll nw=max(dis[u][id],y[v])+(x[v]-(max(dis[u][id],y[v])-y[v])%x[v])%x[v];
				if(dis[v][id+1]>nw){
					dis[v][id+1]=nw,q.push({-dis[v][id+1],{v,-id-1}});
				}
			}
		}
		else{
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(dis[v][id]>dis[u][id]+e[i].w){
					dis[v][id]=dis[u][id]+e[i].w,q.push({-dis[v][id],{v,-id}});
				}
			}
		}
	}
	ll ans=inf;
	for(int i=0;i<=k;i++)ans=min(ans,dis[n][i]);
	if(ans==inf)puts("NIE");
	else printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("hoshitetsu.in","r",stdin);
	// freopen("hoshitetsu.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
