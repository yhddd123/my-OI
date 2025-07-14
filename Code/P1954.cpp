#include<bits/stdc++.h>
using namespace std;
const int maxn=2010;
const int maxm=10010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int head[maxn],tot,head1[maxn];
struct nd{
	int nxt,to;
}e[maxm<<1];
void add(int u,int v){
	e[++tot]={head[u],v};head[u]=tot;
	e[++tot]={head1[v],u};head1[v]=tot;
}
bool vis[maxn];
int t[maxn][maxn],cnt[maxn];
void dfs(int u){
	if(vis[u])return ;vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		dfs(e[i].to);
		a[u]=min(a[u],a[e[i].to]-1);
	}
	t[a[u]][++cnt[a[u]]]=u;
}
void dfs1(int u){
	if(vis[u])return ;vis[u]=1;
	for(int i=head1[u];i;i=e[i].nxt)dfs1(e[i].to);
}
clock_t st,ed;
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	while(m--){
		int u=read(),v=read();
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=cnt[i];j++)printf("%d ",t[i][j]);
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		dfs1(i);
		int num=n;
		for(int j=n;j>=1;j--){
			if(num>j)break;
			for(int k=1;k<=cnt[j];k++)if(!vis[t[j][k]])--num;
		}
		printf("%d ",num);
	}
}
