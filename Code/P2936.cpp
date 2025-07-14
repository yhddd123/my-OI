#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=110;
const int maxm=1410;
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
	int to,nxt,val;
}e[maxm<<2];
int head[maxn],tot=1;
void add(int u,int v,int w){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;
	head[u]=tot;
}

int rad[maxn],dis[maxn];
queue<int> q;
bool bfs(){
	memset(dis,0,sizeof(dis));
	memset(rad,0,sizeof(rad));
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

signed main(){
	n=read();s=1;t=26;
	while(n--){
		int w;
		char u,v;
		cin>>u>>v;w=read();
		add(u-'A'+1,v-'A'+1,w);add(v-'A'+1,u-'A'+1,0);
	}
	while(bfs())ans+=dfs(s,inf);
	printf("%lld\n",ans);
}
