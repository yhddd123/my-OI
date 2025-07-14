#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=2000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,s,t;
int head[maxn],tot;
struct nd{
	int nxt,fr,to,w;
}e[maxn*3];
void add(int u,int v,int w){
	e[++tot]={head[u],u,v,w};head[u]=tot;
}
int id(int u,int v){
	return (u-1)*(m-1)+v;
}
struct node{
	int id,dis;
	bool operator <(const node&tmp)const{return dis>tmp.dis;}
};
priority_queue<node> q;
int dis[maxn];
bool vis[maxn];
void work(){
	n=read();m=read();s=2*(n-1)*(m-1)+1,t=2*(n-1)*(m-1)+2;
	for(int j=1;j<m;j++){
		int w=read();
		add(id(1,j),t,w);
	}
	for(int i=2;i<n;i++){
		for(int j=1;j<m;j++){
			int w=read();
			add(id(2*i-2,j),id(2*i-1,j),w);
			add(id(2*i-1,j),id(2*i-2,j),w);
		}
	}
	for(int j=1;j<m;j++){
		int w=read();
		add(s,id(2*n-2,j),w);
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			int w=read();
			if(j==1)add(s,id(2*i,j),w);
			else if(j==m)add(id(2*i-1,j-1),t,w);
			else{
				add(id(2*i-1,j-1),id(2*i,j),w);
				add(id(2*i,j),id(2*i-1,j-1),w);
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			int w=read();
			add(id(2*i-1,j),id(2*i,j),w);
			add(id(2*i,j),id(2*i-1,j),w);
		}
	}
//	for(int i=1;i<=tot;i++)cout<<e[i].fr<<" "<<e[i].to<<" "<<e[i].w<<"\n";
	mems(dis,0x3f);dis[s]=0;q.push({s,0});
	while(!q.empty()){
		int u=q.top().id;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push({v,dis[v]});
			}
		}
	}
	printf("%lld\n",dis[t]);
}

// \
444

bool Med;
int T;
signed main(){
	freopen("P4001_5.in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
