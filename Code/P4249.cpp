#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=110;
const int maxm=10110;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,mp[maxn][maxn];
int head[maxm],tot=1;
struct nd{
	int nxt,to,w,c;
}e[maxm<<3];
void add(int u,int v,int w,int f){
	e[++tot]={head[u],v,w,f};head[u]=tot;
	e[++tot]={head[v],u,0,-f};head[v]=tot;
}
int s,t,flow,ans;
int dis[maxm],rad[maxm];
bool vis[maxm];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=false,rad[i]=head[i];
	dis[s]=0;q.push(s);vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w>0&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])vis[v]=true,q.push(v);
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=true;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w>0&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(res,e[i].w));
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=false;
	return cnt;
}
void sovle(){
	n=read();
	s=n*n+n+1;t=n*n+n+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mp[i][j]=read();
			if(i>=j)continue;
			if(mp[i][j]==2){
				add(s,(i-1)*n+j,1,0);
				add((i-1)*n+j,n*n+i,1,0);
				add((i-1)*n+j,n*n+j,1,0);
			}
			if(mp[i][j]==1){
				add(s,(i-1)*n+j,1,0);
				add((i-1)*n+j,n*n+i,1,0);
			}
			if(mp[i][j]==0){
				add(s,(i-1)*n+j,1,0);
				add((i-1)*n+j,n*n+j,1,0);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<n;j++)add(n*n+i,t,1,j);
	}
	while(bfs())flow+=dfs(s,inf);
	ans=n*(n-1)*(n-2)/6-ans;
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(mp[i][j]==2){
				int u=(i-1)*n+j;
				for(int ii=head[u];ii;ii=e[ii].nxt){
					if(!e[ii].w&&e[ii].to!=s){
						if(e[ii].to-n*n==i)mp[i][j]=1,mp[j][i]=0;
						else mp[j][i]=1,mp[i][j]=0;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)printf("%lld ",mp[i][j]);
		printf("\n");
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
