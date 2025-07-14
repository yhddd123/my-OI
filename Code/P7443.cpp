#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=3e18;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,t,a,b,ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int sg[maxn],w[maxn],d[maxn];
bool vis[maxn];
priority_queue<pair<int,int> > q;
void dfs(int u){
	sg[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;dfs(v);
		if(!sg[v])sg[u]=1,d[u]++;
	}
	if(!sg[u])q.push({-w[u],u}),vis[u]=0;
}
void dfs2(int u){
	if(t&&d[u]>1)return ;
	if(!t){
		vis[u]=1;
		while(!q.empty()&&vis[q.top().second])q.pop();
		if(q.size())ans=min(ans,-q.top().first*b+a*w[u]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if((t&&!sg[v])||!t){
			t^=1;
			dfs2(v);
			t^=1;
		}
	}
	if(!t){
		vis[u]=0;
		q.push({-w[u],u});
	}
}
void sovle(){
	while(!q.empty())q.pop();
	for(int i=1;i<=n;i++)d[i]=0;
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	n=read();t=read();a=read();b=read();ans=inf;
	for(int i=2;i<=n;i++)add(read(),i);
	for(int i=1;i<=n;i++)w[i]=read();
	dfs(1);
	if(t!=sg[1])printf("0\n");
	else{
		dfs2(1);
		if(ans==inf)printf("-1\n");
		else printf("%lld\n",ans);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--)sovle();
}
