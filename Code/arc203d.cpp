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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int vl,vr,num;bool fl;
}tree[maxn<<2];
node merge(node u,node v){
	if(u.fl&&v.fl)return {u.vl+v.vl,u.vl+v.vl,0,1};
	if(u.fl)return {u.vl+v.vl,v.vr,v.num,0};
	if(v.fl)return {u.vl,u.vr+v.vl,u.num,0};
	return {u.vl,v.vr,u.num+v.num+(u.vr+v.vl>=2),0};
}
void build(int nd,int l,int r){
	if(l==r){
		if(!a[l])tree[nd]={1,1,0,1};
		else tree[nd]={0,0,0,0};
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	tree[nd]=merge(tree[ls],tree[rs]);
}
void modif(int nd,int l,int r,int p){
	if(l==r){
		if(!a[l])tree[nd]={1,1,0,1};
		else tree[nd]={0,0,0,0};
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	tree[nd]=merge(tree[ls],tree[rs]);
}
void work(){
	n=read();int s=0;
	for(int i=1;i<=n;i++)a[i]=read(),s+=a[i];
	build(1,1,n);
	// cout<<tree[1].num<<" "<<(tree[1].vl>=2)<<" "<<(tree[1].vr>=2)<<"\n";
	q=read();
	while(q--){
		int p=read();s-=a[p],a[p]^=1,s+=a[p];
		modif(1,1,n,p);
		// cout<<tree[1].num<<" "<<tree[1].vl<<" "<<tree[1].vr<<"\n";
		if(!tree[1].num&&!tree[1].vl&&!tree[1].vr){
			if(s==n)printf("%lld\n",n);
			else puts("2");
		}
		else if(tree[1].fl)puts("2");
		else printf("%lld\n",(tree[1].num+(tree[1].vl>=2)+(tree[1].vr>=2))*3+1-(tree[1].vl>=2)-(tree[1].vr>=2)+(tree[1].vl==1)+(tree[1].vr==1));
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