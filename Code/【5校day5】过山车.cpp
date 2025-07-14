#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxm=155;
const int maxn=20010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w,c;
}e[10000010];
void add(int u,int v,int w,int c){
	// cout<<u<<" "<<v<<" "<<w<<" "<<c<<"\n";
	e[++tot]={head[u],v,w,-c};head[u]=tot;
	e[++tot]={head[v],u,0,c};head[v]=tot;
	assert(tot<=10000000);
}
int s,t,flow,ans;
int dis[maxn],rad[maxn];bool vis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,rad[i]=head[i],vis[i]=0;
	dis[s]=0,q.push(s),vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			cnt+=out,res-=out;
			ans+=e[i].c*out;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
int a[maxm][maxm],val[maxm][maxm];
int id(int u,int v){return (u-1)*m+v;}
void work(){
	n=read();m=read();s=n*m*3+1,t=n*m*3+2;
	int num=0,cnt=0,sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=1-read();
			if(!a[i][j])continue;
			if(i+j&1)++num,cnt++;
			else --num;
		}
	}
	if(num){puts("-1");return ;}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)val[i][j]=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]){
			sum+=val[i][j];
			if(i+j&1){
				add(s,id(i,j),2,0);
				add(id(i,j),id(i,j)+n*m,1,0),add(id(i,j),id(i,j)+n*m,1,val[i][j]);
				add(id(i,j),id(i,j)+2*n*m,1,0),add(id(i,j),id(i,j)+2*n*m,1,val[i][j]);
				if(a[i-1][j])add(id(i,j)+n*m,id(i-1,j)+n*m,1,0);
				if(a[i+1][j])add(id(i,j)+n*m,id(i+1,j)+n*m,1,0);
				if(a[i][j-1])add(id(i,j)+2*n*m,id(i,j-1)+2*n*m,1,0);
				if(a[i][j+1])add(id(i,j)+2*n*m,id(i,j+1)+2*n*m,1,0);
			}
			else{
				add(id(i,j),t,2,0);
				add(id(i,j)+n*m,id(i,j),1,0),add(id(i,j)+n*m,id(i,j),1,val[i][j]);
				add(id(i,j)+2*n*m,id(i,j),1,0),add(id(i,j)+2*n*m,id(i,j),1,val[i][j]);				
			}
		}
	}
	while(bfs())flow+=dfs(s,inf);
	if(flow!=cnt*2)puts("-1");
	else printf("%lld\n",-ans-sum);
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
	
	T=1;
	while(T--)work();
}
