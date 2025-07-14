#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,len;
struct seg{
	int sum;
	int ls,rs;
}tree[maxn<<8];
int rt[2][maxn],idx;
int nd[4][maxn],c0,c1,c2,c3;
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)nd=++idx;
	tree[nd].sum+=w;
	if(l==r)return ;
	int mid=l+r>>1;
	if(p<=mid)updata(tree[nd].ls,l,mid,p,w);
	else updata(tree[nd].rs,mid+1,r,p,w);
}
int query(int l,int r,int ql,int qr,int k){
	if(l==r)return l;
	int mid=l+r>>1,tot=0;
	for(int i=1;i<=c0;i++)tot-=ql*tree[tree[nd[0][i]].rs].sum;
	for(int i=1;i<=c1;i++)tot+=(qr+1)*tree[tree[nd[1][i]].rs].sum;
	for(int i=1;i<=c2;i++)tot+=tree[tree[nd[2][i]].rs].sum;
	for(int i=1;i<=c3;i++)tot-=tree[tree[nd[3][i]].rs].sum;
	if(k<=tot){
		for(int i=1;i<=c0;i++)nd[0][i]=tree[nd[0][i]].rs;
		for(int i=1;i<=c1;i++)nd[1][i]=tree[nd[1][i]].rs;
		for(int i=1;i<=c2;i++)nd[2][i]=tree[nd[2][i]].rs;
		for(int i=1;i<=c3;i++)nd[3][i]=tree[nd[3][i]].rs;
		return query(mid+1,r,ql,qr,k);
	}
	else{
		for(int i=1;i<=c0;i++)nd[0][i]=tree[nd[0][i]].ls;
		for(int i=1;i<=c1;i++)nd[1][i]=tree[nd[1][i]].ls;
		for(int i=1;i<=c2;i++)nd[2][i]=tree[nd[2][i]].ls;
		for(int i=1;i<=c3;i++)nd[3][i]=tree[nd[3][i]].ls;
		return query(l,mid,ql,qr,k-tot);
	}
}
int lowbit(int x){return x&(-x);}

signed main(){
	n=read();m=read();len=2*n+1;
	while(m--){
		int opt,u,v,w;
		opt=read();u=read();v=read();w=read();
		if(opt==1){
			w+=n+1;
			for(int i=u;i<=n;i+=lowbit(i))updata(rt[0][i],1,len,w,1);
			for(int i=v+1;i<=n;i+=lowbit(i))updata(rt[0][i],1,len,w,-1);
			for(int i=u;i<=n;i+=lowbit(i))updata(rt[1][i],1,len,w,u);
			for(int i=v+1;i<=n;i+=lowbit(i))updata(rt[1][i],1,len,w,-v-1);
		}
		else{
			c0=c1=c2=c3=0;
			for(int i=u-1;i;i-=lowbit(i))nd[0][++c0]=rt[0][i];
			for(int i=v;i;i-=lowbit(i))nd[1][++c1]=rt[0][i];
			for(int i=u-1;i;i-=lowbit(i))nd[2][++c2]=rt[1][i];
			for(int i=v;i;i-=lowbit(i))nd[3][++c3]=rt[1][i];
			printf("%lld\n",query(1,len,u,v,w)-n-1);
		}
	}
}
