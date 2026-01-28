// Problem: P14653 [集训队互测 2025] 你的互相追逐的头
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14653
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-28 20:20:32
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,m,q;
pii id[maxn];
vector<int> e[maxn];
int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1;son[u]=0;dep[u]=dep[fa[u]]+1;
	for(int v:e[u])if(v!=fa[u]){
		fa[v]=u,dfs(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],idx,rnk[maxn],top[maxn],st[19][maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u,st[0][idx]=fa[u];top[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
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
int kth(int u,int k){
	while(dep[u]-dep[fa[top[u]]]<=k){
		k-=dep[u]-dep[fa[top[u]]];
		u=fa[top[u]];
	}
	return rnk[dfn[u]-k];
}
int go(int u,int v,int k){
	int tp=lca(u,v);
	if(dep[u]-dep[tp]>=k)return kth(u,k);
	return kth(v,dep[u]+dep[v]-2*dep[tp]-k);
}
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
int get(int u,int v,int p){//p->path(u,v)
	if(in(p,u)&&in(p,v))return lca(u,v);
	if((in(p,u)&&in(v,p))||(in(p,v)&&in(u,p)))return p;
	int p1=lca(u,p),p2=lca(v,p);
	if(dep[p1]>dep[p2])swap(p1,p2);
	p1=lca(u,v);
	if(dep[p1]>dep[p2])swap(p1,p2);
	return p2;
}
int a[maxn];
pii stk[maxn];int tp;
int suf[maxn];
vector<pii> ask[maxn];
int ans[maxn];
void work(){
	m=read();q=read();
	for(int i=0;i<m;i++)a[i]=read();
	tuple<int,int,int> diameter={0,a[0],a[0]};
	for(int i=1;i<m;i++){
		auto[d,x,y]=diameter;
		diameter=max({diameter,{dis(a[i],x),a[i],x},{dis(a[i],y),a[i],y}});
	}
	auto[d,p1,p2]=diameter;
	int mid=go(p1,p2,d/2);
	int pp=0;for(int i=1;i<m;i++)if(a[i]==p1)pp=i;
	for(int i=0;i<m;i++)ask[i].clear();
	rotate(a,a+pp,a+m);
	// cout<<d<<" "<<p1<<" "<<p2<<" "<<mid<<"\n";
	for(int i=1;i<=q;i++){
		int p=read()-1,t=2*read();ans[i]=0;
		if(t>=d/2)ans[i]=mid;
		else if(p==pp)ans[i]=go(p1,p2,t);
		else ask[(p+m-pp)%m].pb({t,i});
	}
	stk[tp=1]={p1,mid},suf[1]=(d+1)/2;
	for(int i=m-1;i;i--){
		int p1=a[i],p2=a[(i+1)%m],s=0;
		while(tp){
			auto[u,v]=stk[tp];
			int p=get(u,v,p1);
			int d1=dis(p1,p),d2=s+dis(u,p);s+=dis(u,v);
			// cout<<u<<" "<<v<<" "<<p<<" "<<d1<<" "<<d2<<endl;
			if(d1<=d2){
				int nw=go(p,u,(d2-d1)/2);
				// cout<<nw<<" "<<(d2-d1)/2<<"\n";
				if(nw!=v)stk[tp]={nw,v},suf[tp]=suf[tp-1]+dis(nw,v);
				else tp--;
				if(nw!=u)stk[++tp]={p1,nw},suf[tp]=suf[tp-1]+dis(p1,nw);
				break;
			}
			else tp--;
		}
		// cout<<p1<<" "<<p2<<" a"<<endl;
		// for(int i=tp;i;i--)cout<<stk[i].fi<<" "<<stk[i].se<<"\n";
		fflush(stdout);	
		for(auto[t,id]:ask[i]){
			int p=lower_bound(suf+1,suf+tp+1,suf[tp]-t)-suf;
			auto[u,v]=stk[p];
			ans[id]=go(v,u,suf[tp]-t-suf[p-1]);
		}
	}
	for(int i=1;i<=q;i++){
		printf("%d %d\n",id[ans[i]].fi,id[ans[i]].se);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	n=read();T=read();
	for(int i=1;i<=n;i++)id[i]={i,i};
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		id[n+i]={min(u,v),max(u,v)};
		e[u].pb(n+i),e[n+i].pb(u);
		e[v].pb(n+i),e[n+i].pb(v);
	}
	n+=n-1;
	dfs(1),dfs(1,1);
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	while(T--)work();
}