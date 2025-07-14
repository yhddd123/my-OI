#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int dfn[maxn],cnt,rnk[maxn],siz[maxn];
void dfs(int u,int fa){
	dfn[u]=++cnt;rnk[cnt]=u;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
}
set<int> s[maxn];
int tree[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	tree[nd]=tag[nd]=0;
	if(l==r)return ;
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
}
void push(int nd,int l,int r){
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	tree[ls]+=(mid-l+1)*tag[nd];
	tag[ls]+=tag[nd];
	tree[rs]+=(r-mid)*tag[nd];
	tag[rs]+=tag[nd];
	tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		tree[nd]+=(r-l+1)*w;
		tag[nd]+=w;
		return ;
	}
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int opt,x,c;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	dfs(1,1);
	build(1,1,n);
	while(m--){
		opt=read();
		if(opt==1){
			x=read();c=read();
			auto it=s[c].upper_bound(dfn[x]);
			if(it!=s[c].begin()){
				it--;
				if(dfn[x]>=*it&&dfn[x]<=*it+siz[rnk[*it]]-1)continue;
			}
			it=s[c].lower_bound(dfn[x]);
			while(it!=s[c].end()&&*it<=dfn[x]+siz[x]-1){
				updata(1,1,n,*it,*it+siz[rnk[*it]]-1,-1);
				s[c].erase(it);
				it=s[c].lower_bound(dfn[x]);
			}
			updata(1,1,n,dfn[x],dfn[x]+siz[x]-1,1);
//			cout<<dfn[x]<<" "<<dfn[x]+siz[x]-1<<"\n";
			s[c].insert(dfn[x]);
		}
		else{
			x=read();
			printf("%lld\n",query(1,1,n,dfn[x],dfn[x]+siz[x]-1));
//			cout<<dfn[x]<<" "<<dfn[x]+siz[x]-1<<"\n";
		}
	}
}
