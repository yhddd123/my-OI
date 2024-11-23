// Problem: P4097 【模板】李超线段树 / [HEOI2013] Segment
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4097
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-10-18 11:16:31
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define db double
#define mod 39989
using namespace std;
const int maxn=100010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans,m;
struct line{
	db k,b;
}p[maxn];
db calc(int u,int x){return 1.0*(x*p[u].k+p[u].b);}
int tree[maxn<<1];
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
void upd(int nd,int l,int r,int id){
	if(l==r){
		if(calc(id,l)-calc(tree[nd],l)>eps)tree[nd]=id;
		return ;
	}
	if(calc(id,mid)-calc(tree[nd],mid)>eps)swap(tree[nd],id);
	if(calc(id,l)-calc(tree[nd],l)>eps)upd(ls,l,mid,id);
	else upd(rs,mid+1,r,id);
}
void updata(int nd,int l,int r,int ql,int qr,int id){
	if(l>=ql&&r<=qr){
		upd(nd,l,r,id);
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,id);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,id);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	int res;
	if(p<=mid)res=query(ls,l,mid,p);
	else res=query(rs,mid+1,r,p);
	if(calc(tree[nd],p)-calc(res,p)>eps)return tree[nd];
	if(calc(tree[nd],p)-calc(res,p)<-eps)return res;
	return min(tree[nd],res);
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		int opt=read();
		if(opt){
			int u,v,uu,vv;
			u=(read()+ans-1+mod)%mod+1;v=(read()+ans-1+inf)%inf+1;
			uu=(read()+ans-1+mod)%mod+1;vv=(read()+ans-1+inf)%inf+1;
			if(u>uu)swap(u,uu),swap(v,vv);
			if(u==uu)p[++m]={0,1.0*max(v,vv)};
			else p[++m]={1.0*(v-vv)/(u-uu),v-u*1.0*(v-vv)/(u-uu)};
			updata(1,1,mod,u,uu,m);
		}
		else{
			int u=(read()+ans-1+mod)%mod+1;
			ans=query(1,1,mod,u);
			printf("%lld\n",ans);
		}
	}
}