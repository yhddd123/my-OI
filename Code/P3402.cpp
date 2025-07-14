#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
struct nd{
	int rt[maxn],a[maxn];
	int tree[maxn*25],cnt;
	int ls[maxn*25],rs[maxn*25];
	void build(int &nd,int l,int r){
		if(!nd)nd=++cnt;
		if(l==r){
			tree[nd]=a[l];
			return ;
		}
		int mid=l+r>>1;
		build(ls[nd],l,mid);build(rs[nd],mid+1,r);
	}
	void updata(int &nd,int l,int r,int nd1,int ql,int w){
		nd=++cnt;tree[nd]=tree[nd1];ls[nd]=ls[nd1];rs[nd]=rs[nd1];
		if(l==r){
			tree[nd]=w;
			return ;
		}
		int mid=l+r>>1;
		if(ql<=mid)updata(ls[nd],l,mid,ls[nd1],ql,w);
		else updata(rs[nd],mid+1,r,rs[nd1],ql,w);
	}
	int query(int nd,int l,int r,int ql){
		if(l==r)return tree[nd];
		int mid=l+r>>1;
		if(ql<=mid)return query(ls[nd],l,mid,ql);
		else return query(rs[nd],mid+1,r,ql);
	}
}f,siz;
int fd(int x,int p){
	int fa=f.query(f.rt[p],1,n,x);
	if(x==fa)return x;
	return fd(fa,p);
}
void merge(int u,int v,int p){
	int x=fd(u,p),y=fd(v,p);
	if(x==y)return ;
	int sx=siz.query(siz.rt[p],1,n,x),sy=siz.query(siz.rt[p],1,n,y);
	if(sx<=sy){
		f.updata(f.rt[p],1,n,f.rt[p],x,y);
		siz.updata(siz.rt[p],1,n,siz.rt[p],y,sx+sy);
	}
	else{
		f.updata(f.rt[p],1,n,f.rt[p],y,x);
		siz.updata(siz.rt[p],1,n,siz.rt[p],x,sx+sy);
	}
}
int opt,u,v;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)f.a[i]=i,siz.a[i]=1;
	f.build(f.rt[0],1,n);siz.build(siz.rt[0],1,n);
	for(int i=1;i<=m;i++){
		opt=read();
		f.rt[i]=f.rt[i-1];
		siz.rt[i]=siz.rt[i-1];
		if(opt==1){
			u=read();v=read();
			merge(u,v,i);
		}
		else if(opt==2){
			u=read();
			f.rt[i]=f.rt[u];
			siz.rt[i]=siz.rt[u];
		}
		else{
			u=read();v=read();
			if(fd(u,i)==fd(v,i))printf("1\n");
			else printf("0\n");
		}
	}
}
