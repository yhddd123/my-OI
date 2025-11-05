#include<bits/stdc++.h>
// #define int long long
#define ll long long
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
const ll inf=1e18;
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
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
ll sum[maxn<<2],mx[maxn<<2],tag[maxn<<2];int len[maxn<<2];
void build(int nd,int l,int r){
	len[nd]=r-l+1;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,ll w){sum[nd]+=w*len[nd],mx[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    sum[nd]=sum[ls]+sum[rs];
    mx[nd]=max(mx[ls],mx[rs]);
}
ll quesum(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return sum[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return quesum(ls,l,mid,ql,qr);
    if(ql>mid)return quesum(rs,mid+1,r,ql,qr);
    return quesum(ls,l,mid,ql,qr)+quesum(rs,mid+1,r,ql,qr);
}
ll quemx(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mx[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return quemx(ls,l,mid,ql,qr);
    if(ql>mid)return quemx(rs,mid+1,r,ql,qr);
    return max(quemx(ls,l,mid,ql,qr),quemx(rs,mid+1,r,ql,qr));
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
	build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),v=read(),k=read(),w=read();
			vector<pii> a=getpath(u,v,k);
			for(auto[l,r]:a)updata(1,1,n,l,r,w);
		}
		if(op==2){
			int u=read(),w=read();
			vector<pii> a=getsub(u);
			for(auto[l,r]:a)updata(1,1,n,l,r,w);
		}
		if(op==3){
			int u=read(),v=read(),k=read();
			vector<pii> a=getpath(u,v,k);
			ll ans=0;for(auto[l,r]:a)ans+=quesum(1,1,n,l,r);
			printf("%lld\n",ans);
		}
		if(op==4){
			int u=read();
			vector<pii> a=getsub(u);
			ll ans=0;for(auto[l,r]:a)ans+=quesum(1,1,n,l,r);
			printf("%lld\n",ans);
		}
		if(op==5){
			int u=read(),v=read(),k=read();
			vector<pii> a=getpath(u,v,k);
			ll ans=-inf;for(auto[l,r]:a)ans=max(ans,quemx(1,1,n,l,r));	
			printf("%lld\n",ans);
		}
		if(op==6){
			int u=read();
			vector<pii> a=getsub(u);
			ll ans=-inf;for(auto[l,r]:a)ans=max(ans,quemx(1,1,n,l,r));	
			printf("%lld\n",ans);
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