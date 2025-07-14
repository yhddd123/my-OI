// Problem: P5537 【XR-3】系统设计
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5537
// Memory Limit: 250 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2024-07-16 14:30:38
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int maxn=500010;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0;char c=getchar();while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
inline void write(int x){static char buf[20];static int len=-1;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define put() putchar(' ')
#define endl puts("")
bool Mbe;

int n,m,q,rt,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
ll hsh[maxn],val[maxn],bas,pw[maxn];
mt19937 rnd(1);
unordered_map<ll,int> mp;
int dep[maxn];
void dfs(int u){
	mp[hsh[u]*pw[m]]=u;
	for(int i=head[u],cnt=0;i;i=e[i].nxt){
		int v=e[i].to;
		dep[v]=dep[u]+1;
		hsh[v]=hsh[u]+val[++cnt]*pw[dep[u]];
		dfs(v);
	}
}
#define lb(x) (x&(-x))
ll tree[maxn];
void upd(int x,ll w){
	while(x<=m){
		tree[x]+=w;
		x+=lb(x);
	}
}
ll que(int x){
	ll res=0;
	while(x){
		res+=tree[x];
		x-=lb(x);
	}
	return res;
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++){
		int fa=read();
		if(!fa)rt=i;
		else a[i]=fa;
	}
	for(int i=n;i;i--)if(i!=rt)add(a[i],i);
	for(int i=1;i<=m;i++)a[i]=read();
	bas=rnd();for(int i=1;i<=n;i++)val[i]=rnd();
	pw[0]=1;for(int i=1;i<=max(n,m);i++)pw[i]=pw[i-1]*bas;
	dfs(rt);
	for(int i=1;i<=m;i++)upd(i,val[a[i]]*pw[i-1]);
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),l=read(),r=read(),L=l,res=x;
			while(l<=r){
				int mid=l+r>>1;
				ll val=hsh[x]*pw[m]+(que(mid)-que(L-1))*pw[m-L+1]*pw[dep[x]];
				if(mp.find(val)!=mp.end())l=mid+1,res=mp[val];
				else r=mid-1;
			}
			write(res),endl;
		}
		else{
			int u=read(),v=read();
			upd(u,(val[v]-val[a[u]])*pw[u-1]),a[u]=v;
		}
	}
}

// \
444

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
