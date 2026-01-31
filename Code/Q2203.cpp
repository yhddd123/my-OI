#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=300010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
mt19937 rnd(0);
int n,q,x,y;
vector<int> e[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    for(int v:e[u])if(v!=fa[u]){
        fa[v]=u;dfs(v),siz[u]+=siz[v];
        if(siz[v]>=siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn],ed[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;ed[u]=u;
    if(!son[u])return ;dfs(son[u],lst);ed[u]=ed[son[u]];
    for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int h1[maxn],h2[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
inline pii operator*(pii u,pii v){return {1ll*u.fi*v.fi%mod,(1ll*u.fi*v.se+u.se)%mod};}
pii tree[maxn<<2];
void build(int nd,int l,int r){
	tree[nd]={0,1};
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p){
	if(l==r){
		tree[nd]={h2[rnk[l]],y};
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	tree[nd]=tree[ls]*tree[rs];
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)*query(rs,mid+1,r,ql,qr);
}
int que(int u){
	pii res=query(1,1,n,dfn[u],dfn[ed[u]]);
	// cout<<u<<" "<<res.fi<<" "<<res.se<<"\n";
	return (res.fi+res.se)%mod;
}
void add(int u){
	h2[u]=x;
	while(u){
		modif(1,1,n,dfn[u]);
		u=tp[u];
		h2[fa[u]]=1ll*h2[fa[u]]*ksm(h1[u])%mod;
		h1[u]=que(u);
		h2[fa[u]]=1ll*h2[fa[u]]*h1[u]%mod;
		u=fa[u];
	}
}
#define lb(x) (x&(-x))
struct bit1{
	int tree[maxn];
	inline void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	inline int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	inline int ask(int u){return que(dfn[u]+siz[u]-1)-que(dfn[u]);}
}t1;
int find(int u){
	if(u==1)return 0;
	int sz=t1.ask(u);
	if(2*sz<=t1.ask(fa[u]))return u;
	else u=fa[u];
	while(u){
		if(fa[tp[u]]&&2*sz>t1.ask(fa[tp[u]]))u=fa[tp[u]];
		else{
			int l=dfn[tp[u]],r=dfn[u]-1,res=dfn[u];
			while(l<=r){
				if(2*sz>t1.ask(rnk[mid]))res=mid,r=mid-1;
				else l=mid+1;
			}
			u=rnk[res];
			if(u==1)return 0;
			sz=t1.ask(u);
			if(2*sz<=t1.ask(fa[u]))return u;
			else u=fa[u];
		}
	}
	return u;
}
struct bit2{
	int tree[maxn];
	void init(){
		for(int i=1;i<=n;i++)tree[i]=1;
	}
	inline void upd(int x,int w){
		while(x<=n)tree[x]=1ll*tree[x]*w%mod,x+=lb(x);
	}
	inline int que(int x){
		int res=1;
		while(x)res=1ll*res*tree[x]%mod,x-=lb(x);
		return res;
	}
	int calc(int u){
		return 1ll*que(dfn[u]+siz[u]-1)*ksm(que(dfn[u]-1))%mod;
	}
}t2;
int f[maxn],ni[maxn];
map<int,int> mp[maxn];
pii ask[maxn];
int st[maxn],top,tmp[maxn],id[maxn];
void work(){
	x=rnd()%mod,y=rnd()%mod;
	// cout<<x<<" "<<y<<" i\n";
	q=read();n=1;
	for(int i=1;i<=q;i++){
		int op=read(),x=read();ask[i]={op,x};
		if(op==0)++n,e[x].pb(n);
	}
	dfs(1),dfs(1,1);
	build(1,1,n);add(1);
	for(int i=1;i<=n;i++)f[i]=h1[i]=1;
	t1.upd(dfn[1],1);
	t2.init(),t2.upd(dfn[1],f[1]);
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
	for(int i=1,nn=1;i<=q;i++){
		auto[o,u]=ask[i];
		if(o==0){
			u=++nn;
			t1.upd(dfn[u],1);
			top=0;while(u){
				u=find(u);
				if(!u)break ;
				st[++top]=u;
				if(id[fa[u]]&&id[fa[u]]!=u){
					t2.upd(dfn[fa[u]],ksm(f[fa[u]]));
					f[fa[u]]=1ll*f[fa[u]]*ni[mp[fa[u]][tmp[id[fa[u]]]]--]%mod;
					tmp[id[fa[u]]]=que(id[fa[u]]);
					f[fa[u]]=1ll*f[fa[u]]*(++mp[fa[u]][tmp[id[fa[u]]]])%mod;
					t2.upd(dfn[fa[u]],f[fa[u]]);
				}
				u=fa[u];
			}
			add(nn);
			// for(int i=1;i<=top;i++)cout<<st[i]<<" ";cout<<" a\n";
			for(int i=1;i<=top;i++){
				int u=st[i];
				t2.upd(dfn[fa[u]],ksm(f[fa[u]]));
				if(tmp[u]){
					f[fa[u]]=1ll*f[fa[u]]*ni[mp[fa[u]][tmp[u]]--]%mod;
				}
				tmp[u]=que(u);
				f[fa[u]]=1ll*f[fa[u]]*(++mp[fa[u]][tmp[u]])%mod;
				t2.upd(dfn[fa[u]],f[fa[u]]);
				if(!id[fa[u]]||t1.ask(u)>t1.ask(id[fa[u]]))id[fa[u]]=u;
			}
		}
		else{
			write(t2.calc(u));puts("");
		}
		// for(int u=1;u<=nn;u++)if(id[u]){
			// for(int v:e[u])if(v<=nn){
				// if(t1.ask(id[u])<t1.ask(v)){
					// cout<<nn<<"\n";
					// cout<<u<<" "<<id[u]<<" "<<v<<"\n";
					// cout<<t1.ask(id[u])<<" "<<t1.ask(v)<<"\n";
					// exit(0);
				// }
			// }
		// }
		// for(int i=1;i<=nn;i++)cout<<que(i)<<" ";cout<<"\n";
		// for(int i=1;i<=nn;i++)cout<<f[i]<<" ";cout<<"\n";
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