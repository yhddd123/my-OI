#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,p;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v,inf};
	head[u]=tot;
}
int g[maxn],ans[maxn];
int l,r,mid,res;
int vis[maxn];
queue<int> q;
bool check(int x){
	memset(vis,false,sizeof(vis));
	vis[1]=1;q.push(1);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!vis[v]&&e[i].w>=x){
				vis[v]=1;
				q.push(v);
			}
		}
	}
	return vis[n];
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();p=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
	}
	for(int i=1;i<=p;i++){
		g[i]=read();
		if(e[g[i]].w==inf)e[g[i]].w=i;
	}
	l=1;r=p+1;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			res=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	cout<<res<<"\n";
	for(int i=1;i<=p;i++){
		if(e[g[i]].w==i&&g[i]<res)ans[i]=1;
	}
	for(int i=1;i<=p;i++)printf("%lld\n",ans[i]);
}
