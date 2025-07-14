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

int n,m,a[maxn];
int b[maxn],len;
map<int,int> mp;
int rt[maxn],tree[maxn*25],cnt;
int ls[maxn*25],rs[maxn*25];
void build(int &nd,int l,int r){
	if(!nd)nd=++cnt;
	if(l==r)return ;
	int mid=l+r>>1;
	build(ls[nd],l,mid);build(rs[nd],mid+1,r);
}
void updata(int &nd,int l,int r,int ql,int w,int nd1){
	if(!nd){
		nd=++cnt;
		tree[nd]=tree[nd1];
	}
	if(l==r){
		tree[nd]+=w;
		return ;
	}
	int mid=l+r>>1;
	if(ql<=mid)updata(ls[nd],l,mid,ql,w,ls[nd1]),rs[nd]=rs[nd1];
	else updata(rs[nd],mid+1,r,ql,w,rs[nd1]),ls[nd]=ls[nd1];
	tree[nd]=tree[ls[nd]]+tree[rs[nd]];
}
int query(int nd,int nd1,int l,int r,int num){
	if(l==r)return l;
	int mid=l+r>>1;
	if(tree[ls[nd]]-tree[ls[nd1]]>=num)return query(ls[nd],ls[nd1],l,mid,num);
	else return query(rs[nd],rs[nd1],mid+1,r,num-(tree[ls[nd]]-tree[ls[nd1]]));
}
int l,r,k;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i];
	sort(b+1,b+n+1);
	len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		int x=a[i];
		a[i]=lower_bound(b+1,b+len+1,a[i])-b;
		mp[a[i]]=x;
	}
	build(rt[0],1,len);
	for(int i=1;i<=n;i++)updata(rt[i],1,len,a[i],1,rt[i-1]);
	while(m--){
		l=read();r=read();k=read();
		printf("%d\n",mp[query(rt[r],rt[l-1],1,len,k)]);
	}
}
