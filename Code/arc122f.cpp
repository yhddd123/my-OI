// Problem: AT_arc122_f [ARC122F] Domination
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc122_f
// Memory Limit: 1 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2025-04-01 16:43:33
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
const int maxn=100010;
const int maxv=700010;
const int inf=1e12;
bool mbe;

int n,m,k;
pii a[maxn],b[maxn];
int st[maxn],tp;
int head[maxv],tot=1;
struct nd{
	int nxt,to,w,c;
}e[maxv*5];
void add(int u,int v,int w,int c){
	// if(w==inf)cout<<u<<" "<<v<<" inf-"<<c<<"\n";
	// else cout<<u<<" "<<v<<" "<<w<<"-"<<c<<"\n";
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int s,t,flow,ans;
int h[maxv],dis[maxv],pre[maxv],eid[maxv];
bool vis[maxv];
priority_queue<pii> q;
bool dij(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0;
	dis[s]=0,q.push({0,s});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,ww=e[i].c+h[u]-h[v];
			if(e[i].w&&dis[v]>dis[u]+ww){
				dis[v]=dis[u]+ww,pre[v]=u,eid[v]=i;
				q.push({-dis[v],v});
			}
		}
	}
	return dis[t]!=inf;
}
int id[7][maxn],idx;
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	for(int i=1;i<=m;i++)b[i]={read(),read()};
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		while(tp&&a[i].se>=a[st[tp]].se)tp--;
		st[++tp]=i;
	}
	n=0;for(int i=1;i<=tp;i++)a[++n]=a[st[i]];
	for(int j=0;j<2;j++){
		for(int i=1;i<=m;i++)id[j][i]=++idx;
	}
	for(int j=2;j<7;j++){
		for(int i=1;i<=n;i++)id[j][i]=++idx;
	}
	id[6][n+1]=++idx;
	s=id[6][1],t=id[6][n+1];
	for(int i=1;i<=m;i++)add(id[0][i],id[1][i],1,0);
	for(int i=1;i<=n;i++)add(id[6][i],id[2][i],inf,0),add(id[6][i],id[3][i],inf,0);
	for(int i=2;i<=n;i++)add(id[2][i-1],id[2][i],inf,a[i-1].se-a[i].se);
	for(int i=2;i<=n;i++)add(id[3][i],id[3][i-1],inf,0);
	for(int i=1;i<=m;i++){
		int l=1,r=n,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(a[mid].se>=b[i].se)l=mid+1,res=mid;
			else r=mid-1;
		}
		if(res)add(id[2][res],id[0][i],inf,a[res].se-b[i].se);
		if(res<n)add(id[3][res+1],id[0][i],inf,0);
	}
	for(int i=1;i<=n;i++)add(id[4][i],id[6][i+1],inf,0),add(id[5][i],id[6][i+1],inf,0);
	for(int i=2;i<=n;i++)add(id[4][i],id[4][i-1],inf,0);
	for(int i=2;i<=n;i++)add(id[5][i-1],id[5][i],inf,a[i].fi-a[i-1].fi);
	for(int i=1;i<=m;i++){
		int l=1,r=n,res=n+1;
		while(l<=r){
			int mid=l+r>>1;
			if(a[mid].fi>=b[i].fi)r=mid-1,res=mid;
			else l=mid+1;
		}
		if(res>1)add(id[1][i],id[4][res-1],inf,0);
		if(res<=n)add(id[1][i],id[5][res],inf,a[res].fi-b[i].fi);
	}
	while(dij()&&flow<k){
		int mn=k-flow;
		for(int u=t;u!=s;u=pre[u])mn=min(mn,e[eid[u]].w);
		for(int u=t;u!=s;u=pre[u]){
			e[eid[u]].w-=mn,e[eid[u]^1].w+=mn;
			ans+=mn*e[eid[u]].c;
			// cout<<u<<" "<<ans<<"\n";
		}
		flow+=mn;
		for(int i=1;i<=t;i++)h[i]+=dis[i];
	}
	printf("%lld\n",ans);
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