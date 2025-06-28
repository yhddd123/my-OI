// Problem: P12768 [POI 2018 R3] 三人编程锦标赛 Triinformathlon
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12768
// Memory Limit: 128 MB
// Time Limit: 3500 ms
// Written by yhm.
// Start codeing:2025-06-12 22:11:58
// 
// Powered by CP Editor (https://cpeditor.org)

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

int n,q;
int a[maxn],b[maxn],c[maxn];
int id[maxn],rnk[maxn];
struct node{
	int a,b,c,id;
}d[maxn],tmp[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
vector<int> pos;
void upd(int x,int w){
	while(x<=n){
		if(tree[x]==inf)pos.pb(x);
		tree[x]=min(tree[x],w);x+=lb(x);
	}
}
int que(int x){
	int res=inf;
	while(x)res=min(res,tree[x]),x-=lb(x);
	return res;
}
void clr(){
	for(int p:pos)tree[p]=inf;
	pos.clear();
}
int pl[maxn];
void cdq(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	int u=l,v=mid+1,p=l;
	while(u<=mid&&v<=r){
		if(d[u].a>d[v].a)tmp[p++]=d[u++];
		else tmp[p++]=d[v++];
	}
	while(u<=mid)tmp[p++]=d[u++];
	while(v<=r)tmp[p++]=d[v++];
	for(int i=l;i<=r;i++)d[i]=tmp[i];
	for(int i=l;i<=r;i++){
		if(d[i].id<=mid)upd(n-d[i].b+1,d[i].id);
		else pl[d[i].id]=min(pl[d[i].id],que(n-d[i].b+1));
	}
	clr();
}
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return (a[u]<a[v])+(b[u]<b[v])+(c[u]<c[v])>=2;});
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	for(int i=1;i<=n;i++)tree[i]=inf,pl[i]=i;
	for(int i=1;i<=n;i++)d[i]={a[id[i]],b[id[i]],c[id[i]],i};
	cdq(1,n);
	for(int i=1;i<=n;i++)d[i]={b[id[i]],c[id[i]],a[id[i]],i};
	cdq(1,n);
	for(int i=1;i<=n;i++)d[i]={a[id[i]],c[id[i]],b[id[i]],i};
	cdq(1,n);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		for(int j=fd(i);j>pl[i];j=fd(j))f[j]=fd(j-1);
	}
	// for(int i=1;i<=n;i++)cout<<a[id[i]]<<" "<<b[id[i]]<<" "<<c[id[i]]<<"\n";
	// for(int i=1;i<=n;i++)cout<<id[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<pl[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<fd(i)<<" ";cout<<"\n";
	q=read();
	while(q--){
		int u=rnk[read()],v=rnk[read()];
		if(u<v||fd(u)==fd(v))puts("TAK");
		else puts("NIE");
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