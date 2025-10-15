// Problem: F. Odd Queries on Odd Array
// Contest: Codeforces - Codeforces Round 1057 (Div. 2)
// URL: https://codeforces.com/contest/2153/problem/F
// Memory Limit: 1024 MB
// Time Limit: 10000 ms
// Written by yhm.
// Start codeing:2025-10-13 16:22:11
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int p1[maxn],p2[maxn];
int st[maxn],tp;
vector<int> e[maxn];
int pre[maxn],suf[maxn],t[maxn],ans;
void upd(int p){
	t[p]^=1;
	ans+=(2*t[p]-1)*p;
}
int f[maxn];
int num[maxn],sum[maxn];
int to[maxn][20],dep[maxn];
int out[maxn],fr[maxn];
void dfs(int u){
	dep[u]=dep[to[u][0]]+1;
	for(int j=1;j<20;j++)to[u][j]=to[to[u][j-1]][j-1];
	out[u]=u;f[u]=0;
	for(int v:e[u]){
		to[v][0]=u;dfs(v);f[u]+=f[v];
		out[u]=max(out[u],out[v]);
	}
	int lst=0;for(int v:e[u]){
		fr[v]=lst;
		num[v]=num[lst]+(a[u]==a[v]);
		sum[v]=sum[lst]+f[v];
		lst=v;
	}
	if(p1[a[u]]==u)f[u]+=((num[lst]+1)&1)*a[u];
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int j=19;~j;j--)if(dep[to[u][j]]>=dep[v])u=to[u][j];
	if(u==v)return u;
	for(int j=19;~j;j--)if(to[u][j]!=to[v][j])u=to[u][j],v=to[v][j];
	return to[u][0];
}
int kth(int u,int k){
	for(int i=19;~i;i--)if(k&(1<<i))u=to[u][i];
	return u;
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)p1[i]=p2[i]=0;
	for(int i=1;i<=n;i++){
		if(!p1[a[i]])p1[a[i]]=i;
		p2[a[i]]=i;
	}
	for(int i=0;i<=n;i++)e[i].clear();
	tp=0;for(int i=1;i<=n;i++){
		e[st[tp]].pb(i);
		if(p1[a[i]]==i)st[++tp]=i;
		if(p2[a[i]]==i)tp--;
	}
	for(int i=1;i<=n;i++)t[i]=0;ans=0;
	for(int i=1;i<=n;i++){
		upd(a[i]);
		pre[i]=ans;
	}
	for(int i=1;i<=n;i++)t[i]=0;ans=0;
	for(int i=n;i;i--){
		upd(a[i]);
		suf[i]=ans;
	}
	dfs(0);
	ans=0;while(q--){
		// puts("");
		int x=(read()-1+ans)%n+1,y=(read()-1+ans)%n+1;ans=0;
		// cout<<x<<" "<<y<<"\n";
		int l=min(x,y),r=max(x,y);
		if(l==r){printf("%lld ",ans=a[l]);continue ;}
		int tp=lca(l,r),l1,r1;
		if(l==tp)l1=0;
		else{
			l1=kth(l,dep[l]-dep[tp]-1);
			if(a[l1]!=a[tp])ans+=suf[l]-suf[out[l1]+1];
		}
		r1=kth(r,dep[r]-dep[tp]-1);
		ans+=pre[r]-pre[a[tp]!=a[r1]?r1-1:r1];
		// cout<<tp<<" "<<l1<<" "<<r1<<" "<<ans<<"\n";
		if((num[r1]-num[fr[l1]]+(l==tp))&1)ans+=a[tp];
		ans+=sum[fr[r1]]-sum[l1];
		printf("%lld ",ans);
	}
	puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}