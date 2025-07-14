#include<bits/stdc++.h>
using namespace std;
const int maxn=1100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,p;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int a[maxn],col[maxn];
int dep[maxn],f[maxn],siz[maxn],wt[maxn];
void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;f[u]=fa;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[wt[u]])wt[u]=v;
	}
}
int dfn[maxn],idx,rnk[maxn],tp[maxn];
void dfs2(int u,int t){
	dfn[u]=++idx;rnk[idx]=u;tp[u]=t;
	if(!wt[u])return ;
	dfs2(wt[u],t);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f[u]||v==wt[u])continue;
		dfs2(v,v);
	}
}
int rt[maxn],cnt;
int sum[maxn],mx[maxn],ls[maxn],rs[maxn];
void push(int nd){
	sum[nd]=sum[ls[nd]]+sum[rs[nd]];
	mx[nd]=max(mx[ls[nd]],mx[rs[nd]]);
}
void updata(int &nd,int l,int r,int ql,int w){
	if(!nd)nd=++cnt;
	if(l==r){
		sum[nd]=mx[nd]=w;
		return ;
	}
	int mid=l+r>>1;
	if(ql<=mid)updata(ls[nd],l,mid,ql,w);
	else updata(rs[nd],mid+1,r,ql,w);
	push(nd);
}
int querysum(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	int mid=l+r>>1;
	if(qr<=mid)return querysum(ls[nd],l,mid,ql,qr);
	if(ql>mid)return querysum(rs[nd],mid+1,r,ql,qr);
	return querysum(ls[nd],l,mid,ql,qr)+querysum(rs[nd],mid+1,r,ql,qr);
}
int querymx(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	int mid=l+r>>1;
	if(qr<=mid)return querymx(ls[nd],l,mid,ql,qr);
	if(ql>mid)return querymx(rs[nd],mid+1,r,ql,qr);
	return max(querymx(ls[nd],l,mid,ql,qr),querymx(rs[nd],mid+1,r,ql,qr));
}
int asksum(int u,int v,int c){
	int res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res+=querysum(rt[c],1,n,dfn[tp[u]],dfn[u]);
		u=f[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	res+=querysum(rt[c],1,n,dfn[v],dfn[u]);
	return res;
}
int askmx(int u,int v,int c){
	int res=0;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		res=max(res,querymx(rt[c],1,n,dfn[tp[u]],dfn[u]));
		u=f[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	res=max(res,querymx(rt[c],1,n,dfn[v],dfn[u]));
	return res;
}
char s[3];
int l,r;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();p=read();
	for(int i=1;i<=n;i++)a[i]=read(),col[i]=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=n;i++)updata(rt[col[i]],1,n,dfn[i],a[i]);
	while(p--){
		scanf("%s",s);l=read();r=read();
		if(s[1]=='C')updata(rt[col[l]],1,n,dfn[l],0),col[l]=r,updata(rt[col[l]],1,n,dfn[l],a[l]);
		else if(s[1]=='W')a[l]=r,updata(rt[col[l]],1,n,dfn[l],a[l]);
		else if(s[1]=='S')printf("%d\n",asksum(l,r,col[l]));
		else printf("%d\n",askmx(l,r,col[l]));
	}
}
