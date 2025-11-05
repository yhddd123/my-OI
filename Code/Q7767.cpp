#include<bits/stdc++.h>
// #define int long long
#define ull unsigned long long
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
const int maxk=4;
const int inf=1e9;
bool mbe;

int n,q,k=3;
vector<int> e[maxn];
int siz[maxn],son[maxn],fa[maxn];
int dfn[maxn],st[18][maxn],tim;
void dfs(int u){
	siz[u]=1;
	st[0][dfn[u]=++tim]=fa[u];
	vector<int> tmp;
	for(int v:e[u])if(v!=fa[u]){
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		tmp.pb(v);
	}
	e[u]=tmp;
	sort(e[u].begin(),e[u].end(),[&](int u,int v){return siz[u]>siz[v];});
	if(e[u].size())son[u]=e[u][0];	
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
void lca_init(){
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int id[maxn],idx;
void downid(int u,int d){
	if(!d){
		if(!id[u])id[u]=++idx;
		return ;
	}
	for(int v:e[u])downid(v,d-1);
}
void dfsid(int u){
	vector<int> path;
	for(int x=u;x;x=son[x])path.pb(x);
	for(int i=0;i<=k;i++){
		for(int u:path)downid(u,i);
	}
	reverse(path.begin(),path.end());
	for(int u:path){
		for(int v:e[u])if(v!=son[u])dfsid(v);
	}
}
void merge(vector<pii> &u,vector<pii> v){
	for(auto p:v)u.pb(p);
}
void reinit(vector<pii> &u){
	sort(u.begin(),u.end());
	vector<pii> nw;
	for(auto[l,r]:u){
		if(nw.size()&&nw.back().se+1==l)nw.back().se=r;
		else nw.pb({l,r});
	}
	u=nw;
}
vector<pii> sub[maxn],kson[maxn][maxk],bro[maxn][maxk];
void dfsup(int u){
	sub[u]={{id[u],id[u]}},kson[u][0]={{id[u],id[u]}};
	for(int v:e[u]){
		dfsup(v);
		merge(sub[u],sub[v]);
		for(int i=0;i<=k;i++)bro[v][i]=kson[u][i];
		for(int i=1;i<=k;i++)merge(kson[u][i],kson[v][i-1]),reinit(kson[u][i]);
	}
	if(e[u].size()){
		vector<pii> tmp[maxk];
		for(int ii=e[u].size()-1;~ii;ii--){
			int v=e[u][ii];
			for(int i=1;i<=k;i++)merge(bro[v][i],tmp[i]),reinit(bro[v][i]);
			for(int i=1;i<=k;i++)merge(tmp[i],kson[v][i-1]),reinit(tmp[i]);
		}
	}
	reinit(sub[u]);
}
vector<pii> kans[maxn][maxk],kdis[maxn][maxk];
void dfsdw(int u){
	for(int i=0;i<=k;i++){
		kans[u][i]=kans[fa[u]][i];
		merge(kans[u][i],kson[u][i]);
		reinit(kans[u][i]);
	}
	for(int i=0;i<=k;i++){
		for(int j=0;j<=i;j++)merge(kdis[u][i],kson[u][j]);
		for(int j=1,x=u;j<=k&&x;x=fa[x],j++){
			for(int k=0;k<=i-j;k++)merge(kdis[u][i],bro[x][k]);
		}
		reinit(kdis[u][i]);
	}
	for(int v:e[u])dfsdw(v);
}
vector<pii> getsub(int u){return sub[u];}
vector<pii> gettp(int u,int tp,int k){
	vector<pii> a=kans[u][k],b=kans[tp][k],nw;
	// cout<<u<<" "<<tp<<" "<<k<<" "<<a.size()<<" "<<b.size()<<endl;
	for(int i=0,l=0;i<a.size();i++){
		while(l<b.size()&&b[l].se<a[i].fi)l++;
		int r=l;while(r<b.size()&&b[r].se<=a[i].se)r++;
		if(l==r)nw.pb(a[i]);
		else{
			int lst=a[i].fi;
			for(int j=l;j<r;j++){
				if(lst<b[j].fi)nw.pb({lst,b[j].fi-1});
				lst=b[j].se+1;
			}
			if(lst<=a[i].se)nw.pb({lst,a[i].se});
		}
		l=r;
	}
	// cout<<"run"<<endl;
	reinit(nw);
	return nw;
}
vector<pii> getpath(int u,int v,int k){
	int tp=lca(u,v);
	vector<pii> a=kdis[tp][k];
	merge(a,gettp(u,tp,k));
	merge(a,gettp(v,tp,k));
	reinit(a);
	return a;
}
struct ds{
	#define lb(x) (x&(-x))
	ull tree[maxn];
	void upd(int x,ull w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	ull que(int x){
		ull res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
}t1,t2;
void upd(int l,int r,ull w){
	t1.upd(l,w),t1.upd(r+1,-w),t2.upd(l,w*l),t2.upd(r+1,-w*(r+1));
}
ull que(int l,int r){
	return t1.que(l)*(r-l+1)+(t1.que(r)-t1.que(l))*(r+1)-(t2.que(r)-t2.que(l));
}
void work(){
	n=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1);
	lca_init();
	dfsid(1);
	dfsup(1);
	dfsdw(1);
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),v=read(),k=read(),w=read();
			vector<pii> a=getpath(u,v,k);
			for(auto[l,r]:a)upd(l,r,w);
		}
		if(op==2){
			int u=read(),w=read();
			vector<pii> a=getsub(u);
			for(auto[l,r]:a)upd(l,r,w);
		}
		if(op==3){
			int u=read(),v=read(),k=read();
			vector<pii> a=getpath(u,v,k);
			ull ans=0;for(auto[l,r]:a)ans+=que(l,r);	
			printf("%llu\n",ans);	
		}
		if(op==4){
			int u=read();
			vector<pii> a=getsub(u);
			ull ans=0;for(auto[l,r]:a)ans+=que(l,r);
			printf("%llu\n",ans);	
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