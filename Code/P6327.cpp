#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m,a[maxn];
int opt,x,y,w;

struct nd{
	double s,c;
	int tag;
}tree[maxn<<2];

void up(int nd){
	int ls=nd<<1,rs=nd<<1|1;
	tree[nd].c=tree[ls].c+tree[rs].c;
	tree[nd].s=tree[ls].s+tree[rs].s;
}

void down(int nd){
	tree[nd].tag+=w;
	double cs=tree[nd].c,sn=tree[nd].s;
	tree[nd].c=cs*cos(w)-sn*sin(w);
	tree[nd].s=sn*cos(w)+cs*sin(w);
}
void push(int nd){
	int ls=nd<<1,rs=nd<<1|1;
	down(ls);down(rs);
	tree[nd].tag=0;
}

void build(int nd,int l,int r){
	if(l==r){
		tree[nd].c=cos(a[l]);
		tree[nd].s=sin(a[l]);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	up(nd);
}

void add(int nd,int l,int r){
	if(l>=x&&r<=y){
		down(nd);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(tree[nd].tag)push(nd);
	if(x<=mid)add(ls,l,mid);
	if(y>mid)add(rs,mid+1,r);
	up(nd);
}

double query(int nd,int l,int r){
	if(l>=x&&r<=y){
		return tree[nd].s;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	m=read();
	while(m--){
		opt=read();l=read();r=read();
		if(opt==1){
			w=read();
			add(1,1,n);
		}
		else printf("%.1lf\n",query(1,1,n));
	} 
}

