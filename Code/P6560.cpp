#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=100010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,p;
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn*5];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int d[maxn],a[maxn],deg[maxn];
queue<int> q;
void work(){
	n=read();m=read();p=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(v,u);deg[u]++;
	}
	while(p--){
		int u=read(),v=read();
		mems(a,0);
		for(int i=1;i<=n;i++)d[i]=deg[i];
		for(int i=1;i<=n;i++)if(i==v||!d[i])q.push(i),a[i]=-1;
		while(!q.empty()){
			int u=q.front();q.pop();
//			cout<<u<<" "<<a[u]<<"\n";
			if(a[u]==1){
				for(int i=head[u];i;i=e[i].nxt){
					int v=e[i].to;
					d[v]--;if(!d[v])a[v]=-1,q.push(v);
				}
			}
			else{
				for(int i=head[u];i;i=e[i].nxt){
					int v=e[i].to;
					if(!a[v]){
						a[v]=1;
						q.push(v);
					}
				}
			}
		}
		printf("%lld\n",a[u]);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
