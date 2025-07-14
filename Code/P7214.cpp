// Problem: P7214 [JOISC2020] 治療計画
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7214
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-09-26 15:38:59
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
struct node{
	int t,l,r,c;
}a[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
pii mn[maxn<<2],mx[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){
		mn[nd]={a[l].t+a[l].l-1,l},mx[nd]={a[l].t-a[l].l+1,l};
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
}
void updata(int nd,int l,int r,int p){
	if(l==r){
		mn[nd]={inf,l},mx[nd]={-inf,l};
		return ;
	}
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
	mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
}
pii querymn(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {inf,0};
	if(l>=ql&&r<=qr)return mn[nd];
	if(qr<=mid)return querymn(ls,l,mid,ql,qr);
	if(ql>mid)return querymn(rs,mid+1,r,ql,qr);
	return min(querymn(ls,l,mid,ql,qr),querymn(rs,mid+1,r,ql,qr));
}
pii querymx(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {-inf,0};
	if(l>=ql&&r<=qr)return mx[nd];
	if(qr<=mid)return querymx(ls,l,mid,ql,qr);
	if(ql>mid)return querymx(rs,mid+1,r,ql,qr);
	return max(querymx(ls,l,mid,ql,qr),querymx(rs,mid+1,r,ql,qr));
}
priority_queue<pii> q;
int dis[maxn];bool vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]={read(),read(),read(),read()};
	sort(a+1,a+m+1,[&](node u,node v){return u.t<v.t;});
	build(1,1,m);
	mems(dis,0x3f);
	for(int i=1;i<=m;i++)if(a[i].l==1){
		dis[i]=a[i].c,q.push({-dis[i],i});
		updata(1,1,m,i);
	}
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		pii res=querymn(1,1,m,u+1,m);
		while(res.fi<=a[u].t+a[u].r){
			int v=res.se;
			if(dis[v]>dis[u]+a[v].c){
				dis[v]=dis[u]+a[v].c,q.push({-dis[v],v});
			}
			updata(1,1,m,v);
			res=querymn(1,1,m,u+1,m);
		}
		res=querymx(1,1,m,1,u-1);
		while(res.fi>=a[u].t-a[u].r){
			int v=res.se;
			if(dis[v]>dis[u]+a[v].c){
				dis[v]=dis[u]+a[v].c,q.push({-dis[v],v});
			}
			updata(1,1,m,v);
			res=querymx(1,1,m,1,u-1);
		}
	}
	int ans=inf;
	for(int i=1;i<=m;i++)if(a[i].r==n)ans=min(ans,dis[i]);
	if(ans==inf)ans=-1;
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
	
	T=1;
	while(T--)work();
}