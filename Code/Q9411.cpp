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
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,a[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int tree[maxn<<6][2],siz[maxn<<6],idx=1;
void insert(int x){
	int nd=1;
	for(int i=59;~i;i--){
		int v=(x>>i)&1;
		if(!tree[nd][v])tree[nd][v]=++idx;
		nd=tree[nd][v];++siz[nd];
	}
}
vector<int> dp[maxn<<6];
void dfs(int nd,int dep){
	dp[nd].resize(siz[nd]+1);
	if(dep==-1){
		// cout<<nd<<" "<<dep<<" "<<siz[nd]<<"\n";
		for(int i=1;i<=siz[nd];i++)dp[nd][i]=0;
		return ;
	}
	if(tree[nd][0])dfs(tree[nd][0],dep-1);
	if(tree[nd][1])dfs(tree[nd][1],dep-1);
	int pw=(1ll<<dep)%mod;
	for(int i=1;i<=siz[nd];i++){
		if(siz[tree[nd][0]]>=i)inc(dp[nd][i],dp[tree[nd][0]][i]);
		else (dp[nd][i]+=dp[tree[nd][1]][i-siz[tree[nd][0]]]+pw*pw)%=mod;
		if(siz[tree[nd][1]]>=i)inc(dp[nd][i],dp[tree[nd][1]][i]);
		else (dp[nd][i]+=dp[tree[nd][0]][i-siz[tree[nd][1]]]+pw*pw)%=mod;
	}
}
int calc(int x,int k){
	int nd=1,res=0,sum=0;
	for(int i=59;~i;i--){
		int v=(x>>i)&1,pw=(1ll<<i)%mod;
		if(v){
			if(siz[tree[nd][0]]>=k)(res+=pw*sum+dp[tree[nd][0]][k])%=mod;
			else (res+=(sum+pw)*pw+dp[tree[nd][1]][k-siz[tree[nd][0]]])%=mod;
		}
		if(siz[tree[nd][v]]>=k)nd=tree[nd][v];
		else{
			inc(sum,pw);
			k-=siz[tree[nd][v]];
			nd=tree[nd][v^1];
		}
	}
	inc(res,sum);
	return res;
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),insert(a[i]);
	dfs(1,59);
	while(q--){
		int l=read(),r=read(),k=read();
		printf("%lld\n",(calc(r,k)+mod-(l?calc(l-1,k):mod))%mod);
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
