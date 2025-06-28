// Problem: P10181 龙逐千灯幻
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10181
// Memory Limit: 128 MB
// Time Limit: 1200 ms
// Written by yhm.
// Start codeing:2025-05-27 21:37:57
// 
// Powered by CP Editor (https://cpeditor.org)

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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
uint64_t PRG_state;
uint64_t get_number(){
    PRG_state ^= PRG_state << 13;
    PRG_state ^= PRG_state >> 7;
    PRG_state ^= PRG_state << 17;
    return PRG_state;
}
int readW(int l,int r){
	return get_number()%(r-l+1)+l;
}
const int maxn=100010;
const int inf=1e9;
const int B=100;
bool mbe;

int n,q,lim,a[maxn];ll ans;
int pre[maxn],lst[maxn];
struct Dsint{
	int val[maxn],vmn;
	int pre[maxn],ed;
	int f[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void build(){
		for(int i=1;i<=n;i++)f[i]=i;ed=0;vmn=inf;
	}
	void insert(int p,int w){
		while(ed&&w>=vmn){
			vmn=vmn+val[pre[ed]];
			f[fd(ed)]=p;
			ed=pre[ed];
		}
		pre[p]=ed,val[ed]=vmn-w,vmn=w;
		ed=p;
	}
	int quemx(){return inf-val[0];}
	void upd(int p,int v){
		p=fd(p);
		int pp=pre[p];int w=-v;w=w+val[pp];
		while(pp&&w<=0){
			f[fd(pp)]=p;
			pp=pre[pp];
			w=w+val[pp];
		}
		pre[p]=pp,val[pp]=w;
		vmn+=v;
	}
}ds1;
pii operator+(pii u,pii v){return {u.fi+v.fi,u.se+v.se};}
pii operator-(pii u,pii v){return {u.fi-v.fi,u.se-v.se};}
struct Dspii{
	pii val[maxn],vmn;
	int pre[maxn],ed;
	int f[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void build(){
		for(int i=1;i<=n;i++)f[i]=i;ed=0;vmn={inf,0};
	}
	void insert(int p,pii w){
		while(ed&&w>=vmn){
			vmn=vmn+val[pre[ed]];
			f[fd(ed)]=p;
			ed=pre[ed];
		}
		pre[p]=ed,val[ed]=vmn-w,vmn=w;
		ed=p;
	}
	pii quemx(){
		pii res={inf,0};
		res=res-val[0];
		return res;
	}
	void upd(int p,int v){
		p=fd(p);
		int pp=pre[p];pii w={-v,0};w=w+val[pp];
		while(pp&&w<=make_pair(0,0)){
			f[fd(pp)]=p;
			pp=pre[pp];
			w=w+val[pp];
		}
		pre[p]=pp,val[pp]=w;
		vmn.fi+=v;
	}
}ds2;
vector<pii> que1[maxn],que2[maxn];
int f[maxn],g[maxn];
void calc1(int k){
	ds1.build();ds1.insert(1,0);
	for(int i=1;i<=n;i++){
		ds1.upd(lst[i]+1,1);
		f[i]=ds1.quemx();
		if(k<=i&&i<n)ds1.insert(i+1,g[i]);
	}
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
}
pii dp[maxn],dp1[maxn];
void calc2(int n,int c){
	ds2.build();ds2.insert(1,{0,0});
	for(int i=1;i<=n;i++){
		ds2.upd(lst[i]+1,1);
		dp[i]=ds2.quemx();
		dp[i].fi-=c,dp[i].se++;
		if(i<n)ds2.insert(i+1,dp[i]);
	}
}
// mt19937 rnd(1);
void work(){
	n=read();q=read();read();PRG_state=read(),lim=read();
	for(int i=1;i<=n;i++)a[i]=read();
	// for(int i=1;i<=n;i++)a[i]=rnd()%n+1;
	for(int i=1;i<=n;i++)lst[i]=pre[a[i]],pre[a[i]]=i;
	for(int i=1;i<=q;i++){
		int x=readW(lim,n),k=readW(1,x),v=readW(0,1e7);
		if(k<=B)que1[k].pb({x,v});
		else que2[x].pb({k,v});
	}
	for(int k=1;k<=B;k++){
		calc1(k-1);
		for(auto[x,v]:que1[k])ans^=1ll*f[x]*v;
		for(int i=k;i<=n;i++)g[i]=f[i];
	}
	for(int i=1;i<=n;i++)sort(que2[i].begin(),que2[i].end());
	for(int c=0;c<=n/B+1;c++){
		calc2(n,c);
		bool fl=0;
		for(int i=1;i<=n;i++){
			while(que2[i].size()){
				auto[k,v]=que2[i].back();
				if(dp[i].se<k){
					que2[i].pop_back();
					ans^=1ll*(dp1[i].fi+k*(c-1))*v;
				}
				else break;
			}
			fl|=que2[i].size();
		}
		if(!fl)break;
		for(int i=1;i<=n;i++)dp1[i]=dp[i];
	}
	printf("%lld\n",ans);
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