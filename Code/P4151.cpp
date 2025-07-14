#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int head[maxn],tot;
struct edgend{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
bool vis[maxn];
int dis[maxn];
namespace bas{
	const int N=65,bit=61;
	int p[N],cnt;
	bool insert(int x){
		for(int i=bit;i>=0;i--)if(x&(1ll<<i)){
			if(!p[i]){
				++cnt;
				p[i]=x;
				return true;
			}
			x^=p[i];
		}
		return false;
	}
	int quemx(int x){
		for(int i=bit;i>=0;i--)x=max(x,x^p[i]);
		return x;
	}
}
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v])bas::insert(dis[u]^dis[v]^e[i].w);
		else dis[v]=dis[u]^e[i].w,dfs(v);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs(1);
	printf("%lld\n",bas::quemx(dis[n]));
}
