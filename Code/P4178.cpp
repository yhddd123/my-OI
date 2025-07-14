#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,fl=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}
const int maxn=40010;
int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
}
int sum,rt,siz[maxn],w[maxn];
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1;w[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa&&!vis[v]){
			getrt(v,u);
			siz[u]+=siz[v];
			w[u]=max(w[u],siz[v]);
		}
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<w[rt])rt=u;
}
int val[maxn];
int rem[maxn],cnt,dis[maxn];
void getdis(int u,int fa){
	rem[++cnt]=dis[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa&&!vis[v]){
			dis[v]=dis[u]+e[i].w;
			getdis(v,u);
		}
	}
}
int ans;
int calc(int u,int w){
	int res=0;cnt=0;
	dis[u]=w;getdis(u,u);
	sort(rem+1,rem+cnt+1);
	int l=1,r=cnt;
	while(l<=r){
		if(rem[l]+rem[r]<=m){
			res+=r-l;
			l++;
		}
		else r--;
	}
	return res;
}
void sovle(int u){
	vis[u]=1;ans+=calc(u,0);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			ans-=calc(v,e[i].w);
			sum=siz[v];rt=0;w[rt]=n;getrt(v,u);
			sovle(rt);
		}
	}
}
signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	m=read();
	sum=n;w[rt]=n;getrt(1,1);
	sovle(rt);
	printf("%lld\n",ans);
}
