#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=600010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans;
struct bit{
	int c[maxn];
	int lowbit(int x){return x&(-x);}
	void add(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=lowbit(x);
		}
	}
	int ask(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
	int query(int l,int r){
		if(l<1)l=1;
		if(r>n)r=n;
		if(l>r)return 0;
		return ask(r)-ask(l-1);
	}
}b0,b1;
namespace sam{
	int len[maxn],fa[maxn];
	map<int,int> ch[maxn];
	int p=1,cur=1;
	int id[maxn];
	void insert(int c){
		int nd=++cur;
		len[nd]=len[p]+1;
		while(p&&!ch[p][c])ch[p][c]=nd,p=fa[p];
		if(!p){fa[p=nd]=1;return ;}
		int q=ch[p][c];
		if(len[p]+1==len[q])fa[nd]=q;
		else{
			int cl=++cur;
			len[cl]=len[p]+1;fa[cl]=fa[q];
			ch[cl]=ch[q];
			fa[nd]=fa[q]=cl;
			while(p&&ch[p][c]==q)ch[p][c]=cl,p=fa[p];
		}
		p=nd;
	}
	int head[maxn],tot;
	struct edgend{
		int nxt,to;
	}e[maxn];
	void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
	int dfn[maxn],idx,rnk[maxn];
	int siz[maxn],son[maxn];
	void dfs(int u){
		rnk[dfn[u]=++idx]=u;siz[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;dfs(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])son[u]=v;
		}
	}
	void build(int *c,int m){
		for(int i=1;i<=m;i++)id[cur+1]=i,insert(c[i]);
		for(int i=2;i<=cur;i++)add(fa[i],i);
		dfs(1);
	}
	void upd(int x,int val){
		b0.add(x,val);b1.add(x,x*val);
	}
	void dfs1(int u,bool fl){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v!=son[u])dfs1(v,0);
		}
		if(son[u])dfs1(son[u],1);
		int l=len[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==son[u])continue;
			for(int j=dfn[v];j<=dfn[v]+siz[v]-1;j++){
				int p=id[rnk[j]];
				if(!p)continue;
				ans+=b1.query(p+2,p+l+1)-b0.query(p+2,p+l+1)*(p+1)+b0.query(p+l+2,n)*l;
				ans+=b0.query(p-l-1,p-2)*(p-1)-b1.query(p-l-1,p-2)+b0.query(1,p-l-2)*l;
			}
			for(int j=dfn[v];j<=dfn[v]+siz[v]-1;j++){
				int p=id[rnk[j]];
				if(!p)continue;
				upd(p,1);
			}
		}
		int p=id[u];
		if(p){
			ans+=b1.query(p+2,p+l+1)-b0.query(p+2,p+l+1)*(p+1)+b0.query(p+l+2,n)*l;
			ans+=b0.query(p-l-1,p-2)*(p-1)-b1.query(p-l-1,p-2)+b0.query(1,p-l-2)*l;
			upd(p,1);
		}
		if(!fl){
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				for(int j=dfn[v];j<=dfn[v]+siz[v]-1;j++){
					int p=id[rnk[j]];
					if(!p)continue;
					upd(p,-1);
				}
			}
			int p=id[u];
			if(p)upd(p,-1);
		}
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]=a[i+1]-a[i];
	n--;
	sam::build(a,n);
	sam::dfs1(1,1);
	printf("%lld\n",ans+n*(n+1)/2);
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
