// Problem: P9167 [省选联考 2023] 城市建造
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9167
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-03-03 16:31:19
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,k,ans;
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
vector<int> g[maxn];
int dfn[maxn],lw[maxn],idx,scct;
int st[maxn],tp;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				g[++scct].pb(st[tp]),g[st[tp]].pb(scct);
				while(st[tp--]!=v)g[scct].pb(st[tp]),g[st[tp]].pb(scct);
				g[scct].pb(u),g[u].pb(scct);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
int siz[maxn],w[maxn],sum,rt;
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int v:g[u])if(v!=fa){
		getrt(v,u);siz[u]+=siz[v];
		w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
void dfs(int u,int fa){
	siz[u]=u<=n;
	for(int v:g[u])if(v!=fa){
		dfs(v,u);siz[u]+=siz[v];
	}
	for(int i=0;i<g[u].size();i++)if(g[u][i]==fa)g[u][i]=g[u].back(),g[u].pop_back();
}
bool dfs0(int u,int d){
	if(siz[u]<d)return 0;
	int sum=1;
	for(int v:g[u]){
		bool fl=dfs0(v,d);
		if(u<=n){
			if(!fl){
				sum+=siz[v];
				if(sum>d)return 0;
			}
		}
		else{
			if(!fl)return 0;
		}
	}
	// cout<<u<<" "<<d<<" "<<sum<<"\n";
	if(u<=n)return sum==d;
	else return 1;
}
int dfs1(int u,int d){
	if(siz[u]<d)return 0;
	if(u<=n){
		int sum=1,cnt=0,mul=1,ans=0;
		for(int v:g[u]){
			int f=dfs1(v,d);
			if(!f){
				sum+=siz[v];
				if(sum>d+1)return 0;
			}
			else mul=mul*f%mod,cnt+=siz[v]==d;
		}
		if(sum>=d)ans=mul;
		if(sum==1)(ans+=cnt*mul)%=mod;
		return ans;
	}
	else{
		int f=1;
		for(int v:g[u]){
			f=f*dfs1(v,d)%mod;
			if(!f)return 0;
		}
		return f;
	}
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	scct=n;tar(1);
	// for(int i=n+1;i<=scct;i++){
		// for(int j:g[i])cout<<i<<" "<<j<<"\n";
	// }
	sum=scct;getrt(1,0);
	dfs(rt,0);
	if(!k){
		for(int i=1;i<=n/2;i++)if(n%i==0)ans+=dfs0(rt,i);
	}
	else{
		for(int i=1,lst=-1;i<=n/2;i++)if(n%i<=n/i){
			ans+=dfs1(rt,i);
			if(lst+1==i&&n%i==0)ans-=dfs0(rt,i);
			lst=i;
			// cout<<i<<" "<<ans<<"\n";
		}
	}
	printf("%lld\n",ans%mod);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}