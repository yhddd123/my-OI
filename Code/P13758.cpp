// Problem: P13758 【MX-X17-T7】夏终
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13758
// Memory Limit: 512 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2026-01-13 16:04:26
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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=200010;
const int inf=2e15;
bool mbe;

int n,m,q,a[maxn];
int ff[maxn],hd[maxn],ed[maxn],nxt[maxn],fr[maxn],val[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int id[maxn],tmp[maxn];
const int B=1200;
const int maxm=maxn/B+5;
inline void chkmn(int &u,int v){(u>v)&&(u=v);}
inline vector<int> operator*(const vector<int> &u,const vector<int> &v){
	if(!u.size())return v;
	if(!v.size())return u;
	int n=u.size()-1,m=v.size()-1;
	int p=0,q=0,t=0;
	while(p<=n&&u[p]==inf)p++;
	while(q<=m&&v[q]==inf)q++;
	if(p>n||q>m)return {inf};
	vector<int> res;
	res.reserve(n+m+1);
	for(int i=1;i<=p+q;i++)res.pb(inf);
	res.pb(u[p]+v[q]),p++,q++;
	while(p<=n&&q<=m){
		if(u[p]-u[p-1]<v[q]-v[q-1])res.pb(res.back()+u[p]-u[p-1]),p++;
		else res.pb(res.back()+v[q]-v[q-1]),q++;
	}
	while(p<=n)res.pb(res.back()+u[p]-u[p-1]),p++;
	while(q<=m)res.pb(res.back()+v[q]-v[q-1]),q++;
	return res;
}
inline void add(vector<int> &u,vector<int> v){
	if(u.size()<v.size())swap(u,v);
	int n=u.size()-1,m=v.size()-1;
	u.resize(max(n,m)+1,inf);
	for(int i=0;i<=m;i++)chkmn(u[i],v[i]);
}
int pl[maxm],pr[maxm],bel[maxn],num;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct mat{
	vector<int> e00,e01,e10,e11;
	// mat(vector<int> _e00={},vector<int> _e01={},vector<int> _e10={},vector<int> _e11={}){
		// e00=_e00,e01=_e01,e10=_e10,e11=_e11;
	// }
};
inline void upd(mat &res,const mat &u,const mat &v){
	res.e00=u.e00*v.e00;
	add(res.e00,u.e01*v.e10);
	res.e01=u.e00*v.e01;
	add(res.e01,u.e01*v.e11);
	res.e10=u.e10*v.e00;
	add(res.e10,u.e11*v.e10);
	res.e11=u.e10*v.e01;
	add(res.e11,u.e11*v.e11);
}
struct sgt{
	mat tree[B<<2];
	void build(int nd,int l,int r){
		if(l==r){
			tree[nd]={{val[l]},{inf,0},{min(inf,val[l]+a[l])},{val[l],a[l]}};
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		upd(tree[nd],tree[rs],tree[ls]);
	}
	void modif(int nd,int l,int r,int p){
		if(l==r){
			tree[nd]={{val[l]},{inf,0},{min(inf,val[l]+a[l])},{val[l],a[l]}};
			return ;
		}
		if(p<=mid)modif(ls,l,mid,p);
		else modif(rs,mid+1,r,p);
		upd(tree[nd],tree[rs],tree[ls]);
	}
}t[maxm];
#undef mid
int calc(vector<int> &a,int x){
	if(!a.size())return inf;
	// cout<<a.size()<<" "<<x<<endl;
	int l=0,r=a.size()-1;
	while(l<r){
		int mid=l+r>>1;
		if(a[mid]==inf||a[mid]+mid*x>=a[mid+1]+(mid+1)*x)l=mid+1;
		else r=mid;
	}
	return a[l]+l*x;
	// int res=inf;
	// for(int i=0;i<a.size();i++)res=min(res,a[i]+i*x);
	// return res;
}
int gg[2],hh[2];
void work(){
	n=read();m=read();q=read();a[0]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	vector<tuple<int,int,int>> edge;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		edge.pb({w,u,v});
	}
	sort(edge.begin(),edge.end());
	for(int i=1;i<=n;i++)ff[i]=i,hd[i]=ed[i]=i;
	for(auto[w,u,v]:edge){
		u=fd(u),v=fd(v);
		if(u==v)continue;
		ff[u]=v;
		nxt[ed[u]]=hd[v],fr[hd[v]]=ed[u],val[hd[v]]=w;
		hd[v]=hd[u];
	}
	for(int i=1,j=0;i<=n;i++)if(!fr[i]){
		int x=i;val[i]=inf;
		while(x)id[x]=++j,x=nxt[x];
	}
	for(int i=1;i<=n;i++)tmp[id[i]]=a[i];
	for(int i=1;i<=n;i++)a[i]=tmp[i];
	for(int i=1;i<=n;i++)tmp[id[i]]=val[i];
	for(int i=1;i<=n;i++)val[i]=tmp[i];
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n);pl[++num]=l,pr[num]=r;
		for(int j=l;j<=r;j++)bel[j]=num;
		t[num].build(1,l,r);
	}
	multiset<int> s;
	for(int i=1;i<=n;i++)s.insert(a[i]);
	while(q--){
		int x=id[read()],y=read();
		if(x)s.erase(s.find(a[x]));
		a[x]=y;
		if(x)s.insert(a[x]);
		if(x)t[bel[x]].modif(1,pl[bel[x]],pr[bel[x]],x);
		int mn=*s.begin(),w=mn+a[0];
		// cout<<mn<<" "<<w<<"\n";
		gg[0]=gg[1]=0;
		for(int i=1;i<=num;i++){
			chkmn(hh[0]=calc(t[i].tree[1].e00,w)+gg[0],calc(t[i].tree[1].e01,w)+gg[1]);
			chkmn(hh[1]=calc(t[i].tree[1].e10,w)+gg[0],calc(t[i].tree[1].e11,w)+gg[1]);
			gg[0]=hh[0],gg[1]=hh[1];
		}
		write(gg[1]-mn-w);puts("");
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	read();T=1;
	while(T--)work();
}