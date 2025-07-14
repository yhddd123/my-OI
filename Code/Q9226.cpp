#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=55;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn][maxn];
vector<pii> pos[maxn*maxn];
bool vis[maxn],bk[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read(),pos[a[i][j]].pb({i,j});
	}
	int num=0;
	for(int i=1;i<maxn*maxn;i++){
		for(auto[x,y]:pos[i]){
			if(!vis[x])vis[x]=1,++num;
			if(!bk[y])bk[y]=1,++num;
		}
		if(num==2*n){
			printf("%lld\n",i);
			return ;
		}
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
