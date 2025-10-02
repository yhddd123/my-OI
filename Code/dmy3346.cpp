#include<bits/stdc++.h>
#define ll long long
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
const int maxm=11;
const ll inf=1e18;
bool mbe;

int n,m,l,r;ll ans=inf;
tuple<int,int,int> edge[maxn];
int vis[maxn];
int id[maxn],k,rnk[maxn];
int lgx[1<<maxm];
struct graph{
	vector<int> iid;
	vector<tuple<int,int,int>> edge;
	int f[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	bool fl[maxm][maxm];
	ll res=0;
	void init(){
		vector<tuple<int,int,int>> tmp;
		for(int i:iid)f[i]=i;
		for(auto[w,u,v]:edge){
			if(fd(u)!=fd(v))f[fd(u)]=fd(v),tmp.pb({w,u,v});
		}
		swap(tmp,edge);tmp.clear();
		for(int i:iid)f[i]=i;
		for(int i=1;i<k;i++)f[fd(id[i])]=fd(id[i-1]);
		for(auto[w,u,v]:edge){
			if(fd(u)!=fd(v))f[fd(u)]=fd(v),tmp.pb({w,u,v}),res+=w;
		}
		for(int i:iid)f[i]=i;
		for(auto[w,u,v]:tmp){
			u=fd(u),v=fd(v);
			if(vis[v]==3)swap(u,v);
			f[fd(v)]=fd(u);
		}
		iid.clear();for(int i=1;i<=n;i++)if(vis[i]==3)iid.pb(i);
		tmp.clear();
		for(auto[w,u,v]:edge){
			if(fd(u)==fd(v))continue;
			if(fl[rnk[fd(v)]][rnk[fd(u)]])continue;
			fl[rnk[fd(u)]][rnk[fd(v)]]=fl[rnk[fd(v)]][rnk[fd(u)]]=1;
			tmp.pb({w,rnk[fd(u)],rnk[fd(v)]});
		}
		swap(tmp,edge);
		// for(int i:iid)cout<<i<<" ";cout<<"\n";
	}
	ll calc(vector<int> &a){
		ll ans=0;
		for(int i=0;i<k;i++)f[i]=i;
		for(int s:a){
			int ss=s,lst=-1;
			while(ss){
				int i=lgx[ss];
				if(~lst)f[fd(i)]=fd(lst);
				lst=i;
				ss^=1<<i;
			}
		}
		for(auto[w,u,v]:edge){
			u=fd(u),v=fd(v);
			if(u!=v)f[u]=v,ans+=w;
		}
		int num=0;for(int i=0;i<k;i++)num+=f[i]==i;
		if(num>1)ans=inf;
		return ans+res;
	}
}g[2];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> a;
ll val[1<<maxm],sum;
void dfs(int d,int s){
	if(d==-1){
		ll res=sum;
		res+=g[0].calc(a);
		if(res>inf)return ;
		res+=g[1].calc(a);
		ans=min(ans,res);
		return ;
	}
	dfs(d-1,s);
	for(int t=s;t;t=(t-1)&s)if(lgx[t]==d&&val[t]!=inf){
		a.pb(t);sum+=val[t];
		dfs(d-1,s^t);
		a.pop_back();sum-=val[t];
	}
}
bool fl[maxm][maxm];
void work(){
	n=read();m=read();l=read(),r=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		edge[i]={w,u,v};
	}
	sort(edge+1,edge+m+1);
	for(int i=1;i<=l;i++){
		int u=read();
		vis[u]^=1;g[0].iid.pb(u);
	}
	for(int i=1;i<=r;i++){
		int u=read();
		vis[u]^=2;g[1].iid.pb(u);
	}
	for(int i=1;i<=n;i++)if(vis[i]==3)id[k++]=i,rnk[i]=k-1;
	int mm=0;for(int i=1;i<=m;i++){
		auto[w,u,v]=edge[i];
		if(vis[u]==3&&vis[v]==3)edge[++mm]=edge[i];
		else if((vis[u]^vis[v])==3){}
		else if(vis[u]==1||vis[v]==1)g[0].edge.pb(edge[i]);
		else g[1].edge.pb(edge[i]);
	}
	m=mm;mm=0;
	for(int i=1;i<=m;i++){
		auto[w,u,v]=edge[i];
		u=rnk[u],v=rnk[v];
		if(fl[u][v])continue;
		edge[++mm]={w,u,v};fl[u][v]=fl[v][u]=1;
	}m=mm;
	g[0].init(),g[1].init();
	for(int s=1;s<(1<<k);s++){
		for(int i=0;i<k;i++)f[i]=i;
		for(int i=1;i<=m;i++){
			auto[w,u,v]=edge[i];
			if((s&(1<<u))&&(s&(1<<v))){
				if(fd(u)!=fd(v))f[fd(u)]=fd(v),val[s]+=w;
			}
		}
		int num=0;for(int i=0;i<k;i++)if(s&(1<<i))num+=f[i]==i;
		if(num>1)val[s]=inf;
	}
	for(int s=0;s<(1<<k);s++)lgx[s]=__lg(s);
	dfs(k-1,(1<<k)-1);
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