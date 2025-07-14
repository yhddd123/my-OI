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
const int maxn=100010;
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
pii a[maxn],b[maxn];
bool vis[maxn];
map<int,set<pii>> s1,s2;
int head[maxn<<1],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn*6];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int dis[maxn<<1],rad[maxn<<1];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v]){
				dis[v]=dis[u]+1,q.push(v);
			}
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			res-=out,cnt+=out;
			e[i].w-=out,e[i^1].w+=out;
			if(!res)break;
		}
	}
	return cnt;
}
int id[maxn],ans,sum;
void work(){
	n=read();m=read();k=m-read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	for(int i=1;i<=m;i++)b[i]={read(),read()};
	for(int i=1;i<=m;i++)vis[i]=0;
	s1.clear();for(int i=1;i<=n;i++)s1[a[i].fi].insert({a[i].se,i});
	s2.clear();for(int i=1;i<=n;i++)s2[a[i].se].insert({a[i].fi,i});
	s=2*n+1,t=2*n+2;
	for(int i=1;i<=t;i++)head[i]=0;tot=1;
	for(int i=1;i<=m;i++){
		if(s1.find(b[i].fi)==s1.end()||s2.find(b[i].se)==s2.end())continue;
		auto it=s1[b[i].fi].lower_bound({b[i].se,0});
		if(it==s1[b[i].fi].end())continue;
		if(it==s1[b[i].fi].begin())continue;
		int u=(*--it).se;
		it=s2[b[i].se].lower_bound({b[i].fi,0});
		if(it==s2[b[i].se].end())continue;
		if(it==s2[b[i].se].begin())continue;
		int v=(*--it).se;
		add(u,v+n,1),id[tot/2]=i;
	}
	int lst=tot;
	for(int i=1;i<=n;i++)add(s,i,1),add(i+n,t,1);
	flow=ans=sum=0;
	for(auto[x,s]:s1)sum+=s.size()-1;
	for(auto[x,s]:s2)sum+=s.size()-1;
	while(bfs())flow+=dfs(s,inf);
	if(k){
		for(int i=2;i<=lst;i+=2)if(!e[i].w){
			int p=id[i/2];
			vis[p]=1,k--,ans+=2;
			s1[b[p].fi].insert({b[p].se,0});
			s2[b[p].se].insert({b[p].fi,0});
			if(!k)break;
		}
	}
	if(k){
		for(int i=1;i<=m;i++)if(!vis[i]){
			if(s1.find(b[i].fi)==s1.end())continue;
			auto it=s1[b[i].fi].lower_bound({b[i].se,0});
			if(it==s1[b[i].fi].end())continue;
			if(it==s1[b[i].fi].begin())continue;
			if(!(*it).se||!(*--it).se)continue;
			vis[i]=1,k--,++ans;
			if(!k)break;
			s1[b[i].fi].insert({b[i].se,0});
		}
	}
	if(k){
		for(int i=1;i<=m;i++)if(!vis[i]){
			if(s2.find(b[i].se)==s2.end())continue;
			auto it=s2[b[i].se].lower_bound({b[i].fi,0});
			if(it==s2[b[i].se].end())continue;
			if(it==s2[b[i].se].begin())continue;
			if(!(*it).se||!(*--it).se)continue;
			vis[i]=1,k--,++ans;
			if(!k)break;
			s2[b[i].se].insert({b[i].fi,0});
		}
	}
	if(k){
		for(int i=1;i<=m;i++)if(!vis[i]){
			vis[i]=1,k--;
			if(!k)break;
		}
	}
	// assert(!k);
	printf("%lld\n",sum-ans);
	for(int i=1;i<=m;i++)if(!vis[i])printf("%lld ",i);puts("");
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
