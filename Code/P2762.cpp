#include<bits/stdc++.h>
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=5010;
const int inf=1e9;
bool Mbe;

int n,m,sum;
struct nd{
	int nxt,to,val;
}e[maxn];
int head[maxn],tot=1;
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t;
int rad[maxn],dis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=rad[i]=0;
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
char tools[10000];
void work(){
	scanf("%d%d",&n,&m);s=n+m+1,t=n+m+2;
	for(int i=1;i<=n;i++){
		int w;scanf("%d",&w);
		add(s,i,w);sum+=w;
		memset(tools,0,sizeof tools);
		cin.getline(tools,10000);
		int ulen=0,tool;
		while (sscanf(tools+ulen,"%d",&tool)==1)//之前已经用scanf读完了赞助商同意支付该实验的费用
		{
//tool是该实验所需仪器的其中一个      
//			这一行，你可以将读进来的编号进行储存、处理，如连边。
			add(i,n+tool,inf);
			if (tool==0) 
				ulen++;
			else {
				while (tool) {
					tool/=10;
					ulen++;
				}
			}
			ulen++;
		}
	}
	for(int i=1;i<=m;i++){
		int x;scanf("%d",&x);
		add(i+n,t,x);
	}
//	for(int i=2;i<=tot;i+=2)cout<<e[i^1].to<<" "<<e[i].to<<" "<<e[i].val<<"\n";
	while(bfs())sum-=dfs(s,inf);
	for(int i=1;i<=n;i++)if(dis[i])printf("%d ",i);
	printf("\n");
	for(int i=1;i<=m;i++)if(dis[i+n])printf("%d ",i);
	printf("\n");
	printf("%d\n",sum);
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
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
