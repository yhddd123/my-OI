// Problem: P7349 「MCOI-04」Dream and the Multiverse
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7349
// Memory Limit: 250 MB
// Time Limit: 8000 ms
// Written by yhm.
// Start codeing:2025-10-15 08:22:52
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long 
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
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=100100;
const int maxq=1000100;
const int inf=1e9;
bool mbe;

int n,m,q;
vector<int> e[maxn];
int d[maxn];
int id[maxn],tim;
const int B=64;
vector<pii> ask1[maxn/B],ask2[maxn/B],ask3[maxn];
ll ans[maxq];
ull f[maxn];
ll s[maxn],v[maxn];
void work(){
	n=read();m=read();
	for(int i=2;i<=n;i++){
		int p=read();
		e[p-1].pb(i-1),d[i-1]++;
	}
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u].pb(v);d[v]++;
	}
	queue<int> qq;
	for(int i=0;i<n;i++)if(!d[i])qq.push(i);
	while(!qq.empty()){
		int u=qq.front();qq.pop();id[++tim]=u;
		for(int v:e[u]){
			if(!--d[v])qq.push(v);
		}
	}
	q=read();
	auto ask=[&](int u,int v,int id){
		if(u>=64)ask1[(u>>6)-1].pb({v,id});
		if(v>=64)ask2[(v>>6)-1].pb({u,id});
		ask3[u].pb({v,id});
	};
	for(int i=1;i<=q;i++){
		int l=read()-1,r=read()-1;
		ask(r,r,i);
		if(l)ask(l-1,r,-i),ask(r,l-1,-i),ask(l-1,l-1,i);
	}
	for(int l=0,r=B-1;l<n;l+=B,r+=B){
		for(int i=0;i<n;i++)f[i]=0;
		for(int i=l;i<=r;i++)f[i]=1ull<<(i-l);
		for(int i=n;i;i--){
			int u=id[i];
			for(int v:e[u])f[u]|=f[v];
		}
		for(int i=0;i<n;i++)v[i]=(!i?0:v[i-1])+__builtin_popcountll(f[i]);
		for(int i=0;i<n;i++)s[i]+=v[i];
		for(auto[p,id]:ask1[l/B]){
			if(id>0)ans[id]+=s[p];
			else ans[-id]-=s[p];
		}
		for(int x=0;x<B;x++){
			ull S=(x+1==64?0:(1ull<<x+1))-1ull;
			for(auto[y,id]:ask3[x+l]){
				for(int i=(y>>6)<<6;i<=y;i++){
					// cout<<x<<" "<<y<<" "<<id<<" "<<i<<" "<<f[i]<<"\n";
					if(id>0)ans[id]+=__builtin_popcountll(f[i]&S);
					else ans[-id]-=__builtin_popcountll(f[i]&S);
				}
			}
		}
	}
	for(int i=0;i<n;i++)s[i]=0;
	for(int l=0,r=B-1;l<n;l+=B,r+=B){
		for(int i=0;i<n;i++)f[i]=0;
		for(int i=l;i<=r;i++)f[i]=1ull<<(i-l);
		for(int i=1;i<=n;i++){
			int u=id[i];
			for(int v:e[u])f[v]|=f[u];
		}
		for(int i=0;i<n;i++)v[i]=(!(i&(B-1))?0:v[i-1])+__builtin_popcountll(f[i]);
		for(int i=0;i<n;i++)s[i]+=v[i];
		for(auto[p,id]:ask2[l/B]){
			if(id>0)ans[id]+=s[p];
			else ans[-id]-=s[p];
		}
	}
	for(int i=1;i<=q;i++)write(ans[i]),puts("");
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