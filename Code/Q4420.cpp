#include<bits/stdc++.h>
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=50010;
const int maxm=100010;
const int inf=1e9;
bool mbe;

int n,m,q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxm];
void adde(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
bitset<maxn> f[maxn],g[maxm/4],pos;
vector<int> add[maxm],del[maxm],que[maxn];
int ans[maxn];
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		adde(u,v);
	}
	for(int i=1;i<=m;i++)add[i].clear(),del[i].clear();
	for(int i=1;i<=n;i++)que[i].clear();
	for(int i=1;i<=n;i++)f[i].reset();
	for(int i=1;i<=m/4;i++)g[i].reset();
	for(int i=1;i<=q;i++){
		int u=read(),v=read(),l=read(),r=read();
		add[l].pb(i),del[r+1].pb(i);
		que[u].pb(i);
		f[v].set(i);
	}
	for(int i=4;i<=m;i+=4){
		g[i/4]=g[i/4-1];
		for(int j=i-3;j<=i;j++){
			for(int id:add[j])g[i/4].set(id);
			for(int id:del[j])g[i/4].reset(id);
		}
	}
	for(int u=n;u;u--){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			pos=g[i/4];
			for(int j=i/4*4+1;j<=i;j++){
				for(int id:add[j])pos.set(id);
				for(int id:del[j])pos.reset(id);
			}
			f[u]|=f[v]&pos;
		}
		for(int id:que[u])ans[id]=f[u][id];
	}
	for(int i=1;i<=q;i++)puts(ans[i]?"YES":"NO");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}