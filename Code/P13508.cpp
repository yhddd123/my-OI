// Problem: P13508 [OOI 2024] Burenka and Pether
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13508
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-11-13 16:24:43
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,d,q,a[maxn],b[maxn];
int nxt[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
struct ask{
	int op,l,r,id;
}que[maxn];
int ans[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
namespace sgt1{
	int mx[maxn<<2];
	void build(int nd,int l,int r){
		mx[nd]=-inf;
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void modif(int nd,int l,int r,int p,int w){
		mx[nd]=max(mx[nd],w);
		if(l==r)return ;
		if(p<=mid)modif(ls,l,mid,p,w);
		else modif(rs,mid+1,r,p,w);
	}
	void clr(int nd,int l,int r){
		if(mx[nd]==-inf)return ;mx[nd]=-inf;
		if(l==r)return ;
		clr(ls,l,mid),clr(rs,mid+1,r);
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return mx[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}
namespace sgt2{
	int mx[maxn<<2];
	void build(int nd,int l,int r){
		mx[nd]=-inf;
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){mx[nd]=max(mx[nd],w);return ;}
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	}
	int query(int nd,int l,int r,int p){
		if(l==r)return mx[nd];
		if(p<=mid)return max(query(ls,l,mid,p),mx[nd]);
		else return max(query(rs,mid+1,r,p),mx[nd]);
	}
}
#undef mid
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int in[maxn],out[maxn],idx,dep[maxn];
void dfs(int u){
	in[u]=++idx;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dep[v]=dep[u]+1;dfs(v);
	}
	out[u]=idx;
}
vector<int> mdf[maxn];
void sovle(int l,int r,int ql,int qr){
	if(ql>qr||l==r)return ;
	int mid=l+r>>1;
	int qp=ql-1;while(qp<qr&&que[qp+1].r<=mid)qp++;
	sovle(l,mid,ql,qp);
	// cout<<l<<" "<<r<<" s"<<endl;
	for(int i=l;i<=mid+1;i++)head[i]=0;tot=0;
	for(int i=mid;i>=l;i--){
		int fa=sgt1::query(1,1,n,b[i],nxt[b[i]]);
		if(fa>=l)add(fa,i);
		else add(mid+1,i);
		sgt1::modif(1,1,n,b[i],i);
	}
	sgt1::clr(1,1,n);
	for(int i=mid+1;i<=r;i++)sgt1::modif(1,1,n,b[i],-i);
	for(int i=mid+1;i<=r;i++)mdf[i].clear();
	for(int i=l;i<=mid;i++){
		int fa=-sgt1::query(1,1,n,b[i],nxt[b[i]]);
		if(fa<=r)mdf[fa].pb(i);
	}
	sgt1::clr(1,1,n);
	idx=0;dfs(mid+1);
	sgt2::build(1,1,idx);
	for(int i=mid+1,j=qp+1;i<=r;i++){
		for(int u:mdf[i])sgt2::updata(1,1,idx,in[u],out[u],-u);
		sgt1::modif(1,1,n,b[i],i);
		while(j<=qr&&que[j].r==i){
			if(que[j].l<=mid){
				int p=-sgt2::query(1,1,idx,in[que[j].l]);
				if(p==inf)ans[que[j].id]=0,que[j].l=que[j].r;
				else{
					ans[que[j].id]+=dep[que[j].l]-dep[p]+1;
					que[j].l=sgt1::query(1,1,n,b[p],nxt[b[p]]);
				}
				// cout<<que[j].l<<" "<<que[j].r<<" "<<p<<endl;
			}
			j++;
		}
	}
	sgt1::clr(1,1,n);
	sovle(mid+1,r,qp+1,qr);
}
void work(){
	n=read();d=read();read();
	for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]=i;
	for(int i=1;i<=n;i++)f[i]=i;
	set<int> s;
	for(int i=1;i<=n;i++){
		auto it=s.insert(b[i]).fi;
		if(it!=s.begin()){
			it--;
			if(b[i]-(*it)<=d){
				int u=fd(*it),v=fd(b[i]);
				if(u>v)swap(u,v);
				f[u]=v;
			}
			it++;
		}
		if(it!=--s.end()){
			it++;
			if((*it)-b[i]<=d){
				int u=fd(*it),v=fd(b[i]);
				if(u>v)swap(u,v);
				f[u]=v;
			}
			it--;
		}
		nxt[b[i]]=min(n,fd(b[i])+d);
		// cout<<i<<" "<<b[i]<<" "<<fd(b[i])<<" "<<nxt[b[i]]<<"\n";
	}
	// for(int i=1;i<=n;i++)cout<<nxt[i]<<" ";cout<<"\n";
	q=read();
	for(int i=1;i<=q;i++){
		int op=read(),l=read(),r=read();
		que[i]={op,a[l],a[r],i};
	}
	sort(que+1,que+q+1,[&](ask u,ask v){return u.r<v.r;});
	sgt1::build(1,1,n);
	sovle(1,n,1,q);
	for(int i=1;i<=q;i++)if(que[i].op==1)ans[que[i].id]=min(ans[que[i].id],1);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
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