// Problem: CF1336F Journey
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1336F
// Memory Limit: 1000 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-12-10 18:23:44
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=150010;
const int inf=1e9;
bool mbe;

int n,m,k,ans;
pii a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void adde(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],son[maxn],fa[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0;dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
int st[18][maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;
	st[0][dfn[u]]=fa[u];
	if(!son[u])return ;
	dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs(v,v);
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
int kth(int u,int k){
	while(dep[u]-dep[fa[tp[u]]]<=k){
		k-=dep[u]-dep[fa[tp[u]]];
		u=fa[tp[u]];
	}
	return rnk[dfn[u]-k];
}
int get(int u,int v,int k){
	int l=lca(u,v);
	if(dep[u]-dep[l]>=k)return kth(u,k);
	else return kth(v,dep[u]+dep[v]-2*dep[l]-k);
}
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
int que(int l,int r){return l>r?0:que(r)-que(l-1);}
vector<int> add[maxn],del[maxn];
bool op[maxn][2];
void upd(int u,int x,int id,int w){
	int y=a[id].fi^a[id].se^x;
	if(w==1){
		if(in(u,y))return ;
		if(!op[id][y==a[id].se])op[id][y==a[id].se]=1,upd(dfn[y],1);
	}
	else{
		if(op[id][y==a[id].se])op[id][y==a[id].se]=0,upd(dfn[y],-1);
	}
}
int que(int u,int x,int id){
	int y=a[id].fi^a[id].se^x;if(dis(u,y)<k)return 0;
	int a=get(u,y,k-1),b=get(a,y,1);
	// cout<<u<<" "<<x<<" "<<y<<" "<<a<<" "<<b<<"\n";
	int res=0;
	if(fa[a]==b){
		res=que(1,dfn[a]-1)+que(dfn[a]+siz[a],n);
		int l=lca(x,y);
		if(dfn[x]<dfn[y]){
			int p=kth(y,dep[y]-dep[l]-1);
			res-=que(dfn[p],dfn[p]+siz[p]-1);
		}
	}
	else{
		if(dfn[x]<dfn[y]){}
		else res=que(dfn[b],dfn[b]+siz[b]-1);
	}
	return res;
}
void dfs1(int u,int op){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs1(v,0);
	}
	if(son[u])dfs1(son[u],1);
	// cout<<u<<" "<<son[u]<<" "<<que(n)<<"\n";
	for(int id:del[u])upd(u,a[id].fi,id,-1),upd(u,a[id].se,id,-1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		for(int j=dfn[v];j<dfn[v]+siz[v];j++){
			int vv=rnk[j];
			for(int k:add[vv])ans+=que(u,vv,k);
		}
		for(int j=dfn[v];j<dfn[v]+siz[v];j++){
			int vv=rnk[j];
			for(int k:add[vv])upd(u,vv,k,1);
		}
	}
	for(int k:add[u])ans+=que(u,u,k),upd(u,u,k,1);
	if(!op){
		for(int j=dfn[u];j<dfn[u]+siz[u];j++){
			int vv=rnk[j];
			for(int k:add[vv])upd(u,vv,k,-1);
		}
	}
	// cout<<u<<" "<<ans<<"\n";
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		adde(u,v),adde(v,u);
	}
	for(int i=1;i<=m;i++)a[i]={read(),read()};
	dfs(1),dfs(1,1);
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=m;i++){
		add[a[i].fi].pb(i),add[a[i].se].pb(i),del[lca(a[i].fi,a[i].se)].pb(i);
	}
	dfs1(1,1);
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}