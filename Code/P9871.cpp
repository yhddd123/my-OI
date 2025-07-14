#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl; 
}

int n,m,k,d;
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	int tree[maxn<<2],tag[maxn<<2];
	void clear(){
		memset(tree,0,sizeof(tree));
		memset(tag,0,sizeof(tag));
	}
	void push(int nd,int l,int r){
		tree[ls]+=tag[nd];tag[ls]+=tag[nd];
		tree[rs]+=tag[nd];tag[rs]+=tag[nd];
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			tree[nd]+=w;
			tag[nd]+=w;
			return ;
		}
		if(tag[nd])push(nd,l,r);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=max(tree[ls],tree[rs]);
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(ql>qr)return 0;
		if(l>=ql&&r<=qr)return tree[nd];
		if(tag[nd])push(nd,l,r);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
#undef mid
}
struct nd{
	int l,r,w;
}a[maxn];
bool cmp(nd u,nd v){return u.r<v.r;}
int b[maxn],len;
int dp[maxn][2];
void sovle(){
	n=read();m=read();k=read();d=read();
	b[len=1]=n;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		a[i].r=u;a[i].l=u-v+1;
		b[++len]=a[i].l;b[++len]=a[i].r;
		a[i].w=read();
	}
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=m;i++)a[i].l=lower_bound(b+1,b+len+1,a[i].l)-b;
	for(int i=1;i<=m;i++)a[i].r=lower_bound(b+1,b+len+1,a[i].r)-b;
	sort(a+1,a+m+1,cmp);
	sgt::clear();
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1,j=1,nw=1;i<=len;i++){
		dp[i][0]=max({dp[i-1][0],dp[i-1][1],0ll});
		while(b[i]-b[j]+1>k)j++;
		while(nw<=m&&a[nw].r==i){
			sgt::updata(1,1,len,1,a[nw].l,a[nw].w);
			nw++;
		}
		sgt::updata(1,1,len,1,i-1,-d*(b[i]-b[i-1]));
		dp[i][1]=sgt::query(1,1,len,j,i)-d;
		if(i!=len){
			if(b[i+1]-b[i]==1)sgt::updata(1,1,len,i+1,i+1,dp[i][0]);
			else sgt::updata(1,1,len,i+1,i+1,max(dp[i][0],dp[i][1]));
		}
	}
	printf("%lld\n",max(dp[len][0],dp[len][1]));
}

int op,T;
signed main(){
//	freopen("P9871_4.in","r",stdin);
//	freopen("my.out","w",stdout);
	
	op=read();T=read();
	while(T--)sovle();
}
