#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],b[maxn];
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	int tree[maxn<<2][2][2];
	void up(int nd,int l,int r){
		tree[nd][0][0]=tree[nd][0][1]=tree[nd][1][0]=tree[nd][1][1]=0;
		if(a[mid]<=a[mid+1]){
			tree[nd][0][0]|=(tree[ls][0][0]&tree[rs][0][0]);
			tree[nd][0][1]|=(tree[ls][0][0]&tree[rs][0][1]);
			tree[nd][1][0]|=(tree[ls][1][0]&tree[rs][0][0]);
			tree[nd][1][1]|=(tree[ls][1][0]&tree[rs][0][1]);			
		}
		if(a[mid]<=b[mid+1]){
			tree[nd][0][0]|=(tree[ls][0][0]&tree[rs][1][0]);
			tree[nd][0][1]|=(tree[ls][0][0]&tree[rs][1][1]);
			tree[nd][1][0]|=(tree[ls][1][0]&tree[rs][1][0]);
			tree[nd][1][1]|=(tree[ls][1][0]&tree[rs][1][1]);			
		}
		if(b[mid]<=a[mid+1]){
			tree[nd][0][0]|=(tree[ls][0][1]&tree[rs][0][0]);
			tree[nd][0][1]|=(tree[ls][0][1]&tree[rs][0][1]);
			tree[nd][1][0]|=(tree[ls][1][1]&tree[rs][0][0]);
			tree[nd][1][1]|=(tree[ls][1][1]&tree[rs][0][1]);			
		}
		if(b[mid]<=b[mid+1]){
			tree[nd][0][0]|=(tree[ls][0][1]&tree[rs][1][0]);
			tree[nd][0][1]|=(tree[ls][0][1]&tree[rs][1][1]);
			tree[nd][1][0]|=(tree[ls][1][1]&tree[rs][1][0]);
			tree[nd][1][1]|=(tree[ls][1][1]&tree[rs][1][1]);			
		}
	}
	void build(int nd,int l,int r){
		if(l==r){
			tree[nd][0][0]=tree[nd][1][1]=1;
			return ;
		}
		build(ls,l,mid);build(rs,mid+1,r);
		up(nd,l,r);
	}
	void updata(int nd,int l,int r,int p){
		if(l==r)return ;
		if(p<=mid)updata(ls,l,mid,p);
		else updata(rs,mid+1,r,p);
		up(nd,l,r);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	sgt::build(1,1,n);
//	cout<<sgt::tree[1][0][0]<<" "<<sgt::tree[1][0][1]<<" "<<sgt::tree[1][1][0]<<" "<<sgt::tree[1][1][1]<<"\n";
	m=read();
	while(m--){
		int u=read(),v=read();
		swap(a[u],a[v]);swap(b[u],b[v]);
		sgt::updata(1,1,n,u);sgt::updata(1,1,n,v);
//		cout<<sgt::tree[1][0][0]<<" "<<sgt::tree[1][0][1]<<" "<<sgt::tree[1][1][0]<<" "<<sgt::tree[1][1][1]<<"\n";
		if(sgt::tree[1][0][0]|sgt::tree[1][0][1]|sgt::tree[1][1][0]|sgt::tree[1][1][1])printf("TAK\n");
		else printf("NIE\n");
	}
}
