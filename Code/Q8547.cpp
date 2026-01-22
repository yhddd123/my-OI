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
const int maxn=500025;
const int inf=1e9;
bool mbe;

int n,q,k;
vector<int> e[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x)tree[x]+=w,x-=lb(x);
}
int que(int x){
	int res=0;
	while(x<=n)res+=tree[x],x+=lb(x);
	return res;
}
int dfn[maxn],idx,siz[maxn],dep[maxn],fa[maxn];
struct node{
	int l,r,v;
};
bool operator<(node u,node v){return u.r<v.l;}
struct DS{
	vector<int> id;
	set<node> s;
	void clr(){id.clear();s.clear();}
	void init(){
		s.insert({1,(int)id.size(),0});
	}
	void mdf(int u,int w){
		if(!id.size())return ;
		int l=lower_bound(id.begin(),id.end(),dfn[u])-id.begin(),r=lower_bound(id.begin(),id.end(),dfn[u]+siz[u])-id.begin()-1;
		if(l>r)return ;
		// cout<<u<<" "<<l<<" "<<r<<" "<<w<<"\n";
		l++,r++;
		upd(w,r-l+1);
		auto it=s.lower_bound({l,l,0});
		if(it!=s.end()&&(*it).l<l){
			auto[ll,rr,ww]=(*it);s.erase(it);
			if(rr<=r){
				s.insert({ll,l-1,ww});
				upd(ww,-(rr-l+1));
			}
			else{
				s.insert({ll,l-1,ww});
				s.insert({r+1,rr,ww});
				upd(ww,-(r-l+1));
			}
		}
		it=s.lower_bound({l,l,0});
		while(it!=s.end()&&(*it).r<=r){
			auto[ll,rr,ww]=*it;it=s.erase(it);
			upd(ww,-(rr-ll+1));
		}
		if(it!=s.end()&&(*it).l<=r){
			auto[ll,rr,ww]=*it;s.erase(it);
			s.insert({r+1,rr,ww});
			upd(ww,-(r-ll+1));
		}
		s.insert({l,r,w});
	}
}ds[maxn];
void dfs(int u){
	dfn[u]=++idx;siz[u]=1;dep[u]=dep[fa[u]]+1;
	ds[dep[u]].id.pb(dfn[u]);
	for(int v:e[u])if(v!=fa[u])fa[v]=u,dfs(v),siz[u]+=siz[v];
}
int ans[maxn];
vector<pii> ask[maxn];
void work(){
	n=read();k=read();q=read();
	for(int i=1;i<=n;i++)e[i].clear(),ask[i].clear(),ds[i].clr();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	idx=0;dfs(1);
	for(int i=1;i<=n;i++)ds[i].init();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		ask[r].pb({l,i});
	}
	for(int i=1;i<=n;i++)tree[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k&&dep[i]+j<=n;j++)ds[dep[i]+j].mdf(i,i);
		for(int u=fa[i],j=k-1;u&&~j;u=fa[u]?fa[u]:u,j--){
			if(dep[u]+j<=n)ds[dep[u]+j].mdf(u,i);
			if(j&&dep[u]+j-1<=n)ds[dep[u]+j-1].mdf(u,i);
		}
		for(auto[l,id]:ask[i])ans[id]=que(l);
		// for(int i=1;i<=n;i++)cout<<que(i)-que(i+1)<<" ";cout<<"\n";
		// for(int i=1;i<=n;i++){
			// int p=lower_bound(ds[dep[i]].id.begin(),ds[dep[i]].id.end(),dfn[p])-ds[dep[i]].id.begin();
			// p++;
			// auto it=ds[dep[i]].s.lower_bound({p,p,0});
			// cout<<(*it).v<<" ";
		// }
		// cout<<"\n";
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}