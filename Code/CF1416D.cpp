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
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m,q,a[maxn];
pii ask[maxn],edge[maxn];
vector<int> e[maxn];int idx;
int tim[maxn];
bool vis[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int in[maxn],out[maxn],times,rnk[maxn];
int to[maxn][19];
void dfs(int u){
	if(u<=n)in[u]=++times,rnk[times]=u;
	else in[u]=times+1;
	for(int i=1;i<=18;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int v:e[u]){
		to[v][0]=u;dfs(v);
	}
	out[u]=times;
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii mx[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mx[nd]={a[rnk[l]],l};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mx[nd]=max(mx[ls],mx[rs]);
}
void modif(int nd,int l,int r,int p){
	if(l==r){mx[nd]={0,l};return ;}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	mx[nd]=max(mx[ls],mx[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mx[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)edge[i]={read(),read()};
	for(int i=1;i<=q;i++){
		int op=read(),u=read();
		if(op==2)vis[u]=1;
		ask[i]={op,u};
	}
	for(int i=1;i<=n;i++)f[i]=i;int idx=n;
	for(int i=1;i<=n;i++)tim[i]=q+1;
	for(int i=1;i<=m;i++)if(!vis[i]){
		auto[u,v]=edge[i];
		u=fd(u),v=fd(v);
		if(u!=v){
			++idx;f[idx]=idx;e[idx].pb(u),e[idx].pb(v);
			f[u]=f[v]=idx;tim[idx]=q+1;
		}
	}
	for(int i=q;i;i--){
		auto[op,id]=ask[i];
		if(op==2){
			auto[u,v]=edge[id];
			u=fd(u),v=fd(v);
			if(u!=v){
				++idx,f[idx]=idx;e[idx].pb(u),e[idx].pb(v);
				f[u]=f[v]=idx;tim[idx]=i;
			}
		}
	}
	for(int i=idx;i;i--)if(f[i]==i)dfs(i);
	// for(int i=1;i<=idx;i++)cout<<to[i][0]<<" ";cout<<"\n";
	build(1,1,n);
	for(int i=1;i<=q;i++){
		auto[op,u]=ask[i];
		if(op==1){
			for(int j=18;~j;j--)if(tim[to[u][j]]>=i)u=to[u][j];
			// cout<<u<<" "<<tim[u]<<"\n";
			pii mx=query(1,1,n,in[u],out[u]);
			// cout<<mx.fi<<" "<<mx.se<<"\n";
			printf("%d\n",mx.fi);
			modif(1,1,n,mx.se);
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