#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=110;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}


int n,m,s,t,ans;
int b[maxn][maxn],w[maxn][maxn],sb[maxn][maxn],sw[maxn][maxn];
int fx[5][2]={{1,0},{-1,0},{0,1},{0,-1},{0,0}};

struct nd{
	int nxt,to,val;
}e[500010];
int head[40010],tot=1; 
void add(int u,int v,int w){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;
	head[u]=tot;
}

int rad[40010],dis[40010];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
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
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].val){
			int out=dfs(v,min(e[i].val,res));
			e[i].val-=out;e[i^1].val+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
int flow(){
	int res=0;
	while(bfs()){
		res+=dfs(s,inf);
	}
	return res;
}

int cal(int u,int v){return (u-1)*m+v;}
bool in(int u,int v){
	if(u>=1&&u<=n&&v>=1&&v<=m)return true;
	return false;
}

void sovle(){
	n=read();m=read();s=3*n*m+1;t=3*n*m+2;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=read(),ans+=b[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)w[i][j]=read(),ans+=w[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)sb[i][j]=read(),ans+=sb[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)sw[i][j]=read(),ans+=sw[i][j];
	 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			add(s,cal(i,j),b[i][j]);add(cal(i,j),s,0);
			add(cal(i,j),t,w[i][j]);add(t,cal(i,j),0);
			add(s,1*n*m+cal(i,j),sb[i][j]);add(1*n*m+cal(i,j),s,0);
			add(2*n*m+cal(i,j),t,sw[i][j]);add(t,2*n*m+cal(i,j),0);
			for(int k=0;k<5;k++){
				int nx=i+fx[k][0];int ny=j+fx[k][1];
				if(in(nx,ny)){
					add(1*n*m+cal(i,j),cal(nx,ny),inf);add(cal(nx,ny),1*n*m+cal(i,j),0);
					add(cal(nx,ny),2*n*m+cal(i,j),inf);add(2*n*m+cal(i,j),cal(nx,ny),0);
				}
			}
		}
	}
	ans-=flow();
	printf("%lld",ans);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	T=1;
	while(T--)sovle();
}

