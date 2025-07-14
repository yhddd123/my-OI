// Problem: P7497 四方喝彩
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7497
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-28 17:31:30
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
int sum0[maxn<<2],sum1[maxn<<2],num[maxn<<2],cnt[maxn<<2];
int tag[maxn<<2],laz[maxn<<2];
int inc(int u,int v){
	((u+=v)>=mod)&&(u-=mod);
	return u;
}
void up(int nd){
	if(!cnt[nd]){
		sum0[nd]=inc(sum0[ls],sum0[rs]),sum1[nd]=inc(sum1[ls],sum1[rs]);
		num[nd]=num[ls]+num[rs];
	}
}
void build(int nd,int l,int r){
	laz[nd]=1;
	if(l==r){sum0[nd]=a[l],num[nd]=1;return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
}
void add(int nd,int x){
	(sum0[nd]+=x*num[nd])%=mod;
	tag[nd]=inc(tag[nd],x);
}
void mul(int nd,int x){
	(sum0[nd]*=x)%=mod;
	(laz[nd]*=x)%=mod;
	(tag[nd]*=x)%=mod;
}
void down(int nd){
	if(laz[nd]!=1){
		if(!cnt[ls])mul(ls,laz[nd]);
		if(!cnt[rs])mul(rs,laz[nd]);
		laz[nd]=1;
	}
	if(tag[nd]){
		if(!cnt[ls])add(ls,tag[nd]);
		if(!cnt[rs])add(rs,tag[nd]);
		tag[nd]=0;
	}
}
void upd1(int nd,int l,int r,int ql,int qr,int x){
	if(cnt[nd])return ;
	if(l>=ql&&r<=qr){add(nd,x);return ;}
	down(nd);
	if(ql<=mid)upd1(ls,l,mid,ql,qr,x);
	if(qr>mid)upd1(rs,mid+1,r,ql,qr,x);
	up(nd);
}
void upd2(int nd,int l,int r,int ql,int qr,int x){
	if(cnt[nd])return ;
	if(l>=ql&&r<=qr){mul(nd,x);return ;}
	down(nd);
	if(ql<=mid)upd2(ls,l,mid,ql,qr,x);
	if(qr>mid)upd2(rs,mid+1,r,ql,qr,x);
	up(nd);
}
void modif(int nd,int l,int r,int ql,int qr,int op){
	if(l>=ql&&r<=qr){
		if(l!=r)down(nd);
		if(op>0){
			if(!cnt[nd]){
				sum1[nd]=inc(sum0[nd],sum1[nd]);sum0[nd]=0;
				num[nd]=0;
			}
			cnt[nd]+=op;
		}
		else{
			cnt[nd]+=op;
			if(!cnt[nd]){
				if(l==r)swap(sum0[nd],sum1[nd]),num[nd]=1;
				else up(nd);	
			}
		}
		return ;
	}
	down(nd);
	if(ql<=mid)modif(ls,l,mid,ql,qr,op);
	if(qr>mid)modif(rs,mid+1,r,ql,qr,op);
	up(nd);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return inc(sum0[nd],sum1[nd]);
	down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return inc(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
vector<pii> que[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	// cout<<sum0[1]<<" "<<sum1[1]<<"\n";
	// for(int j=1;j<=n;j++)cout<<query(1,1,n,j,j)<<" ";cout<<"\n";
	for(int i=1;i<=m;i++){
		for(pii p:que[i])modif(1,1,n,p.fi,p.se,-1);
		int op=read();
		if(op==1){
			int l=read(),r=read(),x=read();
			upd1(1,1,n,l,r,x);
		}
		if(op==2){
			int l=read(),r=read(),x=read();
			upd2(1,1,n,l,r,x);
		}
		if(op==3){
			int l=read(),r=read(),x=read();
			modif(1,1,n,l,r,1);
			if(i+x+1<=m)que[i+x+1].push_back({l,r});
		}
		if(op==4){
			int l=read(),r=read();
			printf("%lld\n",query(1,1,n,l,r));
		}
		// cout<<sum0[1]<<" "<<sum1[1]<<"\n";
		// for(int j=1;j<=n;j++)cout<<query(1,1,n,j,j)<<" ";cout<<"\n";
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
