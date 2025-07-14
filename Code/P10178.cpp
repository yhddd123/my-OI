// Problem: P10178 陌路寻诗礼
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10178
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=300010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,k;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
struct Dis{
	int id,dis;
	bool operator <(const Dis&tmp)const{return dis>tmp.dis;}
};
priority_queue<Dis> q;
int dis[maxn],pre[maxn];bool vis[maxn];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=1;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v,1);
	}
	for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=0;
	dis[1]=0;q.push({1,0});bool fl=0;
	while(!q.empty()){
		int u=q.top().id;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				pre[v]=i;
				q.push({v,dis[v]});
			}
		}
	}
	// for(int i=1;i<=n;i++)cout<<dis[i]<<" ";cout<<"\n";
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			// cout<<u<<" "<<v<<"\n";
			if(dis[v]==dis[u]+e[i].w&&pre[v]!=i){
				if(k==1){fl=1;break;}
				e[i].w++;
			}
		}
	}
	if(fl)printf("No\n");
	else{
		printf("Yes\n");
		for(int i=2;i<=tot;i++)printf("%lld ",e[i].w);
		printf("\n");
	}
}

int T;
signed main(){
	T=read();
	while(T--)work();
}