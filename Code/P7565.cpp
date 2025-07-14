#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
inline int max(int a,int b){
	if(a>=b)return a;
	return b;
}
int siz[maxn],w[maxn],rt,sum;
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
int val[maxn],ans[maxn],rem[maxn],cnt;
void getdis(int u,int fa,int d){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa&&!vis[v]){
			getdis(v,u,d+1);
			siz[u]+=siz[v];
		}
	}
	rem[siz[u]]=max(rem[siz[u]],d);
}
void calc(int u){
	cnt=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			getdis(v,u,1);
			for(int j=siz[v];j>=1;j--){
				rem[j]=max(rem[j],rem[j+1]);
				ans[j*2]=max(ans[j*2],rem[j]+val[j]);
			}
			for(int j=1;j<=siz[v];j++)val[j]=max(val[j],rem[j]),rem[j]=0;
			cnt=max(cnt,siz[v]);
		}
	}
	for(int i=1;i<=cnt;i++)val[i]=0;
}
void sovle(int u){
	vis[u]=1;calc(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			sum=siz[v];rt=0;w[rt]=n;
			getrt(v,u);sovle(rt);
		}
	}
}

signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	sum=n;rt=0;w[rt]=n;getrt(1,1);
	sovle(rt);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]+1);
}