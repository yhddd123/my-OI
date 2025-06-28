#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=300010;
const int inf=2e9;
bool mbe;

int n,q,a[maxn],ans;
int pos[maxn];
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<7];
int lc[maxn<<7],rc[maxn<<7],idx,rt[maxn];
void updata(int &nd,int l,int r,int p,int w){
	if(p>n)return ;
	int lst=nd;nd=++idx;tree[nd]=tree[lst],ls=lc[lst],rs=rc[lst];
	if(l==r){tree[nd]+=w;return ;}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
void modif(int &nd,int nd1,int l,int r,int p){
	if(p>n)return ;
	int lst=nd;nd=++idx;tree[nd]=tree[lst],ls=lc[lst],rs=rc[lst];
	if(p<=l){tree[nd]=tree[nd1],ls=lc[nd1],rs=rc[nd1];return ;}
	if(p<=mid)modif(ls,lc[nd1],l,mid,p);
	modif(rs,rc[nd1],mid+1,r,p);
}
int query(int nd,int l,int r,int ql,int qr){
	if(ql>qr||ql>n)return 0;
	if(!nd)return 0;
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)pos[i]=n+1;
	for(int i=n;i;i--){
		int to=pos[a[i]];
		pos[a[i]]=i;
		int val=query(rt[i+1],1,n,i+1,to-1);
		rt[i]=rt[i+1];
		modif(rt[i],rt[to+1],1,n,to);
		updata(rt[i],1,n,to,-val-1);
		updata(rt[i],1,n,i,1);
		// cout<<i<<" "<<to<<" "<<val<<"\n";
		// for(int j=i;j<=n;j++)cout<<query(rt[i],1,n,j,j)<<" ";cout<<"\n";
	}
	while(q--){
		int l=read()^ans,r=read()^ans;
		// cout<<l<<" "<<r<<"\n";
		ans=query(rt[l],1,n,l,r);
		printf("%d\n",ans);
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