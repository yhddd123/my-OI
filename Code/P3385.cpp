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
	
	T=read();
	while(T--){
		memset(head,0,sizeof(head));tot=0;
		memset(vis,0,sizeof(vis));
		memset(tim,0,sizeof(tim));
		while(!q.empty())q.pop();
		bool fl=0;
		n=read();m=read();
		for(int i=1;i<=m;i++){
			int u=read(),v=read(),w=read();
			add(u,v,w);
			if(w>=0)add(v,u,w);
		}
		memset(dis,0x3f,sizeof(dis));
		dis[1]=0;vis[1]=1;
		q.push(1);
		while(!q.empty()){
			int u=q.front();q.pop();vis[u]=0;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(dis[v]>dis[u]+e[i].w){
					dis[v]=dis[u]+e[i].w;
					if(!vis[v]){
						if(++tim[v]>=n){
							printf("YES\n");
							fl=1;
							break;
						}
						q.push(v);vis[v]=1;
					}
				}
			}
			if(fl)break;
		}
		if(!fl)printf("NO\n");
	}
}
