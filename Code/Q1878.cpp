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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,m;
int a[maxn],b[maxn],c[maxn];
int lsh[maxn],len;
vector<int> que[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<pii> t1[maxn<<2],t2[maxn<<2];
void updata1(int nd,int l,int r,int ql,int qr,pii w){
	// if(nd==1)cout<<ql<<" "<<qr<<" "<<w.fi<<" "<<w.se<<" a\n";
	if(l>=ql&&r<=qr){t1[nd].pb(w);return ;}
	if(ql<=mid)updata1(ls,l,mid,ql,qr,w);
	if(qr>mid)updata1(rs,mid+1,r,ql,qr,w);
}
void updata2(int nd,int l,int r,int ql,int qr,pii w){
	// if(nd==1)cout<<ql<<" "<<qr<<" "<<w.fi<<" "<<w.se<<" b\n";
	if(l>=ql&&r<=qr){t2[nd].pb(w);return ;}
	if(ql<=mid)updata2(ls,l,mid,ql,qr,w);
	if(qr>mid)updata2(rs,mid+1,r,ql,qr,w);
}
int f[maxn],val[maxn];
int ff[maxn],siz[maxn];
pii st1[maxn];int tp1;
int fd(int x){
	if(x==ff[x])return x;
	return fd(ff[x]);
}
pii st2[maxn<<5];int tp2;
void dfs(int nd,int l,int r){
	// cout<<nd<<" "<<l<<" "<<r<<"\n";
	int lst1=tp1;
	for(auto[u,v]:t1[nd]){
		u=fd(u),v=fd(v);
		if(u==v)continue;
		if(siz[u]<siz[v])swap(u,v);
		ff[v]=u,siz[u]+=siz[v];
		st1[++tp1]={v,val[u]};
		val[u]=max(val[u],val[v]);
		// cout<<u<<" "<<v<<" e1\n";
	}
	int lst2=tp2;
	for(auto[u,v]:t2[nd]){
		u=fd(u);
		if(u==v)continue;
		st2[++tp2]={u,val[u]};
		val[u]=max(val[u],f[v]);
		// cout<<u<<" "<<v<<" e2\n";
	}
	if(l==r){
		for(int u:que[l])f[u]=val[fd(u)];
	}
	else dfs(rs,mid+1,r),dfs(ls,l,mid);
	while(tp2>lst2){
		val[st2[tp2].fi]=st2[tp2].se;
		tp2--;
	}
	while(tp1>lst1){
		int v=st1[tp1].fi,u=ff[v];
		ff[v]=v,siz[u]-=siz[v],val[u]=st1[tp1].se;
		tp1--;
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read(),lsh[++len]=a[i],lsh[++len]=b[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh,b[i]=lower_bound(lsh+1,lsh+len+1,b[i])-lsh;
	for(int i=1;i<=n;i++)que[a[i]].pb(i);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(max(a[u],a[v])<=min(b[u],b[v]))updata1(1,1,len,max(a[u],a[v]),min(b[u],b[v]),{u,v});
		if(a[u]>a[v])swap(u,v);
		if(a[u]<=min(a[v]-1,b[u]))updata2(1,1,len,a[u],min(a[v]-1,b[u]),{u,v});
	}
	for(int i=1;i<=n;i++)ff[i]=i,siz[i]=1,val[i]=c[i];
	dfs(1,1,len);
	for(int i=1;i<=n;i++)printf("%lld ",f[i]);
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