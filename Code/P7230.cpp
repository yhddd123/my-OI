// Problem: P7230 [COCI2015-2016#3] NEKAMELEONI
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7230
// Memory Limit: 488 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-09-09 14:48:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q,a[maxn];
multiset<int> s[maxn];
int que[maxn],res[maxn],cnt[maxn];
vector<int> val[maxn];
int st[maxn<<6][4],tp;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
namespace sgt{
	int mx[maxn<<2],tag[maxn<<2],ans[maxn<<2];
	void build(int nd,int l,int r){
		if(l==r){
			mx[nd]=res[l];ans[nd]=mx[nd]-l+1;
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		mx[nd]=max(mx[ls],mx[rs]),ans[nd]=min(ans[ls],ans[rs]);
	}
	void down(int nd,int l,int r){
			st[++tp][0]=nd,st[tp][1]=mx[nd],st[tp][2]=tag[nd],st[tp][3]=ans[nd];
		st[++tp][0]=ls,st[tp][1]=mx[ls],st[tp][2]=tag[ls],st[tp][3]=ans[ls];
		mx[ls]=tag[nd],tag[ls]=tag[nd],ans[ls]=mx[ls]-mid+1;
		st[++tp][0]=rs,st[tp][1]=mx[rs],st[tp][2]=tag[rs],st[tp][3]=ans[rs];
		mx[rs]=tag[nd],tag[rs]=tag[nd],ans[rs]=mx[rs]-r+1;
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			st[++tp][0]=nd,st[tp][1]=mx[nd],st[tp][2]=tag[nd],st[tp][3]=ans[nd];
			mx[nd]=w,tag[nd]=w,ans[nd]=mx[nd]-r+1;
			return ;
		}
		if(tag[nd])down(nd,l,r);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		st[++tp][0]=nd,st[tp][1]=mx[nd],st[tp][2]=tag[nd],st[tp][3]=ans[nd];
		mx[nd]=max(mx[ls],mx[rs]),ans[nd]=min(ans[ls],ans[rs]);
	}
	int fd(int nd,int l,int r,int w){
		if(mx[nd]<w)return -1;
		if(l==r)return l;
		if(tag[nd])down(nd,l,r);
		int val=fd(ls,l,mid,w);
		if(val==-1)return fd(rs,mid+1,r,w);
		return val;
	}
}
vector<pii> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,pii w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		tree[nd].pb(w);
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void add(pii p){
	int l=*--s[p.se].find(p.fi);
	auto it=s[p.se].erase(s[p.se].find(p.fi));
	if(it==s[p.se].end()){
		sgt::updata(1,1,n,l+1,n,inf);
		return ;
	}
	int r=*it;
	int pos=sgt::fd(1,1,n,r);
	if(pos>l+1)sgt::updata(1,1,n,l+1,pos-1,r);
}
void del(){
	int nd=st[tp][0];
	sgt::mx[nd]=st[tp][1],sgt::tag[nd]=st[tp][2],sgt::ans[nd]=st[tp][3];
	tp--;
}
void dfs(int nd,int l,int r){
	int tmp=tp;
	for(pii p:tree[nd])add(p);
	if(l==r){
		if(que[l])printf("%lld\n",sgt::ans[1]>n?-1:sgt::ans[1]);
	}
	else{
		dfs(ls,l,mid),dfs(rs,mid+1,r);
	}
	while(tp>tmp)del();
	for(pii p:tree[nd])s[p.se].insert(p.fi);
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),s[a[i]].insert(i),val[i].pb(a[i]);
	for(int i=1;i<=m;i++)s[i].insert(0);
	for(int i=1;i<=q;i++){
		int op=read();
		if(op==1){
			int p=read(),v=read();
			updata(1,1,q,i,q,{p,a[p]});
			a[p]=v;s[a[p]].insert(p);val[p].pb(a[p]);
			updata(1,1,q,1,i-1,{p,a[p]});
		}
		else que[i]=1;
	}
	for(int i=1,j=1,num=0;i<=n;i++){
		while(j<=n&&num<m){
			for(int k:val[j]){
				if(!cnt[k])++num;
				cnt[k]++;
			}
			j++;
		}
		if(num<m)res[i]=inf;
		else res[i]=j-1;
		for(int k:val[i]){
			cnt[k]--;
			if(!cnt[k])--num;
		}
	}
	sgt::build(1,1,n);
	dfs(1,1,q);
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
