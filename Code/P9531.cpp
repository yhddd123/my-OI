// Problem: P9531 [JOISC2022] 复兴计划
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9531
// Memory Limit: 1 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2024-07-19 09:32:28
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q;
struct edge{
	int u,v,w;
}g[maxn];
int l[maxn],r[maxn];
set<int> e[maxn];
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int st[maxn],tp;
void dfs(int u,int fa,int ed){
	st[++tp]=u;if(st[tp]==ed)return ;
	for(int v:e[u]){
		if(v==fa)continue;
		dfs(v,u,ed);
		if(st[tp]==ed)return ;
	}
	tp--;
}
map<pii,int> mp;
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<7],tag[maxn<<7],lc[maxn<<7],rc[maxn<<7],idx,rt;
void updata(int &nd,int l,int r,int ql,int qr,int w){
	if(!nd)nd=++idx;
	tree[nd]+=(min(r,qr)-max(l,ql)+1)*w;
	if(l>=ql&&r<=qr){tag[nd]+=w;return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int query(int nd,int l,int r,int ql,int qr,int w){
	if(!nd)return (min(r,qr)-max(l,ql)+1)*w;
	if(l>=ql&&r<=qr)return tree[nd]+(r-l+1)*w;
	w+=tag[nd];
	int res=0;
	if(ql<=mid)res+=query(ls,l,mid,ql,qr,w);
	if(qr>mid)res+=query(rs,mid+1,r,ql,qr,w);
	return res;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)g[i]={read(),read(),read()};
	sort(g+1,g+m+1,[&](edge u,edge v){return u.w<v.w;});
	for(int i=1;i<=n;i++)f[i]=i;
	int val=0;
	for(int i=m;i;i--){
		if(fd(g[i].u)!=fd(g[i].v)){
			f[fd(g[i].u)]=fd(g[i].v);
			e[g[i].u].insert(g[i].v),e[g[i].v].insert(g[i].u);
			mp[{g[i].u,g[i].v}]=mp[{g[i].v,g[i].u}]=i;
		}
		else{
			tp=0;dfs(g[i].u,0,g[i].v);
			int id=0;
			for(int j=1;j<tp;j++){
				id=max(id,mp[{st[j],st[j+1]}]);
			}
			e[g[id].u].erase(g[id].v),e[g[id].v].erase(g[id].u);
			if((g[id].w+g[i].w)&1)r[i]=(g[id].w+g[i].w)/2,l[id]=r[i]+1;
			else l[id]=r[i]=(g[id].w+g[i].w)/2;
			val-=g[id].w;
			// cout<<i<<" "<<id<<" "<<l[id]<<" "<<r[i]<<"\n";
			e[g[i].u].insert(g[i].v),e[g[i].v].insert(g[i].u);
			mp[{g[i].u,g[i].v}]=mp[{g[i].v,g[i].u}]=i;
		}
		val+=g[i].w;
	}
	// cout<<val<<"\n";
	for(int i=1;i<=m;i++)if(!r[i])r[i]=inf;
	int sum=0;
	for(int i=1;i<=m;i++){
		updata(rt,1,inf,l[i]+1,min(g[i].w,r[i]),-1);
		// cout<<val+query(rt,1,inf,1,17,0)<<"\n";
		updata(rt,1,inf,max(g[i].w,l[i])+1,r[i],1);
		// cout<<val+query(rt,1,inf,1,17,0)<<" "<<tree[rt]<<"\n";
		// cout<<g[i].u<<" "<<g[i].v<<" "<<g[i].w<<" "<<l[i]<<" "<<r[i]<<"\n";
	}
	q=read();
	while(q--){
		int x=read();
		printf("%lld\n",val+query(rt,1,inf,1,x,0));
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