#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,m;
char c[maxn];
struct sam{
	int len[maxn],lnk[maxn];
	int a[maxn][26];
	int p=1,cur=1;
	void clr(){
		while(cur){
			len[cur]=lnk[cur]=0;
			for(int i=0;i<26;i++)a[cur][i]=0;
			cur--;
		}
		p=cur=1;
	}
	void insert(int c){
		int nd=++cur;
		len[nd]=len[p]+1;
		while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
		if(!p){lnk[p=nd]=1;return ;}
		int q=a[p][c];
		if(len[p]+1==len[q])lnk[nd]=q;
		else{
			int cl=++cur;
			len[cl]=len[p]+1;lnk[cl]=lnk[q];
			memcpy(a[cl],a[q],sizeof(a[q]));
			lnk[q]=lnk[nd]=cl;
			while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
		}
		p=nd;
	}
};
namespace sgt{
#define ls lc[nd]
#define rs rc[nd]
#define mid (l+r>>1)
	bool tree[maxn<<5];
	int lc[maxn<<5],rc[maxn<<5];
	int rt[maxn],idx;
	void updata(int &nd,int l,int r,int p){
		if(!nd)nd=++idx;
		if(l==r){tree[nd]=1;return ;}
		if(p<=mid)updata(ls,l,mid,p);
		else updata(rs,mid+1,r,p);
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
		if(!tree[nd])return 0;
		if(l>=ql&&r<=qr)return 1;
		if(ql<=mid&&query(ls,l,mid,ql,qr))return 1;
		if(qr>mid&&query(rs,mid+1,r,ql,qr))return 1;
		return 0;
	}
}
namespace sms{
	sam s;
	int head[maxn],tot;
	struct edgend{
		int nxt,to;
	}e[maxn<<1];
	void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
	void dfs(int u){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;dfs(v);
			sgt::rt[u]=sgt::merge(sgt::rt[u],sgt::rt[v],1,n);
		}
	}
	void build(char *c,int n){
		for(int i=1;i<=n;i++){
			s.insert(c[i]-'a');
			sgt::updata(sgt::rt[s.p],1,n,i);
		}
		for(int i=2;i<=s.cur;i++)add(s.lnk[i],i);
		dfs(1);
	}
	void go(int &p,int c,int &l,int u,int v){
		while(1){
			if(s.a[p][c]&&sgt::query(sgt::rt[s.a[p][c]],1,n,u+l,v)){
				p=s.a[p][c];
				l++;
				break;
			}
			if(!l)break;
			l--;
			if(l==s.len[s.lnk[p]])p=s.lnk[p];
		}
	}
}
namespace smt{
	sam s;
	int head[maxn],tot;
	struct edgend{
		int nxt,to;
	}e[maxn<<1];
	void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
	int f[maxn],ans;
	void build(char *c,int n){
		s.clr();
		for(int i=1;i<=n;i++){
			s.insert(c[i]-'a');
			f[i]=i-s.len[s.lnk[s.p]];
			ans+=f[i];
		}
	}
	void sovle(){
		scanf("%s",c+1);m=strlen(c+1);
		int u=read(),v=read();
		ans=0;build(c,m);
		int p=1,l=0;
		for(int i=1;i<=m;i++){
			sms::go(p,c[i]-'a',l,u,v);
			ans-=max(0ll,f[i]-(i-l));
		}
		printf("%lld\n",ans);
	}
}
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	sms::build(c,n);
	q=read();
	while(q--)smt::sovle();
}

bool Med;
int T;
signed main(){
//	freopen("P4770_25.in","r",stdin);
//	freopen("P4770_25.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
