#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=150010;
const int inf=1e9;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x;
}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
bool Mbe;

int n,m,k,a,b;
int head[maxn],tot,hh[maxn];
int pre[maxn<<2],nxt[maxn<<2];
struct nd{
	int nxt,to;
}e[maxn<<2];
void add(int u,int v){
	e[++tot]={head[u],v},head[u]=tot;
	nxt[tot]=hh[u],pre[hh[u]]=tot,hh[u]=tot;
}
int q[maxn],h,t;
int dis[maxn];ll ans[maxn];
bool vis[maxn];
void work(){
	n=read();m=read();k=read();a=read();b=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	q[h=t=1]=k;dis[k]=1;
	while(h<=t){
		int u=q[h];h++;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v])dis[v]=dis[u]+1,q[++t]=v;
		}
	}
	for(int i=1;i<=n;i++){
		dis[i]--;
		ans[i]=min(1ll*dis[i]*a,1ll*dis[i]/2*b+1ll*(dis[i]%2)*a);
		// cout<<dis[i]<<" "<<ans[i]<<"\n";
		dis[i]=inf;
	}
	q[h=t=1]=k;dis[k]=0;
	while(h<=t){
		int u=q[h];h++;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			vis[v]=1;
		}
		for(int ii=head[u];ii;ii=e[ii].nxt){
			int v=e[ii].to;
			for(int i=hh[v];i;i=nxt[i]){
				int w=e[i].to;
				if(vis[w]||dis[w]!=inf)continue;
				dis[w]=dis[u]+1,q[++t]=w;
				nxt[pre[i]]=nxt[i],pre[nxt[i]]=pre[i];
				if(i==hh[v])hh[v]=nxt[i];
			}
		}
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			vis[v]=0;
		}
	}
	for(int i=1;i<=n;i++){
		if(dis[i]!=inf)ans[i]=min(ans[i],1ll*dis[i]*b);
	}
	for(int i=1;i<=n;i++)write(ans[i]),puts("");
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("edge.in","r",stdin);
	// freopen("edge.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
