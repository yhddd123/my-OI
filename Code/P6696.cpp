#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<2];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
}
bool vis[maxn],flag;
double k[maxn],b[maxn];
double x,ans[maxn];
int st[maxn],tp,c[maxn];
void dfs(int u,int fa){
	vis[u]=1;st[++tp]=u;
	c[tp]=k[u]*b[u];
	//	cout<<u<<" "<<k[u]<<" "<<b[u]<<"\n";
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			if(!vis[v]){
				k[v]=-k[u];b[v]=-b[u]+e[i].w;
				dfs(v,u);
			}
			else{
				double kk=-k[u],bb=-b[u]+e[i].w;
				if(kk==k[v]&&bb!=b[v]){
					printf("NO\n");
					exit(0);
				}
				if(kk!=k[v]){
					if(!flag)x=1.0*(b[v]-bb)/(kk-k[v]),flag=1;
					else if(x!=1.0*(b[v]-bb)/(kk-k[v])){
						printf("NO\n");
						exit(0);
					}
				}
			}
		}
	}
}
void fill(int u,int fa,double val){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!ans[v]){
			ans[v]=-val+e[i].w;
			fill(v,u,-val+e[i].w);
		}
	}
}


int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			k[i]=1;x=0;tp=0;flag=0;
			dfs(i,0);
			if(!flag){
				sort(c+1,c+tp+1);
				x=-c[(tp+1)/2];
			}
			ans[i]=x;fill(i,0,x);
		}
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)printf("%.8lf ",ans[i]);
}
