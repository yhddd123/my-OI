#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
char c[maxn];
namespace sgt{
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
	bool tree[maxn<<5];
	int lc[maxn<<5],rc[maxn<<5];
	int rt[maxn],idx;
	void updata(int &nd,int l,int r,int p,int w){
		if(!nd)nd=++idx;
		if(l==r){tree[nd]=w;return ;}
		if(p<=mid)updata(ls,l,mid,p,w);
		else updata(rs,mid+1,r,p,w);
		tree[nd]=tree[ls]|tree[rs];
	}
	int merge(int u,int v,int l,int r){
		if(!u||!v)return u|v;
		int nd=++idx;
		if(l==r){tree[nd]=tree[u]|tree[v];return nd;}
		ls=merge(lc[u],lc[v],l,mid);
		rs=merge(rc[u],rc[v],mid+1,r);
		tree[nd]=tree[ls]|tree[rs];
		return nd;
	}
	bool query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tree[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return query(ls,l,mid,ql,qr)|query(rs,mid+1,r,ql,qr);
	}
#undef mid
}
struct sam{
	int len[maxn],lnk[maxn];
	int a[maxn][26];
	int p=1,cur=1;
	int ed[maxn];
	void insert(int c){
		int nd=++cur;
		len[nd]=len[p]+1;
		sgt::updata(sgt::rt[nd],1,n,len[nd],1);
		while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
		if(!p){lnk[p=nd]=1;return ;}
		int q=a[p][c];
		if(len[p]+1==len[q])lnk[nd]=q;
		else{
			int cl=++cur;
			len[cl]=len[p]+1;lnk[cl]=lnk[q];
			memcpy(a[cl],a[q],sizeof(a[q]));
			lnk[nd]=lnk[q]=cl;
			while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
		}
		p=nd;
	}
	int head[maxn],tot;
	struct edgend{
		int nxt,to;
	}e[maxn<<1];
	void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
	int f[maxn][19];
	void dfs(int u){
		for(int i=1;i<19;i++)f[u][i]=f[f[u][i-1]][i-1];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			f[v][0]=u;dfs(v);
			sgt::rt[u]=sgt::merge(sgt::rt[u],sgt::rt[v],1,n);
		}
	}
	void build(char *c,int n){
		for(int i=1;i<=n;i++)insert(c[i]-'a');
		for(int i=1,nd=1;i<=n;i++){
			nd=a[nd][c[i]-'a'];
			ed[i]=nd;
		}
		for(int i=2;i<=cur;i++)add(lnk[i],i);
		dfs(1);
	}
	int find(int l,int r){
		int res=ed[r];
//		cerr<<res<<"\n";
		for(int i=18;~i;i--)if(f[res][i]&&len[f[res][i]]>=r-l+1)res=f[res][i];
		return res;
	}
}s;
bool check(int a,int b,int l,int r){
	int pos=s.find(l,r);
//	cerr<<r-l+1<<" "<<pos<<" "<<a+r-l<<" "<<b<<"\n";
	return sgt::query(sgt::rt[pos],1,n,a+r-l,b);
}
void work(){
	n=read();m=read();
	scanf("%s",c+1);
	s.build(c,n);
	while(m--){
		int a=read(),b=read(),c=read(),d=read();
		int l=1,r=min(b-a+1,d-c+1),ans=0;
		while(l<=r){
			int mid=l+r>>1;
//			cout<<l<<" "<<r<<" "<<mid<<"\n";
			if(check(a,b,c,c+mid-1))l=mid+1,ans=mid;
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
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
