// Problem: P13758 【MX-X17-T7】夏终
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13758
// Memory Limit: 512 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2026-01-13 16:04:26
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
const int inf=2e15;
bool mbe;

int n,m,q,a[maxn];
int ff[maxn],hd[maxn],ed[maxn],nxt[maxn],fr[maxn],val[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int id[maxn],tmp[maxn];
int f[maxn][2];
void work(){
	n=read();m=read();q=read();a[0]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	vector<tuple<int,int,int>> edge;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		edge.pb({w,u,v});
	}
	sort(edge.begin(),edge.end());
	for(int i=1;i<=n;i++)ff[i]=i,hd[i]=ed[i]=i;
	for(auto[w,u,v]:edge){
		u=fd(u),v=fd(v);
		if(u==v)continue;
		ff[u]=v;
		nxt[ed[u]]=hd[v],fr[hd[v]]=ed[u],val[hd[v]]=w;
		hd[v]=hd[u];
	}
	for(int i=1,j=0;i<=n;i++)if(!fr[i]){
		int x=i;val[i]=inf;
		while(x)id[x]=++j,x=nxt[x];
	}
	for(int i=1;i<=n;i++)tmp[id[i]]=a[i];
	for(int i=1;i<=n;i++)a[i]=tmp[i];
	for(int i=1;i<=n;i++)tmp[id[i]]=val[i];
	for(int i=1;i<=n;i++)val[i]=tmp[i];
	multiset<int> s;
	for(int i=1;i<=n;i++)s.insert(a[i]);
	while(q--){
		int x=id[read()],y=read();
		if(x)s.erase(s.find(a[x]));
		a[x]=y;
		if(x)s.insert(a[x]);
		int mn=*s.begin();
		mems(f,0x3f);
		f[0][1]=0;
		for(int i=1;i<=n;i++){
			f[i][0]=min({inf,f[i-1][1]+(mn+a[0]),f[i-1][0]+val[i]});
			f[i][1]=min({inf,f[i-1][1]+a[i]+(mn+a[0]),f[i-1][0]+val[i]+a[i],f[i-1][1]+val[i]});
		}
		printf("%lld\n",f[n][1]-2*mn-a[0]);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	read();T=1;
	while(T--)work();
}