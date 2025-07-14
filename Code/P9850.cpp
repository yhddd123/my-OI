// Problem: P9850 [ICPC2021 Nanjing R] Ancient Magic Circle in Teyvat
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9850
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-09-04 16:28:27
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=100010;
const int inf=1e18;
// static char buf[1000000],*p1=buf,*p2=buf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
bool Mbe;

ll n,m;
vector<pii> e[maxn],g[maxn];
ll d[maxn];
/*
ans=|f0-f1+f2-f3+f4-f5|
f0=C(n,4)
f1=mC(n-2,2)
f2=(n-3)(\sum C(d[i],2))+C(m,2)-(\sum C(d[i],2))
f3=(n-3)c3+(\sum C(d[i],3))+(\sum (d[u]-1)(d[v]-1))-3c3
f4=(\sum cnt[i](d[i]-2))+c4
f5=(\sum C(num[u][v],2))
*/
ll f0,f1,f2,f3,f4,f5,ans;
ll vis[maxn],cnt[maxn],num[maxn<<1];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb({v,i}),e[v].pb({u,i});
		d[u]++,d[v]++;
	}
	for(int u=1;u<=n;u++){
		for(pii v:e[u])if(d[u]>d[v.fi]||(d[u]==d[v.fi]&&u>v.fi))g[u].pb(v);
	}
	f0=(__int128)n*(n-1)/2*(n-2)/3*(n-3)/4;
	f1=m*(n-2)*(n-3)/2;
	for(int i=1;i<=n;i++)f2+=(n-3)*d[i]*(d[i]-1)/2;
	f2+=m*(m-1)/2;
	for(int i=1;i<=n;i++)f2-=d[i]*(d[i]-1)/2;
	for(int u=1;u<=n;u++){
		for(pii v:g[u])vis[v.fi]=v.se;
		for(pii v:g[u]){
			for(pii w:g[v.fi])if(vis[w.fi]){
				++f3;++cnt[u],++cnt[v.fi],++cnt[w.fi];
				++num[v.se],++num[w.se],++num[vis[w.fi]];
			}
		}
		for(pii v:g[u])vis[v.fi]=0;
	}
	f3=(n-6)*f3;
	for(int i=1;i<=n;i++)f3+=d[i]*(d[i]-1)/2*(d[i]-2)/3;
	for(int u=1;u<=n;u++){
		for(pii v:g[u])f3+=(d[u]-1)*(d[v.fi]-1);
	}
	for(int u=1;u<=n;u++){
		for(pii v:g[u]){
			for(pii w:e[v.fi]){
				if(d[u]>d[w.fi]||(d[u]==d[w.fi]&&u>w.fi))f4+=vis[w.fi]++;
			}
		}
		for(pii v:g[u]){
			for(pii w:e[v.fi])vis[w.fi]=0;
		}
	}
	for(int i=1;i<=n;i++)f4+=cnt[i]*(d[i]-2);
	for(int i=1;i<=m;i++)f5+=num[i]*(num[i]-1)/2;
	// cout<<f0<<" "<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<" "<<f5<<"\n";
	ans=abs(f0-f1+f2-f3+f4-f5);
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("P9850_1.in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}