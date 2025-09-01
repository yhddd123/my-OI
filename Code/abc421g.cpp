#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=310;
const int inf=1e9;

int n,m,a[maxn];
int head[maxn],tot=1;
struct nd{
    int nxt,to,w,c;
}e[maxn<<2];
void add(int u,int v,int w,int c){
    // cout<<u<<" "<<v<<" "<<w<<","<<c<<"\n";
    e[++tot]={head[u],v,w,c};head[u]=tot;
    e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int s,t,flow,cost;
queue<int> q;
int dis[maxn],rad[maxn];
bool vis[maxn];
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0,rad[i]=head[i];
	q.push(s);dis[s]=0;vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
    // cout<<u<<" "<<res<<"\n";
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			cost+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=n;i;i--)a[i]=a[i]-a[i-1];
    s=n+2,t=n+3;
    for(int i=1;i<=n;i++){
        if(a[i]>=0)add(s,i,a[i],0);
        else add(i,t,-a[i],0);
    }
    add(s,n+1,inf,0);
    for(int i=1;i<=m;i++){
        int l=read(),r=read();
        add(r+1,l,inf,1);
    }
    while(bfs())flow+=dfs(s,inf);
    // cout<<flow<<"\n";
    int num=0;for(int i=1;i<=n;i++)num+=max(0ll,-a[i]);
    if(num>flow)puts("-1");
    else printf("%lld\n",cost);

}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}