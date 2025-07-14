#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define ls nd<<1
#define rs nd<<1|1
using namespace std;
const int maxn=100010;
const int inf=2e6;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
bool vis[maxn];
int dis[maxn],tim[maxn];
queue<int> q;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(v,u,w);
	}
	for(int i=1;i<=n;i++)add(0,i,0);
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;vis[0]=1;
	q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;++tim[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				if(!vis[v]){
					if(tim[v]>=n){
						printf("NO\n");
						exit(0);
					}
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",dis[i]);
}
