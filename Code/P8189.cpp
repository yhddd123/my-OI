// Problem: P8189 [USACO22FEB] Redistributing Gifts G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8189
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=18;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,a[maxn][maxn],e[maxn][maxn];
int f[1<<maxn][maxn],g[1<<maxn],dp[1<<maxn];
string s;
map<string,int> mp;

void work(){
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)cin>>a[i][j],a[i][j]--;
		for(int j=0;j<n;j++){
			e[i][a[i][j]]=1;
			if(a[i][j]==i)break;
		}
	}
	for(int i=0;i<n;i++)f[1<<i][i]=1;
	for(int s=1;s<(1<<n);s++){
		int x=log2(s&(-s));
		for(int i=0;i<n;i++)if(f[s][i]){
			for(int j=x;j<n;j++)if(e[i][j]){
				if(j==x)g[s]+=f[s][i];
				if(!(s&(1<<j)))f[s|(1<<j)][j]+=f[s][i];
			}
		}
	}
	dp[0]=1;
	for(int s=1;s<(1<<n);s++){
		int x=log2(s&(-s));
		for(int t=s;t;t=(t-1)&s)if(t&(1<<x)){
			dp[s]+=g[t]*dp[s^t];
		}
	}
	cin>>q;
	while(q--){
		cin>>s;if(mp[s]){cout<<mp[s]<<"\n";continue;}
		int v=0,ans=0;
		for(int i=0;i<n;i++)if(s[i]=='H')v|=(1<<i);
		ans=dp[v]*dp[((1<<n)-1)^v];
		cout<<ans<<"\n",mp[s]=ans;
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
