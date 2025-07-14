#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
vector<int> e[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int in[maxn],out[maxn],idx;
void build(int nd,int l,int r){
	in[nd]=++idx;out[nd]=++idx;
	if(l==r){
		e[in[nd]].push_back(l),e[l].push_back(out[nd]);
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	e[in[nd]].push_back(in[ls]),e[in[nd]].push_back(in[rs]);
	e[out[ls]].push_back(out[nd]),e[out[rs]].push_back(out[nd]);
}
void updin(int nd,int l,int r,int ql,int qr,int id){
	if(l>=ql&&r<=qr)return e[id].push_back(in[nd]);
	if(ql<=mid)updin(ls,l,mid,ql,qr,id);
	if(qr>mid)updin(rs,mid+1,r,ql,qr,id);
}
void updout(int nd,int l,int r,int ql,int qr,int id){
	if(l>=ql&&r<=qr)return e[out[nd]].push_back(id);
	if(ql<=mid)updout(ls,l,mid,ql,qr,id);
	if(qr>mid)updout(rs,mid+1,r,ql,qr,id);
}
int dfn[maxn],lw[maxn],cnt;
int scc[maxn],scct;
int st[maxn],tp;
vector<int> id[maxn];
void tar(int u){
	lw[u]=dfn[u]=++cnt;st[++tp]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scc[st[tp]]=++scct;
		if(st[tp]<=3*n)id[scct].push_back(st[tp]);
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			if(st[tp]<=3*n)id[scct].push_back(st[tp]);
		}
	}
}
vector<int> g[maxn],gg[maxn];int d[maxn];
queue<int> q;
bool ans[maxn],vis[maxn];
map<pii,bool> bk;
void dfs(int u){
	vis[u]=1;
	for(int i:id[u])ans[i]=1;
	for(int v:g[u])if(!vis[v])dfs(v);
}
void dfss(int u){
	vis[u]=1;
	for(int i:id[u])ans[i]=1;
	for(int v:gg[u])if(!vis[v])dfss(v);
}
void work(){
	n=read();m=read();idx=3*n;
	build(1,1,3*n);
	while(m--){
		int a=read(),b=read(),c=read(),d=read();++idx;
		updin(1,1,3*n,c,d,idx),updout(1,1,3*n,a,b,idx);
	}
	for(int i=1;i<=idx;i++)if(!dfn[i])tar(i);
	for(int u=1;u<=idx;u++){
		for(int v:e[u]){
			if(scc[u]!=scc[v]&&!bk[{scc[u],scc[v]}]){
				// cout<<scc[u]<<" "<<scc[v]<<"\n";
				g[scc[u]].push_back(scc[v]),gg[scc[v]].push_back(scc[u]),d[scc[u]]++;
				bk[{scc[u],scc[v]}]=bk[{scc[v],scc[u]}]=1;
			}
		}
	}
	for(int i=1;i<=scct;i++)if(!d[i])q.push(i);
	int ss=0;
	while(!q.empty()){
		int u=q.front();q.pop();ss+=id[u].size();
		// cout<<u<<" "<<ss<<"\n";
		for(int i:id[u])ans[i]=1;
		if(ss>=n)break;
		for(int v:gg[u]){
			if(!d[v])continue;
			d[v]--;if(!d[v])q.push(v);
		}
	}
	while(!q.empty())q.pop();
	if(ss<=2*n){
		puts("TAK");
		for(int i=1;i<=3*n;i++){if(ans[i])printf("F");else printf("R");}printf("\n");
	}
	else{
		for(int i=1;i<=3*n;i++)ans[i]=0;bool fl=0;
		for(int u=1;u<=scct;u++)if(id[u].size()>=n&&id[u].size()<=2*n){
			dfs(u);
			int ss=0;for(int i=1;i<=3*n;i++)ss+=ans[i];
			if(ss<=2*n){
				puts("TAK");
				for(int i=1;i<=3*n;i++){if(ans[i])printf("F");else printf("R");}printf("\n");
			}
			else{
				for(int i=1;i<=3*n;i++)ans[i]=0;
				for(int i=1;i<=scct;i++)vis[i]=0;
				dfss(u);
				int ss=0;for(int i=1;i<=3*n;i++)ss+=ans[i];
				if(ss<=2*n){
					puts("TAK");
					for(int i=1;i<=3*n;i++){if(ans[i])printf("R");else printf("F");}printf("\n");
				}
				else puts("NIE");
			}
			fl=1;break;
		}
		if(!fl)puts("NIE");
	}
	for(int i=1;i<=idx;i++)e[i].clear(),dfn[i]=lw[i]=scc[i]=0;
	for(int i=1;i<=scct;i++)g[i].clear(),gg[i].clear(),id[i].clear(),vis[i]=d[i]=0;
	bk.clear();idx=scct=cnt=tp=0;
	for(int i=1;i<=3*n;i++)ans[i]=0;
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
