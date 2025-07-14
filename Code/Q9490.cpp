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
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
pii a[maxn];
struct nd{
	int nxt,to,w;
}e[maxn*maxn<<2];
int head[maxn],tot=1,s,t,flow;
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<" "<<w<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int rad[maxn],dis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]={read(),read()};
	sort(a+1,a+m+1);s=2*m+1,t=2*m+2;
	for(int i=1;i<=m;i++){
		add(s,i,1);add(i+m,t,1);
	}
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			if(max(min(a[i].se,a[j].se)-a[j].fi+1,0ll)&1){
				add(i,j+m,inf),add(j,i+m,inf);
			}
		}
	}
	while(bfs())flow+=dfs(s,inf);
	// cout<<flow<<"\n";
	printf("%lld\n",m-flow/2);
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
