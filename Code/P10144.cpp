// Problem: P10144 [WC2024] 水镜
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10144
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// Problem: P10144 [WC/CTS2024] 水镜
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10144
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}
#define pii pair<int,int>

int n,a[maxn],ans;
struct nd{
	pii f[2][2];
}tree[maxn<<2];
void init(pii &u){
	if(u.first>=u.second)u=make_pair(inf,0);
}
void clr(nd &u){
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++)init(u.f[i][j]);
	}
}
pii mymin(pii u,pii v){
	init(u),init(v);
	return {max(u.first,v.first),min(u.second,v.second)};
}
pii mymax(pii u,pii v){
	init(u),init(v);
	return {min(u.first,v.first),max(u.second,v.second)};
}
nd merge(nd u,nd v){
	nd res;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			res.f[i][j]=mymax(mymin(u.f[i][0],v.f[0][j]),mymin(u.f[i][1],v.f[1][j]));
			init(res.f[i][j]);
		}
	}
	return res;
}
#define mid (l+r>>1)
#define ls o<<1
#define rs o<<1|1
void build(int o,int l,int r){
	if(l==r){
		tree[o].f[0][0]=tree[o].f[1][1]={inf,0};
		tree[o].f[0][1]={a[l]+a[l+1],inf};
		tree[o].f[1][0]={0,a[l]+a[l+1]};
		if(a[l]<a[l+1])tree[o].f[0][0]={0,inf};
		if(a[l]>a[l+1])tree[o].f[1][1]={0,inf};
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	tree[o]=merge(tree[ls],tree[rs]);
	clr(tree[o]);
}
nd query(int o,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[o];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	nd res=merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	clr(res);
	return res;
}
bool check(int l,int r){
	nd res=query(1,1,n-1,l,r-1);
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			if(res.f[i][j].first<res.f[i][j].second)return true;
		}
	}
	return false;
}
#undef mid

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n-1);
	// for(int i=393;i<397;i++){
		// for(int j=i+1;j<=397;j++){
			// nd res=query(1,1,n-1,i,j-1);
			// for(int ii=0;ii<2;ii++){
				// for(int jj=0;jj<2;jj++)cout<<res.f[ii][jj].first<<" "<<res.f[ii][jj].second<<" ";
				// cout<<"\n";
			// }
			// cout<<i<<" "<<j<<" p\n";
		// }
	// }
	for(int i=1,r=0;i<=n;i++){
		if(r<i)r=i;
		while(r<n&&check(i,r+1))r++;
		ans+=r-i;
		// cout<<i<<" "<<r<<"\n";
	}
	printf("%lld\n",ans);
}