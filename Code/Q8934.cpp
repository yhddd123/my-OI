#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=1025;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,e[maxn][maxn];
int a[maxn],vis[maxn];
int calc(){
	int res=0;
	for(int i=1;i<=n;i++){
		int mex=1;
		for(int j=1;j<=n;j++)vis[j]=0;
		for(int j=1;j<i;j++)if(e[i][j])vis[a[j]]=1;
		while(vis[mex])mex++;
		a[i]=mex;res=max(res,mex);
		// cout<<i<<" "<<a[i]<<"\n";
	}
	return res;
}
vector<pii> ans;
void work(){
	n=read();n=1024;
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)e[i][j]=1;
	// }
	e[1][2]=e[2][1]=e[4][3]=e[3][4]=1;
	for(int i=5;i<=n;i+=2){
		e[i][2]=e[2][i]=e[i][3]=e[3][i]=1;
		for(int j=6;j<i;j+=2)e[i][j]=e[j][i]=1;
	}
	for(int i=6;i<=n;i+=2){
		e[1][i]=e[i][1]=e[4][i]=e[i][4]=1;
		for(int j=5;j<i-1;j+=2)e[i][j]=e[j][i]=1;
	}
	ans.pb({1,2}),ans.pb({3,4});
	for(int i=5;i<=n;i+=2){
		ans.pb({i,2}),ans.pb({i,3});
		for(int j=6;j<i;j+=2)ans.pb({i,j});
	}
	for(int i=6;i<=n;i+=2){
		ans.pb({1,i}),ans.pb({4,i});
		for(int j=5;j<i-1;j+=2)ans.pb({i,j});
	}
	printf("1024 %lld 2\n",ans.size());
	printf("1 2 2 1 ");for(int i=5;i<=n;i++)printf("%lld ",2-(i&1));puts("");
	for(auto[u,v]:ans)printf("%lld %lld\n",u,v);
	// printf("%lld\n",calc());
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
