#include<iostream>
using namespace std;
const int maxn=500010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int tree[maxn<<5],ls[maxn<<5],rs[maxn<<5],idx,rt[maxn];
void updata(int &nd,int l,int r,int nd1,int p){
	if(!nd)nd=++idx;
	tree[nd]=tree[nd1]+1;
	if(l==r)return ;
	int mid=l+r>>1;
	if(p<=mid)updata(ls[nd],l,mid,ls[nd1],p),rs[nd]=rs[nd1];
	else updata(rs[nd],mid+1,r,rs[nd1],p),ls[nd]=ls[nd1];
}
int query(int nd,int nd1,int l,int r,int k){
	if(l==r)return l;
	int mid=l+r>>1;
	if(tree[ls[nd1]]-tree[ls[nd]]>=k)return query(ls[nd],ls[nd1],l,mid,k);
	else return query(rs[nd],rs[nd1],mid+1,r,k-(tree[ls[nd1]]-tree[ls[nd]]));
}
int count(int nd,int nd1,int l,int r,int p){
	if(l==r)return tree[nd1]-tree[nd];
	int mid=l+r>>1;
	if(p<=mid)return count(ls[nd],ls[nd1],l,mid,p);
	else return count(rs[nd],rs[nd1],mid+1,r,p);
}

signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)updata(rt[i],1,n,rt[i-1],read());
	while(m--){
		int u,v,k;
		u=read();v=read();k=2;
		int nw=1,d=(v-u+1)/k+1,val=0;
		while(nw<=v-u+1){
			val=query(rt[u-1],rt[v],1,n,nw);
			if(count(rt[u-1],rt[v],1,n,val)>=d)break;
			else nw+=d,val=0;
		}
		printf("%d\n",val);
	}
}
