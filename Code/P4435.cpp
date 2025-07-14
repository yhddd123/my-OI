#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
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

int n,m,a[maxn];
int gcd(int a,int b){
	return __gcd(a,b);
}
struct seg{
	int ans,l,r;
	vector<pair<int,int> > pre,suf;
}tree[maxn<<2];
#define ls nd<<1
#define rs nd<<1|1
seg up(seg a,seg b){
	seg res;
	res.l=a.l;res.r=b.r;
	res.ans=a.ans+b.ans;
	int j=-1;
	for(int i=a.suf.size()-1;i>=0;i--){
		int len;
		if(i==a.suf.size()-1)len=a.suf[i].first-a.l+1;
		else len=a.suf[i].first-a.suf[i+1].first;
		while(j<(int)(b.pre.size()-1)&&gcd(b.pre[j+1].second,a.suf[i].second)>1)j++;
		if(j==-1)continue;
		if(j==b.pre.size()-1)res.ans+=len*(b.r-b.l+1);
		else res.ans+=len*(b.pre[j+1].first-b.l);
	}
	res.pre=a.pre;
	for(pair<int,int> p:b.pre){
		if(res.pre.back().second!=gcd(res.pre.back().second,p.second)){
			p.second=gcd(p.second,res.pre.back().second);
			res.pre.push_back(p);
		}
	}
	res.suf=b.suf;
	for(pair<int,int> p:a.suf){
		if(res.suf.back().second!=gcd(res.suf.back().second,p.second)){
			p.second=gcd(p.second,res.suf.back().second);
			res.suf.push_back(p);
		}
	}
	return res;
}
void build(int nd,int l,int r){
	if(l==r){
		tree[nd].ans=(a[l]>1);
		tree[nd].pre.push_back(make_pair(l,a[l]));
		tree[nd].suf.push_back(make_pair(l,a[l]));
		tree[nd].l=tree[nd].r=l;
		return ;
	}
	int mid=l+r>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	tree[nd]=up(tree[ls],tree[rs]);
}
void updata(int nd,int l,int r,int p,int w){
	if(l==r){
		tree[nd].ans=(w>1);
		tree[nd].pre[0]=make_pair(l,w);
		tree[nd].suf[0]=make_pair(l,w);
		return ;
	}
	int mid=l+r>>1;
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=up(tree[ls],tree[rs]);
}
seg query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	int mid=l+r>>1;
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return up(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void sovle(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	while(m--){
		int opt=read(),u=read(),v=read();
		if(opt==1)updata(1,1,n,u,v);
		else printf("%lld\n",query(1,1,n,u,v).ans);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
