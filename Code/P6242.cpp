#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define ls nd<<1
#define rs nd<<1|1
using namespace std;
const int maxn=500010;
const int inf=2e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int sum[maxn<<2],mxa[maxn<<2],mxb[maxn<<2],cnt[maxn<<2],se[maxn<<2];
int tagmx1[maxn<<2],tagmx2[maxn<<2],tagse1[maxn<<2],tagse2[maxn<<2];
void up(int nd){
	sum[nd]=sum[ls]+sum[rs];
	mxa[nd]=max(mxa[ls],mxa[rs]);
	mxb[nd]=max(mxb[ls],mxb[rs]);
	if(mxa[ls]==mxa[rs]){
		cnt[nd]=cnt[ls]+cnt[rs];
		se[nd]=max(se[ls],se[rs]);
	}
	if(mxa[ls]>mxa[rs]){
		cnt[nd]=cnt[ls];
		se[nd]=max(se[ls],mxa[rs]);
	}
	if(mxa[ls]<mxa[rs]){
		cnt[nd]=cnt[rs];
		se[nd]=max(mxa[ls],se[rs]);
	}
}
void build(int nd,int l,int r){
	if(l==r){
		sum[nd]=mxa[nd]=mxb[nd]=a[l];
		cnt[nd]=1;se[nd]=-inf;
		return ;
	}
	int mid=l+r>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	up(nd);
}
void down(int nd,int l,int r){
	int mid=l+r>>1;
	int mx=max(mxa[ls],mxa[rs]);
	if(mx==mxa[ls]){
		sum[ls]+=tagmx1[nd]*cnt[ls]+tagse1[nd]*(mid-l+1-cnt[ls]);
		mxb[ls]=max(mxb[ls],mxa[ls]+tagmx2[nd]);mxa[ls]+=tagmx1[nd];
		if(se[ls]!=-inf)se[ls]+=tagse1[nd];
		tagmx2[ls]=max(tagmx2[ls],tagmx1[ls]+tagmx2[nd]);tagmx1[ls]+=tagmx1[nd];
		tagse2[ls]=max(tagse2[ls],tagse1[ls]+tagse2[nd]);tagse1[ls]+=tagse1[nd];
	}
	else{
		sum[ls]+=tagse1[nd]*(mid-l+1);
		mxb[ls]=max(mxb[ls],mxa[ls]+tagse2[nd]);mxa[ls]+=tagse1[nd];
		if(se[ls]!=-inf)se[ls]+=tagse1[nd];
		tagmx2[ls]=max(tagmx2[ls],tagmx1[ls]+tagse2[nd]);tagmx1[ls]+=tagse1[nd];
		tagse2[ls]=max(tagse2[ls],tagse1[ls]+tagse2[nd]);tagse1[ls]+=tagse1[nd];
	}
	if(mx==mxa[rs]){
		sum[rs]+=tagmx1[nd]*cnt[rs]+tagse1[nd]*(r-mid-cnt[rs]);
		mxb[rs]=max(mxb[rs],mxa[rs]+tagmx2[nd]);mxa[rs]+=tagmx1[nd];
		if(se[rs]!=-inf)se[rs]+=tagse1[nd];
		tagmx2[rs]=max(tagmx2[rs],tagmx1[rs]+tagmx2[nd]);tagmx1[rs]+=tagmx1[nd];
		tagse2[rs]=max(tagse2[rs],tagse1[rs]+tagse2[nd]);tagse1[rs]+=tagse1[nd];
	}
	else{
		sum[rs]+=tagse1[nd]*(r-mid);
		mxb[rs]=max(mxb[rs],mxa[rs]+tagse2[nd]);mxa[rs]+=tagse1[nd];
		if(se[rs]!=-inf)se[rs]+=tagse1[nd];
		tagmx2[rs]=max(tagmx2[rs],tagmx1[rs]+tagse2[nd]);tagmx1[rs]+=tagse1[nd];
		tagse2[rs]=max(tagse2[rs],tagse1[rs]+tagse2[nd]);tagse1[rs]+=tagse1[nd];
	}
	tagmx1[nd]=tagmx2[nd]=tagse1[nd]=tagse2[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		sum[nd]+=(r-l+1)*w;
		mxa[nd]+=w;mxb[nd]=max(mxb[nd],mxa[nd]);
		if(se[nd]!=-inf)se[nd]+=w;
		tagmx1[nd]+=w;tagmx2[nd]=max(tagmx2[nd],tagmx1[nd]);
		tagse1[nd]+=w;tagse2[nd]=max(tagse2[nd],tagse1[nd]);
		return ;
	}
	down(nd,l,r);
	int mid=l+r>>1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	up(nd);
}
void modif(int nd,int l,int r,int ql,int qr,int w){
	if(mxa[nd]<=w)return ;
	if(l>=ql&&r<=qr&&se[nd]<w){
		int d=mxa[nd]-w;
		sum[nd]-=d*cnt[nd];
		mxa[nd]=w;tagmx1[nd]-=d;
		return ;
	}
	down(nd,l,r);
	int mid=l+r>>1;
	if(ql<=mid)modif(ls,l,mid,ql,qr,w);
	if(qr>mid)modif(rs,mid+1,r,ql,qr,w);
	up(nd);
}
int querysum(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	down(nd,l,r);
	int mid=l+r>>1;
	if(qr<=mid)return querysum(ls,l,mid,ql,qr);
	if(ql>mid)return querysum(rs,mid+1,r,ql,qr);
	return querysum(ls,l,mid,ql,qr)+querysum(rs,mid+1,r,ql,qr);
}
int querymxa(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){
		return mxa[nd];
	}
	down(nd,l,r);
	int mid=l+r>>1;
	if(qr<=mid)return querymxa(ls,l,mid,ql,qr);
	if(ql>mid)return querymxa(rs,mid+1,r,ql,qr);
	return max(querymxa(ls,l,mid,ql,qr),querymxa(rs,mid+1,r,ql,qr));
}
int querymxb(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mxb[nd];
	down(nd,l,r);
	int mid=l+r>>1;
	if(qr<=mid)return querymxb(ls,l,mid,ql,qr);
	if(ql>mid)return querymxb(rs,mid+1,r,ql,qr);
	return max(querymxb(ls,l,mid,ql,qr),querymxb(rs,mid+1,r,ql,qr));
}


int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	while(m--){
		int opt=read(),u,v,w;
		if(opt==1){
			u=read();v=read();w=read();
			updata(1,1,n,u,v,w);
		}
		if(opt==2){
			u=read();v=read();w=read();
			modif(1,1,n,u,v,w);
		}
		if(opt==3){
			u=read();v=read();
			printf("%lld\n",querysum(1,1,n,u,v));
		}
		if(opt==4){
			u=read();v=read();
			printf("%lld\n",querymxa(1,1,n,u,v));
		}
		if(opt==5){
			u=read();v=read();
			printf("%lld\n",querymxb(1,1,n,u,v));
		}
	}
}
