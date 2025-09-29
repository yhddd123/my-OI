// Problem: P11831 [省选联考 2025] 追忆
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11831
// Memory Limit: 2048 MB
// Time Limit: 9000 ms
// Written by yhm.
// Start codeing:2025-09-29 20:18:22
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=100010;
bool mbe;

int n,m,q,qq,k;
int a[maxn],b[maxn];
bitset<maxn> f[maxn],g[maxn/2],vis,pos;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add_e(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int tim[maxn];
struct node_upd{
	int u,a,b,lt,rt;
}upd[maxn*3];
struct node_que{
	int u,l,r,id;
}que[maxn];
int ans[maxn];
vector<int> add[maxn],del[maxn];
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add_e(u,v);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	qq=k=0;
	for(int i=1;i<=n;i++)tim[i]=0;
	for(int i=1;i<=q;i++){
		int op=read();
		if(op==1){
			int x=read(),y=read();
			if(tim[x]+1<=qq)upd[++k]={x,a[x],b[x],tim[x]+1,qq};
			if(tim[y]+1<=qq)upd[++k]={y,a[y],b[y],tim[y]+1,qq};
			swap(a[x],a[y]);
			tim[x]=qq,tim[y]=qq;
		}
		if(op==2){
			int x=read(),y=read();
			if(tim[x]+1<=qq)upd[++k]={x,a[x],b[x],tim[x]+1,qq};
			if(tim[y]+1<=qq)upd[++k]={y,a[y],b[y],tim[y]+1,qq};
			swap(b[x],b[y]);
			tim[x]=qq,tim[y]=qq;
		}
		if(op==3){
			que[++qq]={read(),read(),read(),i},ans[qq]=0;
		}
	}
	for(int i=1;i<=n;i++)if(tim[i]<qq)upd[++k]={i,a[i],b[i],tim[i]+1,qq};
	sort(upd+1,upd+k+1,[&](node_upd u,node_upd v){return u.b>v.b;});
	for(int i=1;i<=n;i++)f[i].reset();
	for(int i=1;i<=qq;i++)f[que[i].u][i]=1;
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			f[v]|=f[u];
		}
	}
	for(int i=1;i<=n;i++)add[i].clear(),del[i].clear();
	for(int i=1;i<=qq;i++)add[que[i].l].pb(i),del[que[i].r+1].pb(i);
	g[0].reset();
	for(int i=1;i<=n/2;i++){
		g[i]=g[i-1];
		for(int j:add[i])g[i].set(j);
		for(int j:del[i])g[i].reset(j);
	}
	vis.set();
	for(int i=1;i<=k;i++){
		auto[u,a,b,lt,rt]=upd[i];
		if(a>n/2)continue;
		pos=f[u]&g[a]&vis;
		for(int p=pos._Find_next(lt-1);p<=rt;p=pos._Find_next(p)){
			ans[p]=max(ans[p],b);
			vis.reset(p);
		}
	}
	g[0]=g[n/2];
	for(int i=n/2+1;i<=n;i++){
		g[i-n/2]=g[i-n/2-1];
		for(int j:add[i])g[i-n/2].set(j);
		for(int j:del[i])g[i-n/2].reset(j);
	}
	vis.set();
	for(int i=1;i<=k;i++){
		auto[u,a,b,lt,rt]=upd[i];
		if(a<=n/2)continue;
		pos=f[u]&g[a-n/2]&vis;
		for(int p=pos._Find_next(lt-1);p<=rt;p=pos._Find_next(p)){
			ans[p]=max(ans[p],b);
			vis.reset(p);
		}
	}
	for(int i=1;i<=qq;i++)write(ans[i]),puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	read();T=read();
	while(T--)work();
}