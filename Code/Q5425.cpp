#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1<<22];
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
static int opos=0;
inline void flush_out(){fwrite(obuf,1,opos,stdout);opos=0;}
inline void pc(char c){if(opos == (1<<22))flush_out();obuf[opos++]=c;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)pc('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)pc(buf[len--]+48);}
const int maxn=250010;
const int inf=1e9;
bool mbe;

int n,m;ll ans[maxn];
vector<int> e[maxn];
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
bool vis[maxn];
vector<pii> mdf[maxn];
mt19937 rnd(time(0));
int val[2],bas,pw[maxn];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<6],lc[maxn<<6],rc[maxn<<6];
int rt[maxn],idx,tmp;
void modif(int &nd,int l,int r,int p,int w){
	if(nd<=tmp){int lst=nd;nd=++idx,ls=lc[lst],rs=rc[lst];}
	if(l==r){tree[nd]=val[w];return ;}
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	tree[nd]=(1ll*tree[ls]*pw[r-mid]+tree[rs])%mod;
}
bool cmp(int u,int v,int l,int r){
	if(tree[u]==tree[v])return 0;
	if(l==r)return tree[u]<tree[v];
	if(tree[lc[u]]!=tree[lc[v]])return cmp(lc[u],lc[v],l,mid);
	else return cmp(rc[u],rc[v],mid+1,r);
}
int find(int u,int v,int l,int r){
	if(tree[u]==tree[v])return r+1;
	if(l==r)return l;
	if(tree[lc[u]]!=tree[lc[v]])return find(lc[u],lc[v],l,mid);
	else return find(rc[u],rc[v],mid+1,r);
}
int id[maxn];
vector<pii> edge[maxn];
void work(){
	n=read()-1;m=read();
	int cnt0=n,cnt1=0;
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n+1;i++)f[i]=i;
	for(int i=1;i<=n;i++)mdf[i].clear();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();if(l>r)swap(l,r);
		for(int p=fd(l);p<r;){
			if(vis[p]){
				cnt1--;
				p=f[p]=fd(p+1);
			}
			else{
				vis[p]=1;
				cnt0--,cnt1++;
				p=fd(p+1);
			}
		}
		ans[i]=1ll*cnt0*(n+i-cnt0)+cnt1;
		if(l>1)mdf[1].pb({i,0});
		mdf[l].pb({i,1});
		if(r<=n)mdf[r].pb({i,0});
	}
	bas=rnd()%mod;
	val[0]=rnd()%bas,val[1]=rnd()%bas;
	if(val[0]>val[1])swap(val[0],val[1]);
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=1ll*pw[i-1]*bas%mod;
	while(idx)tree[idx]=lc[idx]=rc[idx]=0,idx--;
	for(int i=1;i<=n;i++){
		rt[i]=rt[i-1];tmp=idx;
		for(auto[p,w]:mdf[i])modif(rt[i],1,m,p,w);
	}
	for(int i=1;i<=n;i++)id[i]=i;
	stable_sort(id+1,id+n+1,[&](int u,int v){return cmp(rt[u],rt[v],1,m);});
	// for(int i=1;i<=n;i++)cout<<id[i]<<" ";cout<<"\n";
	for(int i=1;i<=m;i++)edge[i].clear();
	for(int i=1;i<n;i++){
		int p=find(rt[id[i]],rt[id[i+1]],1,m);
		edge[p-1].pb({id[i],id[i+1]});
	}
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	ll res=0;
	for(int i=m;i;i--){
		for(auto[u,v]:edge[i]){
			int uu=fd(u),vv=fd(v);
			res-=1ll*siz[uu]*(siz[uu]-1)/2+1ll*siz[vv]*(siz[vv]-1)/2;
			f[uu]=vv,siz[vv]+=siz[uu];
			res+=1ll*siz[vv]*(siz[vv]-1)/2;
		}
		ans[i]+=res;
	}
	for(int i=1;i<=m;i++)write(ans[i]),pc('\n');
	flush_out();
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=read();
	while(T--)work();
}