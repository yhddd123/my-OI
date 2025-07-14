#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=300010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],k;
vector<int> ans;
struct sgt{
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	vector<pii> tree;
	void updata(int nd,int l,int r,int p,pii w){
		if(l==r){tree[nd]=w;return ;}
		if(p<=mid)updata(ls,l,mid,p,w);
		else updata(rs,mid+1,r,p,w);
		tree[nd]=max(tree[ls],tree[rs]);
	}
	pii query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tree[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}t[maxn];
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<k;i++)t[i].tree.resize((n/k+5)<<2);
	for(int i=1;i<=n;i++)t[i%k].updata(1,0,n/k+2,i/k,{a[i],-i});
	int pos=1;
	while(pos<=n){
		pii p=t[pos%k].query(1,0,n/k+2,pos/k,n/k+2);
		if(!p.fi)break;
		ans.pb(p.fi),pos=-p.se+1;
	}
	for(int i:ans)printf("%lld ",i);
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
