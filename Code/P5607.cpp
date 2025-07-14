// Problem: P5607 [Ynoi2013] 无力回天 NOI2017
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5607
// Memory Limit: 125 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-04-23 16:20:10
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=50010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],b[maxn];
struct bas{
	int p[30],pos[30];
	void insert(int x){
		if(!x)return ;
		for(int i=29;~i;i--)if(x&(1<<i)){
			if(!p[i]){p[i]=x;return ;}
			x^=p[i];
		}
	}
	int query(int res){
		for(int i=29;~i;i--)if(p[i])res=max(res,res^p[i]);
		return res;
	}
}tree[maxn<<2];
bas merge(bas u,bas v){
	bas res=u;
	for(int i=0;i<30;i++)res.insert(v.p[i]);
	return res;
}
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
void build(int nd,int l,int r){
	for(int i=l;i<=r;i++)tree[nd].insert(b[i]);
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int p,int w){
	if(l==r){
		for(int i=0;i<30;i++)tree[nd].p[i]=0;
		tree[nd].insert(w);
		return ;
	}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=merge(tree[ls],tree[rs]);
}
bas query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
namespace bit{
	#define lb(x) (x&(-x))
	int tree[maxn];
	void upd(int x,int w){
		while(x<=n){
			tree[x]^=w;
			x+=lb(x);
		}
	}
	int que(int x){
		int res=0;
		while(x){
			res^=tree[x];
			x-=lb(x);
		}
		return res;
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i-1]^a[i];
	build(1,1,n);
	for(int i=1;i<=n;i++)bit::upd(i,b[i]);
	while(m--){
		int op=read(),l=read(),r=read(),v=read();
		if(op==1){
			b[l]^=v,bit::upd(l,v),updata(1,1,n,l,b[l]);
			if(r<n)b[r+1]^=v,bit::upd(r+1,v),updata(1,1,n,r+1,b[r+1]);
		}
		else{
			if(l==r)printf("%lld\n",max(bit::que(l)^v,v));
			else{
				bas res=query(1,1,n,l+1,r);
				res.insert(bit::que(l));
				printf("%lld\n",res.query(v));
			}
		}
	}
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
