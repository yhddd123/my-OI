// Problem: P9329 [JOIST 2023] 两种货币 / Two Currencies
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9329
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-06 16:25:43
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,q;
vector<pii> e[maxn];
int lsh[maxn],len;
vector<int> a[maxn];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int num[maxn<<6],sum[maxn<<6],lc[maxn<<6],rc[maxn<<6],idx,tmp,rt[maxn];
void updata(int &nd,int l,int r,int p){
	if(nd<=tmp){
		int lst=nd;nd=++idx;num[nd]=num[lst],sum[nd]=sum[lst],ls=lc[lst],rs=rc[lst];
	}
	num[nd]++,sum[nd]+=lsh[p];
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
}
int quenum(int nd,int l,int r,int ql,int qr){
	if(!nd||ql>qr)return 0;
	if(l>=ql&&r<=qr)return num[nd];
	if(qr<=mid)return quenum(ls,l,mid,ql,qr);
	if(ql>mid)return quenum(rs,mid+1,r,ql,qr);
	return quenum(ls,l,mid,ql,qr)+quenum(rs,mid+1,r,ql,qr);
}
int quesum(int nd,int l,int r,int ql,int qr){
	if(!nd||ql>qr)return 0;
	if(l>=ql&&r<=qr)return sum[nd];
	if(qr<=mid)return quesum(ls,l,mid,ql,qr);
	if(ql>mid)return quesum(rs,mid+1,r,ql,qr);
	return quesum(ls,l,mid,ql,qr)+quesum(rs,mid+1,r,ql,qr);
}
int dep[maxn],dfn[maxn],tim,st[17][maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;st[0][dfn[u]=++tim]=fa;
	for(auto[v,i]:e[u])if(v!=fa){
		rt[v]=rt[u];
		tmp=idx;
		for(int w:a[i])updata(rt[v],1,len,lower_bound(lsh+1,lsh+len+1,w)-lsh);
		dfs(v,u);
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb({v,i}),e[v].pb({u,i});
	}
	for(int i=1;i<=m;i++){
		int u=read(),w=read();
		a[u].pb(w);lsh[++len]=w;
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	dfs(1,0);
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	while(q--){
		int u=read(),v=read(),x=read(),y=read(),tp=lca(u,v);
		int l=1,r=len,res=0;
		while(l<=r){
			int sum=quesum(rt[u],1,len,1,mid)+quesum(rt[v],1,len,1,mid)-2*quesum(rt[tp],1,len,1,mid);
			if(sum<=y)res=mid,l=mid+1;
			else r=mid-1;
		}
		int cnt=quenum(rt[u],1,len,1,res)+quenum(rt[v],1,len,1,res)-2*quenum(rt[tp],1,len,1,res);
		y-=quesum(rt[u],1,len,1,res)+quesum(rt[v],1,len,1,res)-2*quesum(rt[tp],1,len,1,res);
		int lst=res;
		l=res+1,r=len,res=r+1;
		while(l<=r){
			int num=quesum(rt[u],1,len,lst+1,mid)+quesum(rt[v],1,len,lst+1,mid)-2*quesum(rt[tp],1,len,lst+1,mid);
			if(num)res=mid,r=mid-1;
			else l=mid+1;
		}
		if(res!=len+1){
			int d=min(quenum(rt[u],1,len,res,res)+quenum(rt[v],1,len,res,res)-2*quenum(rt[tp],1,len,res,res),y/lsh[res]);
			cnt+=d;
		}
		cnt=num[rt[u]]+num[rt[v]]-2*num[rt[tp]]-cnt;
		printf("%lld\n",max(-1ll,x-cnt));
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