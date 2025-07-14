#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=50010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,q;
int lmx[maxn<<2],rmx[maxn<<2],mx[maxn<<2];
int tag[maxn<<2];
void up(int nd,int l,int r){
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	lmx[nd]=lmx[ls];
	if(lmx[nd]==mid-l+1)lmx[nd]+=lmx[rs];
	rmx[nd]=rmx[rs];
	if(rmx[nd]==r-mid)rmx[nd]+=rmx[ls];
	mx[nd]=max({mx[ls],rmx[ls]+lmx[rs],mx[rs]});
}
void build(int nd,int l,int r){
	tag[nd]=-1;
	if(l==r){
		lmx[nd]=rmx[nd]=mx[nd]=r-l+1;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	up(nd,l,r);
}
void down(int nd,int l,int r){
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	lmx[ls]=rmx[ls]=mx[ls]=(mid-l+1)*tag[nd];
	tag[ls]=tag[nd];
	lmx[rs]=rmx[rs]=mx[rs]=(r-mid)*tag[nd];
	tag[rs]=tag[nd];
	tag[nd]=-1;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		lmx[nd]=rmx[nd]=mx[nd]=(r-l+1)*w;
		tag[nd]=w;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(tag[nd]!=-1)down(nd,l,r);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	up(nd,l,r);
}
int query(int nd,int l,int r,int k){
	if(l==r)return l;
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(tag[nd]!=-1)down(nd,l,r);
	if(mx[ls]>=k)return query(ls,l,mid,k);
	if(rmx[ls]+lmx[rs]>=k)return mid-rmx[ls]+1;
	return query(rs,mid+1,r,k);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();q=read();
	build(1,1,n);
	while(q--){
		int opt,u,v;
		opt=read();
		if(opt==1){
			u=read();
			if(mx[1]<u)printf("0\n");
			else{
				v=query(1,1,n,u);
				printf("%lld\n",v);
				updata(1,1,n,v,v+u-1,0);
			}
		}
		else{
			u=read();v=read();
			updata(1,1,n,u,u+v-1,1);
		}
	}
}
