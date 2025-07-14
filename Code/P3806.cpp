#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,fl=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int maxm=10000010;
const int inf=10000000;
int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
}
int p[maxn];
int rt,siz[maxn],w[maxn],sum;
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
int val[maxm],ans[maxn];
int st[maxn],tp,res[maxn];
int rem[maxn],cnt,dis[maxn];
void getdis(int u,int fa){
	rem[++cnt]=dis[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa&&!vis[v]){
			dis[v]=dis[u]+e[i].w;
			if(dis[v]>inf)continue;
			getdis(v,u);
		}
	}
}
void calc(int u){
	tp=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			cnt=0;dis[v]=e[i].w;
			getdis(v,u);
			for(int j=1;j<=cnt;j++){
				for(int k=1;k<=m;k++){
					if(p[k]==rem[j])ans[k]=1;
					else if(p[k]>rem[j])ans[k]|=val[p[k]-rem[j]];
				}
			}
			for(int j=1;j<=cnt;j++){
				st[++tp]=rem[j];
				val[rem[j]]=1;
			}
		}
	}
	while(tp){
		val[st[tp]]=0;
		tp--;
	}
}
void sovle(int u){
	vis[u]=1;calc(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			sum=siz[v];rt=0;w[rt]=n;
			getrt(v,v);sovle(rt);
		}
	}
}
signed main(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=m;i++)p[i]=read();
	sum=n;w[rt]=n;getrt(1,1);
	sovle(rt);
	for(int i=1;i<=m;i++){
		if(ans[i])printf("AYE\n");
		else printf("NAY\n");
	}
}
