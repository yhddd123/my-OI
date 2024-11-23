// Problem: #191. 无向图四元环计数
// Contest: LibreOJ
// URL: https://loj.ac/p/191
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-04 16:38:03
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

int n,m;
int d[maxn],cnt[maxn],ans;
vector<int> e[maxn],g[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
		d[u]++,d[v]++;
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u]){
			if(d[u]>d[v]||(d[u]==d[v]&&u>v))g[u].push_back(v);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j:g[i]){
			// cout<<i<<" "<<j<<"\n";
			for(int k:e[j])if(d[i]>d[k]||(d[i]==d[k]&&i>k)){
				ans+=cnt[k]++;
				// cout<<i<<" "<<j<<" "<<k<<"\n";
			}
		}
		for(int j:g[i]){
			for(int k:e[j])cnt[k]=0;
		}
	}
	printf("%lld\n",ans);
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
