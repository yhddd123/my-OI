#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	priority_queue<int> tree[maxn<<2][2];
	int top(int nd){
		while(!tree[nd][1].empty()&&tree[nd][0].top()==tree[nd][1].top())tree[nd][0].pop(),tree[nd][1].pop();
		return tree[nd][0].size()?tree[nd][0].top():-1;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w,int op){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			tree[nd][op].push(w);
			return ;
		}
		if(ql<=mid)updata(ls,l,mid,ql,qr,w,op);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w,op);
	}
	int query(int nd,int l,int r,int p){
		int res=top(nd);
		if(l==r)return res;
		if(p<=mid)return res=max(res,query(ls,l,mid,p));
		else return res=max(res,query(rs,mid+1,r,p));
	}
#undef mid
}
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
int tp[maxn],dfn[maxn],idx,rnk[maxn];
void dfs(int u){
	siz[u]=1;dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u])continue;
		fa[v]=u;dfs(v);
		siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
void dfs1(int u,int lst){
	tp[u]=lst;
	dfn[u]=++idx;rnk[idx]=u;
	if(!son[u])return ;
	dfs1(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs1(v,v);
	}
}
vector<pii> l;
void upd(int u,int v,int w,int op){
	l.clear();
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		l.push_back(make_pair(dfn[tp[u]],dfn[u]));
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	l.push_back(make_pair(dfn[v],dfn[u]));
	sort(l.begin(),l.end());
	int lst=1;
	for(pii i:l){
		sgt::updata(1,1,n,lst,i.first-1,w,op);
		lst=i.second+1;
	}
	sgt::updata(1,1,n,lst,n,w,op);
}
struct ask{
	int u,v,w;
}p[maxn<<1];
void work(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1);dfs1(1,1);
	for(int i=1;i<=m;i++){
		int op=read();
		if(op==0){
			p[i]={read(),read(),read()};
			upd(p[i].u,p[i].v,p[i].w,0);
		}
		if(op==1){
			int u=read();
			upd(p[u].u,p[u].v,p[u].w,1);
		}
		if(op==2){
			int u=read();
			printf("%d\n",sgt::query(1,1,n,dfn[u]));
		}
	}
}

int T;
signed main(){
	T=1;
	while(T--)work();
}
