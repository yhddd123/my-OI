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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,ans[maxn];
int a[maxn],b[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int trans[3][3]={{0,1,1},{1,1,2},{1,2,2}};
int calc(int p,int x,int y){return (a[p]<=x)+(b[p]>=y);}
int tree[maxn<<2][3];
int vx,vy;
void up(int nd){
	for(auto i:{0,1,2})tree[nd][i]=tree[rs][tree[ls][i]];
}
void build(int nd,int l,int r){
	if(l==r){
		for(auto i:{0,1,2})tree[nd][i]=trans[1][i];
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
}
void modif(int nd,int l,int r,int p,int op){
	if(p==1)return ;
	if(l==r){
		for(auto i:{0,1,2})tree[nd][i]=trans[op][i];
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p,op);
	else modif(rs,mid+1,r,p,op);
	up(nd);
}
int pa[maxn],pb[maxn];
int l[maxn],r[maxn],res[maxn];
void sovle(){
	build(1,2,n);
	for(int i=1;i<=n;i++)pa[a[i]]=pb[b[i]]=i;
	for(int i=1,j=1;i<=n;i++){
		modif(1,2,n,pa[i],calc(pa[i],i,j));
		while(j<=n&&tree[1][calc(1,i,j)]==2)j++,modif(1,2,n,pb[j-1],calc(pb[j-1],i,j));
		res[i]=j-1;
	}
}
void work(){
	n=read();for(int i=0;i<n;i++)ans[i]=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sovle();
	for(int i=1;i<=n;i++)r[i]=res[i];
	for(int i=1;i<=n;i++)a[i]=n-a[i]+1;
	for(int i=1;i<=n;i++)b[i]=n-b[i]+1;
	sovle();
	for(int i=1;i<=n;i++)l[n-i+1]=n-res[i]+1;
	auto upd=[&](int l,int r,int w=1){ans[l]+=w,ans[r+1]-=w;};
	for(int i=1;i<=n;i++)if(l[i]<=r[i]){
		if(i<=l[i])upd(l[i]-i,r[i]-i);
		else if(r[i]<=i)upd(i-r[i],i-l[i]);
		else upd(0,i-l[i]),upd(1,r[i]-i);
	}
	for(int i=1;i<n;i++)ans[i]+=ans[i-1];
	for(int i=0;i<n;i++)printf("%d ",ans[i]);puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}