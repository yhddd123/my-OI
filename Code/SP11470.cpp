#include<iostream>
#define int long long
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],t;
int rt[maxn],cnt;
int tree[maxn*25],add[maxn*25];
int ls[maxn*25],rs[maxn*25];
void build(int &nd,int l,int r){
	if(!nd)nd=++cnt;
	if(l==r){
		tree[nd]=a[l];
		return ;
	}
	int mid=l+r>>1;
	build(ls[nd],l,mid);build(rs[nd],mid+1,r);
	tree[nd]=tree[ls[nd]]+tree[rs[nd]];
}
void updata(int &nd,int l,int r,int nd1,int ql,int qr,int w){
	nd=++cnt;tree[nd]=tree[nd1];add[nd]=add[nd1];
	ls[nd]=ls[nd1];rs[nd]=rs[nd1];
	if(l>=ql&&r<=qr){
		add[nd]+=w;
		return ;
	}
	int mid=l+r>>1;
	if(ql<=mid)updata(ls[nd],l,mid,ls[nd1],ql,qr,w);
	if(qr>mid)updata(rs[nd],mid+1,r,rs[nd1],ql,qr,w);
	tree[nd]=tree[ls[nd]]+tree[rs[nd]]+add[ls[nd]]*(mid-l+1)+add[rs[nd]]*(r-mid);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd]+(r-l+1)*add[nd];
	int mid=l+r>>1;
	if(qr<=mid)return query(ls[nd],l,mid,ql,qr)+(min(qr,r)-max(ql,l)+1)*add[nd];
	if(ql>mid)return query(rs[nd],mid+1,r,ql,qr)+(min(qr,r)-max(ql,l)+1)*add[nd];
	return query(ls[nd],l,mid,ql,qr)+query(rs[nd],mid+1,r,ql,qr)+(min(qr,r)-max(ql,l)+1)*add[nd];
}
char s[2];
int l,r,d;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(rt[t],1,n);
	while(m--){
		scanf("%s",s);
		if(s[0]=='C'){
			l=read();r=read();d=read();
			updata(rt[t+1],1,n,rt[t],l,r,d);t++;
		}
		if(s[0]=='Q'){
			l=read();r=read();
			printf("%lld\n",query(rt[t],1,n,l,r));
		}
		if(s[0]=='H'){
			l=read();r=read();d=read();
			printf("%lld\n",query(rt[d],1,n,l,r));
		}
		if(s[0]=='B')t=read();
	}
}
