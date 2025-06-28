#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m,q;
vector<pii> e[maxn],g[maxn],h[maxn];
int d[maxn],rnk[maxn];
int st[maxn],tp;
int val[maxn],ans[maxn];
vector<tuple<int,int,int>> que[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		e[u].pb({v,w}),e[v].pb({u,w}),d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++)if(d[i]<=5)st[++tp]=i;
	for(int i=1;i<=n;i++){
		int u=st[i];rnk[u]=i;
		for(auto[v,w]:e[u])if(d[v]>5){
			d[v]--;
			if(d[v]<=5)st[++tp]=v;
		}
	}
	tp=0;
	for(int u=1;u<=n;u++){
		for(auto[v,w]:e[u])(rnk[u]<rnk[v]?g[u]:h[u]).pb({v,w});
	}
	auto ask=[&](int u,int v){
		int res=inf;
		for(auto[x,w1]:g[u]){
			for(auto[y,w2]:g[v])if(x==y)res=min(res,w1+w2);
		}
		return res;
	};
	// for(int i=1;i<=n;i++)assert(g[i].size()<=5);
	q=read();
	for(int i=1;i<=q;i++){
		int u=read(),v=read();
		que[u].pb({v,0,i}),que[v].pb({u,0,i}),ans[i]=ask(u,v);
		for(auto[x,w]:g[u])que[v].pb({x,w,i}),que[x].pb({v,w,i}),ans[i]=min(ans[i],ask(v,x)+w);
		for(auto[x,w]:g[v])que[u].pb({x,w,i}),que[x].pb({u,w,i}),ans[i]=min(ans[i],ask(u,x)+w);
	}
	for(int i=1;i<=n;i++)val[i]=inf;
	for(int u=1;u<=n;u++){
		st[++tp]=u,val[u]=0;
		for(auto[v,w1]:g[u]){
			for(auto[w,w2]:g[v])st[++tp]=w,val[w]=min(val[w],w1+w2);
		}
		for(auto[v,w1]:h[u]){
			for(auto[w,w2]:g[v])st[++tp]=w,val[w]=min(val[w],w1+w2);
		}
		for(auto[v,w,id]:que[u])ans[id]=min(ans[id],val[v]+w);
		for(auto[v,w1]:h[u]){
			for(auto[w,w2]:g[v]){
				for(auto[x,w3]:g[w])st[++tp]=x,val[x]=min(val[x],w1+w2+w3);
			}
		}
		for(auto[v,w,id]:que[u])if(!w)ans[id]=min(ans[id],val[v]);
		while(tp)val[st[tp--]]=inf;
	}
	for(int i=1;i<=q;i++)write(ans[i]==inf?-1:ans[i]),puts("");
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