// Problem: 传送
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/showproblem.php?pid=7436
// Memory Limit: 524 MB
// Time Limit: 8000 ms
// Written by yhm.
// Start codeing:2024-07-24 15:38:19
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<vector>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int maxn=600010;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
//fk you

#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1

int n,m;
int f[maxn],siz[maxn];ll ans[maxn];
int fd(int x){
	if(x==f[x])return x;
	return fd(f[x]);
}
int st[maxn],tp;
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	if(siz[u]<siz[v])swap(u,v);
	st[++tp]=v;
	f[v]=u,siz[u]+=siz[v],ans[v]-=ans[u];
}
void del(int v){
	int u=f[v];
	f[v]=v,siz[u]-=siz[v],ans[v]+=ans[u];
}
vector<pii> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,pii w){
	if(l>=ql&&r<=qr){tree[nd].push_back(w);return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void dfs(int nd,int l,int r){
	int lst=tp;
	for(pii p:tree[nd])merge(p.fi,p.se);
	if(l==r){
		ans[fd(1)]+=l;
	}
	else{
		dfs(ls,l,mid),dfs(rs,mid+1,r);
	}
	while(tp>lst)del(st[tp]),tp--;
}

signed main(){
	n=read();m=read();
	while(m--){
		int u=read(),v=read(),l=read(),r=read();
		updata(1,1,n,l,r,{u,v});
	}
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	dfs(1,1,n);
	ll res=0;for(int i=1;i<=n;i++)res^=ans[i];
	printf("%lld\n",res);	
}