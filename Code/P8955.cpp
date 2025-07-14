#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,q,m;
int a[maxn];
int head[maxn],tot;
struct edgend{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	int tree[maxn<<2];
	void updata(int nd,int l,int r,int q,int w){
		if(l==r){
			tree[nd]=w;
			return ;
		}
		if(q<=mid)updata(ls,l,mid,q,w);
		else updata(rs,mid+1,r,q,w);
		tree[nd]=tree[ls]|tree[rs];
	}
	int query(int nd,int l,int r,int x){
		if((x|tree[nd])<=m)return -1;
		if(l==r)return l;
		if((x|tree[ls])>m)return query(ls,l,mid,x);
		else return query(rs,mid+1,r,x|tree[ls]);
	}
#undef mid
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();q=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=q;i++){
		int u=read(),v=read(),x=read();
		add(u,i,x);add(v+1,i,0);
	}
	for(int i=1;i<=n;i++){
		for(int ii=head[i];ii;ii=e[ii].nxt)sgt::updata(1,1,q,e[ii].to,e[ii].w);
		printf("%lld ",sgt::query(1,1,q,a[i]));
	}
}
