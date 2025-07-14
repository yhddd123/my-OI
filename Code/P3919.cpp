#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int rt[maxn],tree[maxn*25],cnt;
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
	if(!nd){
		nd=++cnt;
		tree[nd]=tree[nd1];
	}
	if(l==r){
		tree[nd]=w;
		return ;
	}
	int mid=l+r>>1;
	if(ql<=mid)updata(ls[nd],l,mid,ls[nd1],ql,w),rs[nd]=rs[nd1];
	else updata(rs[nd],mid+1,r,rs[nd1],ql,w),ls[nd]=ls[nd1];
}
int query(int nd,int l,int r,int ql){
	if(l==r)return tree[nd];
	int mid=l+r>>1;
	if(ql<=mid)return query(ls[nd],l,mid,ql);
	else return query(rs[nd],mid+1,r,ql);
}
int lst,opt,u,w;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(rt[0],1,n);
	for(int i=1;i<=m;i++){
		lst=read();opt=read();
		if(opt==1){
			u=read();w=read();
			updata(rt[i],1,n,rt[lst],u,w);
		}
		else{
			u=read();
			printf("%d\n",query(rt[lst],1,n,u));
			rt[i]=++cnt;ls[rt[i]]=ls[rt[lst]];rs[rt[i]]=rs[rt[lst]];
		}
	}
}
