// Problem: P6071 『MdOI R1』Treequery
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6071
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-04-10 12:37:40
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,ans;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dfn[maxn],rnk[maxn],tim,st[18][maxn],siz[maxn],dis[maxn];
void dfs(int u,int fa){
	st[0][dfn[u]=++tim]=fa,rnk[tim]=u,siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dis[v]=dis[u]+e[i].w;dfs(v,u);siz[u]+=siz[v];
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(!u||!v)return 0;
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int calc(int u,int v){return dis[u]+dis[v]-2*dis[lca(u,v)];}
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int rt[maxn],idx;
int tree[maxn<<5],lc[maxn<<5],rc[maxn<<5];
void updata(int &nd,int l,int r,int p){
	int lst=nd;nd=++idx;tree[nd]=tree[lst]+1,ls=lc[lst],rs=rc[lst];
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
}
int findmn(int nd,int nd1,int l,int r,int p){
	if(tree[nd]-tree[nd1]==0)return n+1;
	if(l==r)return l;
	if(p<=mid){
		int res=findmn(ls,lc[nd1],l,mid,p);
		if(res<=n)return res;
	}
	return findmn(rs,rc[nd1],mid+1,r,p);
}
int findmx(int nd,int nd1,int l,int r,int p){
	if(tree[nd]-tree[nd1]==0)return 0;
	if(l==r)return l;
	if(p>mid){
		int res=findmx(rs,rc[nd1],mid+1,r,p);
		if(res)return res;
	}
	return findmx(ls,lc[nd1],l,mid,p);
}
void work(){
	n=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)updata(rt[i]=rt[i-1],1,n,dfn[i]);
	while(q--){
		int u=read(),l=read(),r=read();
		u^=ans,l^=ans,r^=ans;
		int mn=findmn(rt[r],rt[l-1],1,n,0),mx=findmx(rt[r],rt[l-1],1,n,n+1);
		// cout<<u<<" "<<l<<" "<<r<<" "<<mn<<" "<<mx<<"\n";
		if(dfn[u]<=mn&&mx<=dfn[u]+siz[u]-1)printf("%lld\n",ans=calc(u,lca(rnk[mn],rnk[mx])));
		else{
			int p=findmn(rt[r],rt[l-1],1,n,dfn[u]);
			if(p<=dfn[u]+siz[u]-1)printf("%lld\n",ans=0);
			else{
				int tp=lca(rnk[mn],rnk[mx]);
				if(dfn[tp]<=dfn[u]&&dfn[u]<=dfn[tp]+siz[tp]-1){
					int q=findmx(rt[r],rt[l-1],1,n,dfn[u]);
					int p1=lca(rnk[p],u),p2=lca(rnk[q],u);
					if(dis[p1]<dis[p2])swap(p1,p2);
					printf("%lld\n",ans=dis[u]-dis[p1]);
				}
				else printf("%lld\n",ans=calc(u,tp));
			}
		}
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