#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
int t[maxn],pos[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,fl;
}e[maxn<<1];
void add(int u,int v,int fl=0){
	e[++tot]={head[u],v,fl};head[u]=tot;
}
int in[maxn],out[maxn];
queue<int> qq;
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)head[i]=pos[i]=in[i]=out[i]=0;
	priority_queue<pii> q;
	for(int i=1;i<=n;i++)t[i]=a[i]=read(),pos[a[i]]=i;
	for(int i=1;i<=n;i++)if(!a[i])t[i]=inf;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u,1),in[v]++,out[u]++;
	}
	for(int i=1;i<=n;i++)if(!out[i])qq.push(i);
	while(!qq.empty()){
		int u=qq.front();qq.pop();
		for(int i=head[u];i;i=e[i].nxt)if(e[i].fl){
			int v=e[i].to;
			t[v]=min(t[v],t[u]-1);
			out[v]--;if(!out[v])qq.push(v);
		}
	}
	for(int i=1;i<=n;i++)if(t[i]<a[i]){puts("-1");return ;}
	// for(int i=1;i<=n;i++)cout<<t[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)if(!in[i]&&!a[i])q.push({-t[i],i});
	for(int tim=1;tim<=n;tim++){
		// cout<<tim<<" "<<q.size()<<"\n";
		if(pos[tim]){
			if(in[pos[tim]]){puts("-1");return ;}
			else{
				int u=pos[tim];
				for(int i=head[u];i;i=e[i].nxt)if(!e[i].fl){
					int v=e[i].to;
					in[v]--;
					if(!in[v]&&!a[v])q.push({-t[v],v});
				}
			}
		}
		else{
			if(!q.size()){puts("-1");return ;}
			int u=q.top().se;a[u]=tim;q.pop();
			for(int i=head[u];i;i=e[i].nxt)if(!e[i].fl){
				int v=e[i].to;
				in[v]--;
				if(!in[v]&&!a[v])q.push({-t[v],v});
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);puts("");
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("permutation.in","r",stdin);
	// freopen("permutation.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
