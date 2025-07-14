#include<bits/stdc++.h>
using namespace std;
const int maxn=70010;
const int inf=2e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
vector<int> g[maxn];
int f[maxn][18],dep[maxn];
int mn[maxn][18],mx[maxn][18];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	for(int i=1;i<=17;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int v:g[u]){
		if(v!=fa)dfs(v,u);
	}
}
char c[2];
int b[maxn],len;
void sovle(int u,int v,int w,int fl){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=17;i>=0;i--){
		if(dep[f[u][i]]>=dep[v]){
			if(fl)mx[u][i]=min(mx[u][i],w);
			else mn[u][i]=max(mn[u][i],w);
			u=f[u][i];
		}
	}
	if(u==v)return ;
	for(int i=17;i>=0;i--){
		if(f[u][i]!=f[v][i]){
			if(fl)mx[u][i]=min(mx[u][i],w),mx[v][i]=min(mx[v][i],w);
			else mn[u][i]=max(mn[u][i],w),mn[v][i]=max(mn[v][i],w);
			u=f[u][i];v=f[v][i];
		}
	}
	if(fl)mx[u][0]=min(mx[u][0],w),mx[v][0]=min(mx[v][0],w);
	else mn[u][0]=max(mn[u][0],w),mn[v][0]=max(mn[v][0],w);
}
int head[maxn<<1],tot=1;
struct nd{
	int nxt,to,val;
}e[maxn<<3];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
struct edge{
	int x,y,w;
}mp[maxn];
int s,t,num;
int dis[maxn<<1],rad[maxn<<1];
queue<int> q;
bool bfs(){
	memset(dis,0,sizeof(dis));
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		rad[u]=head[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].val){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[t];
}
int flow(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=1;
		if(dis[v]==dis[u]+1&&e[i].val){
			int out=flow(v,min(e[i].val,res));
			e[i].val-=out;e[i^1].val+=out;
			res-=out;cnt+=out;
			if(!res)break;
		}
	}
	return cnt;
}
bool bk[maxn];

signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		g[u].push_back(v);g[v].push_back(u);
	}
	dfs(1,0);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=17;j++)mx[i][j]=inf,mn[i][j]=-inf;
	}
	m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",c+1);
		int u=read(),v=read(),w=read();
		b[++len]=w;
		if(c[1]=='M')sovle(u,v,w,1);
		else sovle(u,v,w,0);
	}
	b[++len]=inf;b[++len]=-inf;
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	for(int j=17;j>=1;j--){
		for(int i=1;i<=n;i++){
			mx[i][j-1]=min(mx[i][j-1],mx[i][j]),mn[i][j-1]=max(mn[i][j-1],mn[i][j]);
			mx[f[i][j-1]][j-1]=min(mx[f[i][j-1]][j-1],mx[i][j]),mn[f[i][j-1]][j-1]=max(mn[f[i][j-1]][j-1],mn[i][j]);
		}
	}
	for(int u=1;u<=n;u++){
		for(int v:g[u]){
			if(dep[u]>dep[v]){
				int p1=lower_bound(b+1,b+len+1,mx[u][0])-b,p2=lower_bound(b+1,b+len+1,mn[u][0])-b;
				mp[++num]={u,v,b[p1]};
				if(p1!=len)add(p1,num+len,1);
				if(p2!=1)add(p2,num+len,1);
				if(p1==len&&p2==1){
					printf("%d %d %d\n",u,v,inf);
					bk[num]=1;
				}
			}
		}
	}
	s=n+len;t=n+len+1;
	for(int i=2;i<len;i++)add(s,i,1);
	for(int i=len+1;i<=len+n-1;i++)add(i,t,1);
	while(bfs())flow(s,inf);
	for(int u=2;u<len;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!e[i].val&&v<n+len){
				printf("%d %d %d\n",mp[v-len].x,mp[v-len].y,b[u]);
				bk[v-len]=1;
			}
		}
	}
	for(int i=1;i<n;i++)if(!bk[i])printf("%d %d %d\n",mp[i].x,mp[i].y,mp[i].w);
}
