#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=250010;
const int inf=1e9;
bool mbe;

int n,m,q;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int pl[maxn<<2],pr[maxn<<2],pos[maxn];
struct node{
	int sum,add,mn,mnp;
}tree[maxn<<2];
node operator+(node u,node v){
	node res;
	res.sum=u.sum+v.sum,res.add=u.add+v.add,res.mn=min(u.mn,u.sum+v.mn);
	res.mnp=(res.mn==u.sum+v.mn?v.mnp:u.mnp);
	return res;
}
void build(int nd,int l,int r){
	pl[nd]=l,pr[nd]=r;tree[nd]={0,0,0,r};
	if(l==r){pos[l]=nd;return ;}
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif1(int nd,int l,int r,int p,int w){
	if(l==r){
		tree[nd].sum+=w,tree[nd].add+=w,tree[nd].mn+=w;
		return ;
	}
	if(p<=mid)modif1(ls,l,mid,p,w);
	else modif1(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
void modif2(int nd,int l,int r,int p,int w){
	if(l==r){
		tree[nd].sum+=w,tree[nd].mn+=w;
		return ;
	}
	if(p<=mid)modif2(ls,l,mid,p,w);
	else modif2(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
node query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {0,0,0,0};
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int find(int p,int w){
	int nd=pos[p];
	if(tree[nd].add>=w)return p;
	w-=tree[nd].add;
	while(nd){
		if(~nd&1){
			if(tree[nd^1].add>=w){nd^=1;break;}
			w-=tree[nd^1].add;
		}
		nd>>=1;
	}
	if(!nd)return q+1;
	int l=pl[nd],r=pr[nd];
	while(l!=r){
		if(tree[ls].add>=w)nd=ls,r=mid;
		else w-=tree[ls].add,nd=rs,l=mid+1;
	}
	return l;
}
int id[maxn];
vector<pii> upd1[maxn],upd2[maxn],que[maxn];
int ans[maxn];
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=q;i++){
		int op=read();
		if(op==1){
			int l=read(),r=read(),c=read(),k=read();
			id[i]=c;
			upd1[l].pb({i,k}),upd1[r+1].pb({i,-k});
		}
		if(op==2){
			int l=read(),r=read(),k=read();
			upd2[l].pb({i,-k}),upd2[r+1].pb({i,k});
		}
		if(op==3){
			int p=read(),k=read();
			que[p].pb({i,k});
		}
	}
	build(1,0,q);
	for(int i=1;i<=n;i++){
		for(auto[t,w]:upd1[i])modif1(1,0,q,t,w);
		for(auto[t,w]:upd2[i])modif2(1,0,q,t,w);
		for(auto[t,w]:que[i]){
			node res1=query(1,0,q,0,t-1);
			node res2=query(1,0,q,res1.mnp+1,t);
			// cout<<t<<" "<<w<<" q\n";
			// cout<<res1.mn<<" "<<res1.mnp<<"\n";
			w+=res2.add-res2.sum;
			// cout<<res2.add<<" "<<res2.sum<<"\n";
			int p=find(res1.mnp+1,w);
			// cout<<w<<" "<<p<<"\n";
			if(p>t)ans[t]=-1;
			else ans[t]=p;
		}
	}
	for(int i=1;i<=q;i++)if(ans[i]){
		if(ans[i]==-1)ans[i]=0;
		printf("%lld\n",id[ans[i]]);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}