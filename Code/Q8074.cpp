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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,q;
int a[maxn],b[maxn],tim[maxn];
int ans[maxn];
struct node1{
	int p,a,b;
};
vector<node1> upd[maxn<<2];
struct node2{
	int x,l,r,id;
};
vector<node2> que[maxn<<2];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
void updata1(int nd,int l,int r,int ql,int qr,node1 w){
	if(l>=ql&&r<=qr){
		upd[nd].pb(w);
		return ;
	}
	if(ql<=mid)updata1(ls,l,mid,ql,qr,w);
	if(qr>mid)updata1(rs,mid+1,r,ql,qr,w);
}
void updata2(int nd,int l,int r,int p,node2 w){
	que[nd].pb(w);
	if(l==r)return ;
	if(p<=mid)updata2(ls,l,mid,p,w);
	else updata2(rs,mid+1,r,p,w);
}
int lsh[maxn],len;
vector<pii> mdf[maxn];
vector<pii> tree[maxn<<2];
pii operator-(pii u,pii v){return {u.fi-v.fi,u.se-v.se};}
int cross(pii u,pii v){return u.fi*v.se-u.se*v.fi;}
void ins(vector<pii> &a,pii w){
	while(a.size()>=2&&cross(a[a.size()-1]-a[a.size()-2],w-a[a.size()-1])>=0)a.pop_back();
	a.pb(w);
}
int pos[maxn<<2];
void build(int nd,int l,int r){
	pos[nd]=0;tree[nd].clear();
	if(l==r){
		for(pii p:mdf[l])ins(tree[nd],p);
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	vector<pii> tmp(tree[ls].size()+tree[rs].size());
	int p=0,q=0,ed=0;
	while(p<tree[ls].size()&&q<tree[rs].size()){
		if(tree[ls][p].fi<tree[rs][q].fi)tmp[ed++]=tree[ls][p++];
		else tmp[ed++]=tree[rs][q++];
	}
	while(p<tree[ls].size())tmp[ed++]=tree[ls][p++];
	while(q<tree[rs].size())tmp[ed++]=tree[rs][q++];
	for(pii p:tmp)ins(tree[nd],p);
}
int calc(pii w,int x){return w.fi*x+w.se;}
int query(int nd,int l,int r,int ql,int qr,int x){
	if(l>=ql&&r<=qr){
		while(pos[nd]+1<tree[nd].size()&&calc(tree[nd][pos[nd]+1],x)>=calc(tree[nd][pos[nd]],x))pos[nd]++;
		return calc(tree[nd][pos[nd]],x);
	}
	if(qr<=mid)return query(ls,l,mid,ql,qr,x);
	if(ql>mid)return query(rs,mid+1,r,ql,qr,x);
	return max(query(ls,l,mid,ql,qr,x),query(rs,mid+1,r,ql,qr,x));
}
void dfs(int nd,int l,int r){
	vector<node1> &uu=upd[nd];
	vector<node2> &qq=que[nd];
	if(uu.size()&&qq.size()){
		sort(uu.begin(),uu.end(),[&](node1 u,node1 v){return u.a<v.a;});
		sort(qq.begin(),qq.end(),[&](node2 u,node2 v){return u.x<v.x;});
		len=0;for(auto[p,x,y]:uu)lsh[++len]=p;
		sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
		for(int i=1;i<=len;i++)mdf[i].clear();
		for(auto[p,x,y]:uu){
			p=lower_bound(lsh+1,lsh+len+1,p)-lsh;
			mdf[p].pb({x,y});
		}
		build(1,1,len);
		// cout<<l<<" "<<r<<" s\n";
		// for(pii p:tree[1])cout<<p.fi<<" "<<p.se<<"\n";
		for(auto[x,l,r,id]:qq){
			l=lower_bound(lsh+1,lsh+len+1,l)-lsh;
			r=upper_bound(lsh+1,lsh+len+1,r)-lsh-1;
			if(l<=r)ans[id]=max(ans[id],query(1,1,len,l,r,x));
		}
	}
	if(l==r)return ;
	dfs(ls,l,mid),dfs(rs,mid+1,r);
}
bool vis[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=q;i++){
		int o=read(),k=read(),l=read(),r=read();
		if(o==1){
			if(tim[k]<i)updata1(1,1,q,tim[k]+1,i,{k,a[k],b[k]});
			a[k]=l,b[k]=r;tim[k]=i;
		}
		else{
			updata2(1,1,q,i,{k,l,r,i});
			vis[i]=1;
		}
	}
	for(int i=1;i<=n;i++)if(tim[i]<q)updata1(1,1,q,tim[i]+1,q,{i,a[i],b[i]});
	dfs(1,1,q);
	for(int i=1;i<=q;i++)if(vis[i])printf("%lld\n",ans[i]);
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