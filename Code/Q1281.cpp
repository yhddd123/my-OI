#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
const int inf=1e6;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],b[maxn],ans;
int la[maxn],ra[maxn],ta1,ta3,sa[maxn],lb[maxn],rb[maxn],tb1,tb3,sb[maxn];
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<6][2],lc[maxn<<6],rc[maxn<<6],idx,rt;
void updata(int &nd,int l,int r,int p,int v1,int v2){
	if(!nd)nd=++idx;
	if(l==r){tree[nd][0]=max(tree[nd][0],v1),tree[nd][1]=max(tree[nd][1],v2);return ;}
	if(p<=mid)updata(ls,l,mid,p,v1,v2);
	else updata(rs,mid+1,r,p,v1,v2);
	tree[nd][0]=max(tree[ls][0],tree[rs][0]),tree[nd][1]=max(tree[ls][1],tree[rs][1]);
}
int query(int nd,int l,int r,int ql,int qr,int op){
	if(!tree[nd][op]||!nd||ql>qr)return 0;
	if(l>=ql&&r<=qr)return tree[nd][op];
	if(qr<=mid)return query(ls,l,mid,ql,qr,op);
	if(ql>mid)return query(rs,mid+1,r,ql,qr,op);
	return max(query(ls,l,mid,ql,qr,op),query(rs,mid+1,r,ql,qr,op));
}
void work(){
	for(int i=1;i<=idx;i++)tree[i][0]=tree[i][1]=lc[i]=rc[i]=0;idx=rt=0;ta1=ta3=tb1=tb3=0;
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)if(a[i]==1)la[++ta1]=i;
	for(int i=1;i<=n;i++)sa[i]=sa[i-1]+(a[i]==2);
	for(int i=n;i;i--)if(a[i]==3)ra[++ta3]=i;
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=1;i<=m;i++)if(b[i]==1)lb[++tb1]=i;
	for(int i=1;i<=m;i++)sb[i]=sb[i-1]+(b[i]==2);
	for(int i=m;i;i--)if(b[i]==3)rb[++tb3]=i;
	ra[0]=n+1,rb[0]=m+1;ans=0;
	// cout<<ta1<<" "<<ta3<<" "<<tb1<<" "<<tb3<<"\n";
	for(int i=min(ta1,tb1),j=0;~i;i--){
		while(ra[j]>la[i]&&rb[j]>lb[i]&&j<=min(ta3,tb3)){
			updata(rt,-inf,inf,sa[ra[j]-1]-sb[rb[j]-1],j+sa[ra[j]-1],j+sb[rb[j]-1]);
			j++;
		}
		ans=max({ans,i-sa[la[i]]+query(rt,-inf,inf,-inf,sa[la[i]]-sb[lb[i]],0),i-sb[lb[i]]+query(rt,-inf,inf,sa[la[i]]-sb[lb[i]],inf,1)});
	}
	printf("%lld\n",ans);
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
	
	T=read();
	while(T--)work();
}
