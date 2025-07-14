// Problem: P3429 [POI2005] DWA-Two Parties
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3429
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-05 21:15:14
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
const int maxn=210;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
bitset<maxn> a[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		int k=read();
		if(k&1){
			for(int j=1;j<=k;j++){
				int x=read();
				a[i][x]=1;
			}
			a[i][i]=1,a[i][n+1]=1;
		}
		else{
			for(int j=1;j<=k;j++){
				int x=read();
				a[i][x]=1;
			}
		}
	}
	int pos=1;
	for(int i=1;i<=n;i++){
		if(!a[pos][i]){
			for(int j=pos+1;j<=n;j++)if(a[j][i]){swap(a[pos],a[j]);break;}
		}
		if(!a[pos][i])continue;
		for(int j=1;j<=n;j++)if(pos!=j)a[j]^=a[pos];
		pos++;
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n+1;j++)cout<<a[i][j]<<" ";cout<<"\n";
	// }
	for(int i=pos;i<=n;i++)if(a[i][n+1]){puts("Impossible");return ;}
	vector<int> ans;
	for(int i=1;i<=n;i++)if(a[i][i]&&a[i][n+1])ans.pb(i);
	printf("%lld\n",(int)ans.size());
	for(int i:ans)printf("%lld ",i);
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