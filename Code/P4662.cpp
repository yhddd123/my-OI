#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}


int n,m,s,t,ans;
struct nd{
	int nxt,to,val;
}e[500010];
int head[40010],tot=1; 
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int rad[40010],dis[40010];
queue<int> q;
bool bfs(){
	for(int i=1;i<=2*n;i++)dis[i]=0,rad[i]=head[i];
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
	return res;
}
bool vis[maxn];
void dfs1(int u){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]&&e[i].val>0)dfs1(v);
	}
}
vector<int> st;

int T;
signed main(){
	
	n=read();m=read();s=read();t=read()+n;
	for(int i=1;i<=n;i++)add(i,i+n,read());
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u+n,v,inf);add(v+n,u,inf);
	}
	while(bfs())ans+=dfs(s,inf);
	dfs1(s);
	for(int i=2;i<=tot;i+=2){
		if(vis[e[i^1].to]&&!vis[e[i].to])st.push_back(e[i^1].to);
	}
	sort(st.begin(),st.end());
	for(int i:st)printf("%lld ",i);
}

