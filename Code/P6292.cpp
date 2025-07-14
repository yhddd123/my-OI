#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
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

int n,q;
char c[maxn];
struct ask{
	int l,r,id;
}p[maxn];
bool cmp(ask u,ask v){return u.r<v.r;}
int ans[maxn];
struct nd{
	int l,r,p;
};
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	nd tree[maxn<<2];
	int tag[maxn<<2];
	nd merge(nd u,nd v,int pos){
		nd nw;
		nw.l=u.l,nw.r=v.r;
		if(v.p)nw.p=v.p;
		else if(u.r!=v.l)nw.p=pos;
		else nw.p=u.p;
		return nw;
	}
	void push(int nd){
		tree[ls]={tag[nd],tag[nd],0};tag[ls]=tag[nd];
		tree[rs]={tag[nd],tag[nd],0};tag[rs]=tag[nd];
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){
			tree[nd]={w,w,0};tag[nd]=w;
			return ;
		}
		if(tag[nd])push(nd);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=merge(tree[ls],tree[rs],mid);
	}
	nd query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tree[nd];
		if(tag[nd])push(nd);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr),mid);
	}
#undef mid
}
struct bit{
	int c[maxn];
	int lowbit(int x){return x&(-x);}
	void add(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=lowbit(x);
		}
	}
	void updata(int l,int r,int w){add(l,w),add(r+1,-w);}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}b0,b1;
struct add{
	void updata(int l,int r,int p,int c){
		if(p!=r)b0.updata(1,p-r,c*(r-l+1));
		b0.updata(p-r+1,p-l+1,c*(p-l+2));
		b1.updata(p-r+1,p-l+1,-c);
	}
	int query(int p){return b0.query(p)+b1.query(p)*p;}
}con;
namespace sam{
	int len[maxn],fa[maxn];
	int a[maxn][26];
	int p=1,cur=1;
	void insert(int c){
		int nd=++cur;
		len[nd]=len[p]+1;
		while(p&&!a[p][c])a[p][c]=nd,p=fa[p];
		if(!p){fa[p=nd]=1;return ;}
		int q=a[p][c];
		if(len[p]+1==len[q])fa[nd]=q;
		else{
			int cl=++cur;
			len[cl]=len[p]+1;fa[cl]=fa[q];
			memcpy(a[cl],a[q],sizeof(a[q]));
			fa[nd]=fa[q]=cl;
			while(p&&a[p][c]==q)a[p][c]=cl,p=fa[p];
		}
		p=nd;
	}
	int head[maxn],tot;
	struct edgend{
		int nxt,to;
	}e[maxn];
	void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
	int dep[maxn],siz[maxn],son[maxn];
	void dfs1(int u){
		dep[u]=dep[fa[u]]+1;siz[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			dfs1(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])son[u]=v;
		}
	}
	int dfn[maxn],rnk[maxn],idx,tp[maxn];
	void dfs2(int u,int lst){
		dfn[u]=++idx;rnk[idx]=u;tp[u]=lst;
		if(!son[u])return ;
		dfs2(son[u],lst);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==son[u])continue;
			dfs2(v,v);
		}
	}
	void build(char *c,int m){
		for(int i=1;i<=m;i++)insert(c[i]-'a');
		for(int i=2;i<=cur;i++)add(fa[i],i);
		dfs1(1);dfs2(1,1);
	}
	int pos=1;
	void updata(int p,int c){
		pos=a[pos][c];
		int u=pos;
		while(u){
			int uu=u;
			while(1){
				nd res=sgt::query(1,1,cur,dfn[tp[u]],dfn[u]);
				int v;
				if(!res.p)v=tp[u];
				else v=rnk[res.p+1];
				if(res.r)con.updata(len[fa[v]]+1,len[u],res.r,-1);
				con.updata(len[fa[v]]+1,len[u],p,1);
				if(v==tp[u])break;
				else u=fa[v];
			}
			sgt::updata(1,1,cur,dfn[tp[uu]],dfn[uu],p);
			u=fa[tp[u]];
		}
	}
}
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	sam::build(c,n);
	q=read();
	for(int i=1;i<=q;i++)p[i]={read(),read(),i};
	sort(p+1,p+q+1,cmp);
	for(int i=1,j=1;i<=n;i++){
		sam::updata(i,c[i]-'a');
		while(p[j].r==i){
			ans[p[j].id]=con.query(p[j].l);
			j++;
		}
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

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
