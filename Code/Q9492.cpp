#include<bits/stdc++.h>
#define ull unsigned long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
inline ull read(){
	ull x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+(ch-48);ch=getchar();}
	return x;
}
bool Mbe;

int n,m;ull a[maxn];
vector<pii> pos;
struct tree{
	int head[maxn],tot;
	struct nd{
		int nxt,to;
	}e[maxn<<1];
	void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
	int fa[maxn],siz[maxn],son[maxn],dep[maxn];
	void dfs(int u){
		siz[u]=1,dep[u]=dep[fa[u]]+1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==fa[u])continue;
			fa[v]=u,dfs(v);siz[u]+=siz[v];
			if(siz[v]>=siz[son[u]])son[u]=v;
		}
	}
	int dfn[maxn],rnk[maxn],idx,tp[maxn];
	void dfs(int u,int lst){
		rnk[dfn[u]=++idx]=u,tp[u]=lst;
		if(!son[u])return ;dfs(son[u],lst);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==fa[u]||v==son[u])continue;
			dfs(v,v);
		}
	}
	void lca(int u,int v){
		while(tp[u]!=tp[v]){
			if(dep[tp[u]]<dep[tp[v]])swap(u,v);
			pos.pb({dfn[tp[u]],dfn[u]});u=fa[tp[u]];
		}
		if(dep[u]<dep[v])swap(u,v);
		pos.pb({dfn[v],dfn[u]});
	}
}t1,t2;
int pl[maxn],pr[maxn],id[maxn],B=450,num;
int to[maxn],fr[maxn];
ull sum[460][460],cnt[460],tag[460],val[maxn];
void updata(int l,int r,ull w){
	// for(int i=l;i<=r;i++)cnt[id[to[i]]]+=w,val[i]+=w;
	// return ;
	if(id[l]==id[r]){
		for(int i=l;i<=r;i++)cnt[id[to[i]]]+=w,val[i]+=w;
	}
	else{
		for(int i=l;i<=pr[id[l]];i++)cnt[id[to[i]]]+=w,val[i]+=w;
		for(int i=pl[id[r]];i<=r;i++)cnt[id[to[i]]]+=w,val[i]+=w;
		l=id[l]+1,r=id[r]-1;
		if(l<=r){
			for(int i=1;i<=num;i++)cnt[i]+=(sum[r][i]-sum[l-1][i])*w;
			for(int i=l;i<=r;i++)tag[i]+=w;
		}
	}
}
ull query(int l,int r){
	ull ans=0;
	// for(int i=l;i<=r;i++)ans+=val[fr[i]]+tag[id[fr[i]]];
	// return ans;
	if(id[l]==id[r]){
		for(int i=l;i<=r;i++)ans+=val[fr[i]]+tag[id[fr[i]]];
	}
	else{
		for(int i=l;i<=pr[id[l]];i++)ans+=val[fr[i]]+tag[id[fr[i]]];
		for(int i=pl[id[r]];i<=r;i++)ans+=val[fr[i]]+tag[id[fr[i]]];
		l=id[l]+1,r=id[r]-1;
		if(l<=r){
			for(int i=l;i<=r;i++)ans+=cnt[i];
		}
	}
	return ans;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		t1.add(u,v),t1.add(v,u);
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		t2.add(u,v),t2.add(v,u);
	}
	t1.dfs(1),t1.dfs(1,1),t2.dfs(1),t2.dfs(1,1);
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n);pl[++num]=l,pr[num]=r;
		for(int j=l;j<=r;j++)id[j]=num;
	}
	for(int i=1;i<=n;i++)to[t1.dfn[i]]=t2.dfn[i];
	for(int i=1;i<=n;i++)fr[to[i]]=i;
	for(int i=1;i<=n;i++)sum[id[i]][id[to[i]]]++;
	for(int i=1;i<=num;i++){
		for(int j=1;j<=num;j++)sum[i][j]+=sum[i-1][j];
	}
	for(int i=1;i<=n;i++)updata(t1.dfn[i],t1.dfn[i],a[i]);
	while(m--){
		int u=read(),v=read();ull k=read();
		pos.clear();t1.lca(u,v);
		for(auto[l,r]:pos)updata(l,r,k);
		pos.clear();t2.lca(u,v);
		ull ans=0;
		for(auto[l,r]:pos)ans+=query(l,r);
		printf("%llu\n",ans);
	}
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
	
	T=1;
	while(T--)work();
}
