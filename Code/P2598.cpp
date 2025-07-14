#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a,s,t;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
	e[++tot]={head[v],u,0};
	head[v]=tot;
}
queue<int> q;
int rad[maxn],dis[maxn];
int flow;
bool bfs(){
	memset(dis,0,sizeof(dis));
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		rad[u]=head[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w){
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
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(res,e[i].w));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}

signed main(){
	n=read();m=read();s=n*m+1,t=n*m+2;
	for(int i=0;i<n;i++){
		for(int j=1;j<=m;j++){
			a=read();
			if(a==1)add(s,i*m+j,inf);
			if(a==2)add(i*m+j,t,inf);
			if(i!=0)add(i*m+j,(i-1)*m+j,1);
			if(i!=n-1)add(i*m+j,(i+1)*m+j,1);
			if(j!=1)add(i*m+j,i*m+j-1,1);
			if(j!=m)add(i*m+j,i*m+j+1,1);
		}
	}
	while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",flow);
}
