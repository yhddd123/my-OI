#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x;
}
int n,q;
map<int,int> mp;
int ls[maxn<<5],rs[maxn<<5],tree[maxn<<5];
int lmx[maxn<<5],rmx[maxn<<5],mx[maxn<<5],md[maxn<<5];
int cnt,rt;
void build(int &nd,int l,int r){
	nd=++cnt;
	tree[nd]=0;lmx[nd]=rmx[nd]=mx[nd]=r-l+1;
	md[nd]=(r+l+1)/2;
}
void up(int nd,int l,int r){
	int mid=l+r>>1;
	tree[nd]=tree[ls[nd]]+tree[rs[nd]];
	lmx[nd]=lmx[ls[nd]];
	if(lmx[nd]==mid-l+1)lmx[nd]+=lmx[rs[nd]];
	rmx[nd]=rmx[rs[nd]];
	if(rmx[nd]==r-mid)rmx[nd]+=rmx[ls[nd]];
	mx[nd]=0;
	if(mx[nd]<mx[rs[nd]])mx[nd]=mx[rs[nd]],md[nd]=md[rs[nd]];
	if(mx[nd]<lmx[rs[nd]]+rmx[ls[nd]])mx[nd]=lmx[rs[nd]]+rmx[ls[nd]],md[nd]=mid-rmx[ls[nd]]+1+(mx[nd]>>1);
	if(mx[nd]<mx[ls[nd]])mx[nd]=mx[ls[nd]],md[nd]=md[ls[nd]];
}
void updata(int &nd,int l,int r,int ql,int w){
	if(l==r){
		lmx[nd]=rmx[nd]=mx[nd]=1-w;
		tree[nd]=w;
		return ;
	}
	int mid=l+r>>1;
	if(!ls[nd])build(ls[nd],l,mid);
	if(!rs[nd])build(rs[nd],mid+1,r);
	if(ql<=mid)updata(ls[nd],l,mid,ql,w);
	else updata(rs[nd],mid+1,r,ql,w);
	up(nd,l,r);
}
int query(int nd,int l,int r,int ql,int qr){
	if(!nd)return 0;
	if(l>=ql&&r<=qr)return tree[nd];
	int res=0,mid=l+r>>1;
	if(ql<=mid)res+=query(ls[nd],l,mid,ql,qr);
	if(qr>mid)res+=query(rs[nd],mid+1,r,ql,qr);
	return res;
	
}
signed main(){
	n=read();q=read();
	build(rt,1,n);
	while(q--){
		int k,u,v;
		k=read();
		if(!k){
			u=read();v=read();
			printf("%d\n",query(rt,1,n,u,v));
		}
		else{
			if(mp[k]){
				updata(rt,1,n,mp[k],0);
				mp[k]=0;
			}
			else{
				mp[k]=md[rt];
				updata(rt,1,n,mp[k],1);
			}
		}
	}
}
