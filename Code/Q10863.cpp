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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int pos[maxn],op[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int fl[maxn<<2][2],val[maxn<<2][2];
void init(int nd,int op){
	if(op==0){
		fl[nd][0]=1,val[nd][0]=1;
		fl[nd][1]=0,val[nd][1]=1;
	}
	if(op==1){
		fl[nd][0]=0;val[nd][0]=2;
		fl[nd][1]=0,val[nd][1]=3;
	}
	if(op==2){
		fl[nd][0]=0,val[nd][0]=2;
		fl[nd][1]=0,val[nd][1]=1;
	}
}
void up(int nd){
	for(int o=0;o<2;o++){
		fl[nd][o]=fl[rs][fl[ls][o]];
		val[nd][o]=val[ls][o]+val[rs][fl[ls][o]];
	}
}
void build(int nd,int l,int r){
	if(l==r)return init(nd,op[l]);
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
}
void modif(int nd,int l,int r,int p){
	if(l==r)return init(nd,op[l]);
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	up(nd);
}
void mdf(int v){
	int p1=pos[v],p2=pos[v+n];
	if(p1>p2)swap(p1,p2);
	a[p1]=v,pos[v]=p1,a[p2]=v+n,pos[v+n]=p2;
	op[p1]=0,op[p2]=(p2>1&&a[p2-1]+n==a[p2])?2:1;
	modif(1,1,2*n,p1);
	modif(1,1,2*n,p2);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=2*n;i++)a[i]=read();
	for(int i=1;i<=2*n;i++){
		if(pos[a[i]])a[i]+=n;
		pos[a[i]]=i;
	}
	for(int i=1;i<=2*n;i++)op[i]=a[i]<=n?0:((i>1&&a[i-1]+n==a[i])?2:1);
	build(1,1,2*n);
	printf("%lld\n",val[1][0]/2);
	while(q--){
		int u=read(),v=read();
		swap(a[u],a[v]);swap(pos[a[u]],pos[a[v]]);
		mdf((a[u]-1)%n+1);
		mdf((a[v]-1)%n+1);
		printf("%lld\n",val[1][0]/2);
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