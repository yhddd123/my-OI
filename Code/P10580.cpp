// Problem: P10580 [蓝桥杯 2024 国 A] gcd 与 lcm
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10580
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-26 12:49:29
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,x,y;
vector<pii> p;
vector<int>id;
map<int,int> mp;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void dfs(int dep,int mul){
	if(dep==p.size()){
		id.pb(mul);
		return ;
	}
	for(int i=0;i<=p[dep].se;i++){
		dfs(dep+1,mul);
		mul=mul*p[dep].fi;
	}
}
unordered_map<int,int> dp;
int dfs(int u){
	if(u==1)return dp[u]=1;
	if(dp[u])return dp[u];
	id.clear();dfs(0,1);
	vector<int> idd;swap(idd,id);
	int res=1;for(pii i:p)res=res*(i.se+1);
	dp[u]=ksm(res,n);
	// cout<<u<<" "<<res<<" "<<dp[u]<<"\n";
	// for(pii i:p)cout<<i.fi<<" "<<i.se<<"\n";
	// for(int i:id)cout<<i<<" ";cout<<"\n";
	for(int v:idd)if(v!=1){
		vector<pii> tmp=p;
		int x=v,res=1;
		for(int i=0;i<p.size();i++)if(x%p[i].fi==0){
			int cnt=0;
			while(x%p[i].fi==0)x/=p[i].fi,++cnt;
			p[i].se-=cnt;
			res=res*(cnt+1)%mod;
		}
		(dp[u]+=mod-res*dfs(u/v)%mod)%=mod;
		// if(u==12)cout<<u<<" "<<v<<" "<<res<<" "<<dp[u/v]<<"\n";
		p=tmp;tmp.clear();
	}
	idd.clear();
	// cout<<u<<" "<<dp[u]<<"\n";
	return dp[u];
}
void work(){
	x=read(),y=read();n=read();
	if(y%x){
		puts("0");
		return ;
	}
	y/=x;p.clear();
	x=y;
	for(int i=2;i*i<=x;i++)if(x%i==0){
		int cnt=0;
		while(x%i==0)x/=i,++cnt;
		p.pb({i,cnt});
	}
	if(x>1)p.pb({x,1});
	dp.clear();
	printf("%lld\n",dfs(y));
	// cout<<dp.size()<<"\n";
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("totoro.in","r",stdin);
	// freopen("totoro.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}