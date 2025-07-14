#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=8010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,p,m;
int a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
int scc[maxn],scct;
int mn[maxn],num[maxn];
bool vis[maxn];
void tar(int u){
	dfn[u]=lw[u]=++idx;
	vis[u]=1;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(vis[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		++scct;
		scc[st[tp]]=scct;
		vis[st[tp]]=0;
		mn[scct]=a[st[tp]];
		num[scct]=st[tp];
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			vis[st[tp]]=0;
			mn[scct]=min(mn[scct],a[st[tp]]);
			num[scct]=min(num[scct],st[tp]);
		}
	}
}
int d[maxn];
int ans;
vector<int> g[maxn];
bool bk[maxn],fl;
queue<int> q;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();p=read();
	for(int i=1;i<=n;i++)a[i]=inf;
	for(int i=1;i<=p;i++)a[read()]=read();
	m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(scc[u]!=scc[v]){
				g[scc[u]].push_back(scc[v]);
				d[scc[v]]++;
			}
		}
	}
	for(int i=1;i<=scct;i++){
		if(!d[i]){
			if(mn[i]==inf)fl=1;
			else ans+=mn[i];
			q.push(i);
		}
		if(mn[i]!=inf)bk[i]=1;
	}
	if(fl){
		printf("NO\n");
		ans=n;
		while(!q.empty()){
			int u=q.front();q.pop();
			if(!bk[u])ans=min(ans,num[u]);
			for(int v:g[u]){
				d[v]--;bk[v]|=bk[u];
				if(!d[v]&&!bk[v])q.push(v);
			}
		}
		printf("%lld\n",ans);
	}
	else printf("YES\n%lld\n",ans);
}
