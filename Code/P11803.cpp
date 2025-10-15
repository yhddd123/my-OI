// Problem: P11803 【MX-X9-T7】『GROI-R3』此花绽放之时
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11803
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-10-14 16:09:29
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1,dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],tim,tp[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++tim]=u;tp[u]=lst;
	if(!son[u])return ;
	dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs(v,v);
	}
}
#define lb(x) (x&(-x))
int tr[maxn];
void upd(int x,int w){
	while(x<=n)tr[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tr[x],x-=lb(x);
	return res;
}
void upd(int l,int r,int w){upd(l,w),upd(r+1,-w);}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int rt[maxn];
int tree[maxn<<7],lc[maxn<<7],rc[maxn<<7],idx;
void updata(int &nd,int l,int r,int ql,int qr,int w){
	if(!nd)nd=++idx;
	if(l>=ql&&r<=qr){tree[nd]+=w;return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	if(p<=mid)return query(ls,l,mid,p)+tree[nd];
	else return query(rs,mid+1,r,p)+tree[nd];
}
map<int,int> mp[maxn];
struct node{
	int l,r,c;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
struct odt{
	set<node> s;
	void split(int p){
		auto it=s.lower_bound({p,p,0});
		if((*it).r>p){
			auto[l,r,c]=*it;
			s.erase(it);
			s.insert({l,p,c}),s.insert({p+1,r,c});
		}
	}
	void ins(int l,int r,int c){
		split(l-1),split(r);
		auto it=s.lower_bound({l,l,0});
		while((*it).r<=r)it=s.erase(it);
		while((*it).c==c)r=(*it).r,it=s.erase(it);
		it--;while((*it).c==c)l=(*it).l,it=s.erase(it),it--;
		s.insert({l,r,c});
	}
	node que(int p){
		auto it=s.lower_bound({p,p,0});
		return (*it);
	}
}col[maxn];
void mdf(int u){
	if(!fa[u])return ;
	auto[l,r,c]=col[u].que(dfn[u]);
	int val=query(rt[c],1,n,dfn[fa[u]])-mp[u][c];mp[u][c]+=val;
	updata(rt[c],1,n,l,r,val);upd(l,r,val);
}
int st[maxn],top;
void down(int u){
	top=0;while(u)st[++top]=tp[u],u=fa[tp[u]];
	for(int i=top;i;i--)mdf(st[i]);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++)fa[i]=read(),add(fa[i],i);
	dfs(1),dfs(1,1);
	for(int i=1;i<=n;i++)if(i==tp[i])col[tp[i]].s.insert({0,n+1,0});
	for(int i=1;i<=n;i++)col[tp[i]].ins(dfn[i],dfn[i],a[i]);
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),v=read(),c=read();
			down(u),down(v);
			while(tp[u]!=tp[v]){
				if(dep[tp[u]]<dep[tp[v]])swap(u,v);
				col[tp[u]].ins(dfn[tp[u]],dfn[u],c);
				mp[tp[u]][c]=query(rt[c],1,n,dfn[fa[tp[u]]]);
				u=fa[tp[u]];
			}
			if(dep[u]<dep[v])swap(u,v);
			col[tp[u]].ins(dfn[v],dfn[u],c);
			if(v==tp[u])mp[v][c]=query(rt[c],1,n,dfn[fa[v]]);
		}
		if(op==2){
			int u=read(),w=read();
			// down(u);
			int lst=u,cc=col[tp[u]].que(dfn[u]).c;
			while(u){
				auto[l,r,c]=col[tp[u]].que(dfn[u]);
				// cout<<u<<" "<<l<<" "<<r<<" "<<c<<"\n";
				if(c!=cc)break;
				if(l!=dfn[tp[u]]){
					lst=rnk[l];
					break;
				}
				lst=tp[u],u=fa[tp[u]];
			}
			u=lst;
			auto[l,r,c]=col[tp[u]].que(dfn[u]);
			// cout<<u<<" "<<l<<" "<<r<<"\n";
			updata(rt[c],1,n,l,r,w);upd(l,r,w);
		}
		if(op==3){
			int u=read();
			down(u);
			// cout<<u<<" "<<dfn[u]<<" "<<que(dfn[u])<<"\n";
			printf("%lld\n",que(dfn[u]));
		}
	}
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