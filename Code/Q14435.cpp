#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,m,k,a[maxn],b[maxn];
pii tree[maxn];
#define lb(x) (x&(-x))
void upd(int x,pii w){while(x<=n)tree[x]=max(tree[x],w),x+=lb(x);}
pii que(int x){pii res={0,0};while(x)res=max(res,tree[x]),x-=lb(x);return res;}
int mx[maxn];
void upd1(int x,int w){while(x<=n)mx[x]=max(mx[x],w),x+=lb(x);}
int que1(int x){int res=0;while(x)res=max(res,mx[x]),x-=lb(x);return res;}
bool ans[maxn];
namespace sub1{
	bool vis[maxn];
	int pre[maxn];
	void sovle(){
		for(int i=1;i<=n;i++)a[i]=n-a[i]+1;
		pii mx={0,0};
		for(int i=1;i<=n;i++){
			pii dp=que(a[i]);dp.fi++;
			upd(a[i],{dp.fi,i}),pre[i]=dp.se,mx=max(mx,{dp.fi,i});
		}
		if(mx.fi<m){puts("No");return ;}
		puts("Yes");
		for(int i=mx.se;i&&m;i=pre[i])m--,ans[i]=1;
		for(int i=1;i<=n;i++)a[i]=n-a[i]+1;
		for(int i=1;i<=n;i++)if(ans[i])printf("%d ",a[i]);
	}
}
const int maxm=maxn*16;
int tot=1;
struct nd{
	int to,w,c;
}e[maxm<<4],edge[maxm<<4];
inline void add(int u,int v,int w=n,int c=0){
	edge[++tot]={v,w,c},edge[++tot]={u,0,-c};
}
int s,t,flow,cost;
int pl[maxm],pr[maxm],d[maxm],op[maxm<<2],pos[maxm<<2];
void reid(){
	for(int i=2;i<=tot;i++)d[edge[i].to]++;
	for(int i=1;i<=t;i++)d[i]+=d[i-1],pl[i]=d[i-1]+1,pr[i]=d[i];
	for(int i=2;i<=tot;i+=2){
		pos[i]=op[d[edge[i].to]]=d[edge[i^1].to];
		pos[i^1]=op[d[edge[i^1].to]]=d[edge[i].to];
		e[d[edge[i^1].to]--]=edge[i];
		e[d[edge[i].to]--]=edge[i^1];
	}
}
int h[maxm];bool vis[maxm];
void spfa(){
	queue<int> q;
	for(int i=1;i<=t;i++)h[i]=inf,vis[i]=0;
	h[s]=0,vis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=pl[u];i<=pr[u];i++){
			int v=e[i].to,val=h[u]+e[i].c;
			if(e[i].w&&h[v]>val){
				h[v]=val;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
}
int dis[maxm],eid[maxm];
vector<int> q[maxn];
int qq[maxm],hh,tt;
bool dij(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0;
	dis[s]=0;q[0].pb(s);
	auto upd=[&](int u){
		for(int i=pl[u];i<=pr[u];i++){
			nd &ee=e[i];
			int v=ee.to,nw=dis[u]+ee.c+h[u]-h[v];
			if(ee.w&&dis[v]>nw){
				dis[v]=nw;
				// eid[v]=i;
				if(dis[u]==nw)qq[++tt]=v;
				else q[dis[v]].pb(v);
			}
		}
	};
	for(int i=0;i<=-h[t];i++)if(q[i].size()){
		hh=1,tt=0;
		for(int u:q[i]){
			if(vis[u])continue;vis[u]=1;
			upd(u);
		}
		while(hh<=tt){
			int u=qq[hh++];
			if(vis[u])continue;vis[u]=1;
			upd(u);
		}
		if(vis[t])break;
	}
	for(int i=0;i<=-h[t];i++)q[i].clear();
	return dis[t]!=inf;
}
int rk[maxn],idx;
void sovle(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	if(r-l>=10)mid=(int)(l*0.3+r*0.7);
	sovle(l,mid),sovle(mid+1,r);
	sort(rk+l,rk+r+1,[&](int u,int v){return a[u]<a[v];});
	for(int i=l,lst=0;i<=r;i++){
		int p=rk[i];
		if(p<=mid){
			if(lst)add(p+n,lst);
		}
		else{
			int nw=++idx;
			add(nw,p);if(lst)add(nw,lst);
			lst=nw;
		}
	}
}
int rad[maxn];
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int i=rad[u];i<=pr[u];i++){
		int v=e[i].to;rad[u]=i+1;
		if(e[i].w&&h[u]-h[v]+e[i].c==0&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			res-=out;cnt+=out;
			e[i].w-=out;e[op[i]].w+=out;
			cost+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
int pre[maxn];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(k==1)return sub1::sovle();
	int mx1=0;
	for(int i=1;i<=n;i++){
		int dp=que1(a[i])+1;
		upd1(a[i],dp),mx1=max(mx1,dp);
	}
	if(mx1<k){puts("No");return ;}
	for(int i=1;i<=n;i++)b[a[i]]=i,rk[i]=i;
	for(int i=1;i<=n;i++)add(i,i+n,1,-1);
	idx=2*n;
	int cnt=n;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)if(a[i]>a[j])++cnt;
	}
	// cout<<cnt<<"\n";
	if(cnt+2*n<(maxm<<1)){
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++)if(a[i]>a[j])add(i+n,j);
		}
	}
	else sovle(1,n);
	s=++idx,t=++idx;
	for(int i=1;i<=n;i++)add(s,i,1,0),add(i+n,t,1,0);
	// for(int i=2;i<=tot;i+=2)cout<<e[i+1].to<<" "<<e[i].to<<" "<<e[i].w<<" "<<e[i].c<<"\n";
	reid();
	// cerr<<idx<<" "<<tot<<" "<<(maxm)<<endl;
	spfa();
	// cerr<<h[t]<<"\n";
	for(int i=0;i<=-h[t];i++)q[i].reserve(min(n,t/(i+1)+5));
	while(flow<k&&-cost<m&&dij()){
		for(int i=1;i<=t;i++)if(h[i]<inf)h[i]+=dis[i];
		// if(flow>=100&&h[t]==-1){
			for(int i=1;i<=t;i++)rad[i]=pl[i],vis[i]=0;
			flow+=dfs(s,k-flow);
		// }
		// else{
			// flow++;cost+=h[t];
			// for(int u=t;u!=s;u=e[op[eid[u]]].to)e[eid[u]].w--,e[op[eid[u]]].w++;
		// }
	}
	// cerr<<flow<<" "<<cost<<"\n";
	// cerr<<num<<"\n";
	if(-cost<m){puts("No");return ;}
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)if(!e[pos[2*i]].w)vis[i]=1;
	if(flow<k){
		int l=1,r=n,res=0;
		auto chk=[&](int p){
			for(int i=1;i<=n;i++)mx[i]=0;
			int mx1=0;
			for(int i=1;i<=n;i++)if(i<=p||vis[i]){
				int dp=que1(a[i])+1;
				upd1(a[i],dp),mx1=max(mx1,dp);
			}
			return mx1<=k;
		};
		while(l<=r){
			int mid=l+r>>1;
			if(chk(mid))l=mid+1,res=mid;
			else r=mid-1;
		}
		for(int i=1;i<=res;i++)vis[i]=1;
	}
	for(int i=1;i<=n;i++)tree[i]={0,0};
	pii mx={0,0};
	for(int i=1;i<=n;i++)if(vis[i]){
		pii dp=que(a[i]);dp.fi++;
		upd(a[i],{dp.fi,i}),pre[i]=dp.se,mx=max(mx,{dp.fi,i});
	}
	for(int i=mx.se;i&&m;i=pre[i])m--,ans[i]=1,vis[i]=0;
	for(int i=1;i<=n;i++)if(vis[i]&&m)ans[i]=1,m--;
	puts("Yes");
	for(int i=1;i<=n;i++)if(ans[i])write(a[i]),putchar(' ');
}

bool med;
signed main(){
	// freopen("c.in","r",stdin);
	// freopen("c.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}