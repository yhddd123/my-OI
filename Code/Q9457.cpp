#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=3010;
const int maxm=2000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int pre[maxm],cnt;
bool vis[maxm];
void init(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0)break;
		}
	}
}
int n,k,a[maxn];
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn*maxn];
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<" "<<w<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int rad[maxn],dis[maxn];
bool bk[maxn];
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;if(bk[v])continue;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			cnt+=out,res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		// cout<<u<<" "<<dis[u]<<endl;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(bk[v])continue;
			if(e[i].w&&!dis[v]){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[t];
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n+2;i++)head[i]=0;tot=1;
	int cnt=0,sum=0;
	s=n+1,t=n+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++)if(!vis[a[i]+a[j]]){
			bk[i]=bk[j]=1;
			if(a[i]==1&&a[j]==1)continue;
			if(a[i]&1)add(i,j,1);
			else add(j,i,1);
		}
		if(a[i]&1)add(s,i,1);
		else add(i,t,1);
	}
	for(int i=1;i<=n;i++)if(bk[i])++sum,bk[i]=0;
	for(int i=1;i<=n;i++)if(a[i]==1)bk[i]=1,++cnt;
	int flow=0;
	while(bfs())flow+=dfs(s,inf);
	for(int i=1;i<=n;i++)if(a[i]==1)bk[i]=0;
	int num=0;
	while(bfs())num+=dfs(s,inf);
	flow+=num;
	// cout<<flow<<" "<<num<<" "<<cnt<<" "<<sum<<"\n";
	if(k<=flow)printf("%lld\n",k*2);
	else{
		if(k-flow<=(cnt-num)/2)printf("%lld\n",k*2);
		else printf("%lld\n",min(sum,flow*2+(cnt-num)/2*2+k-flow-(cnt-num)/2));
	}
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();init(maxm-10);
	while(T--)work();
}
