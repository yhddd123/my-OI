#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=5010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,seed,a[maxn][maxn];
void gen(int n,int seed){
	std::mt19937 rng(seed);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n+1;++j){
			a[i][j]=j;
			std::swap(a[i][j],a[i][rng()%j+1]);
		}
	}
}
int id[maxn],b[maxn][maxn],pos[maxn];
bool vis[maxn];
void work(){
	n=read();seed=read();
	if(!seed){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n+1;j++)a[i][j]=read();
		}
	}
	else gen(n,seed);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++)b[i][a[i][j]]=j;
	}
	for(int i=1;i<=n;i++)pos[i]=1;
	for(int p=1;p<=n;p++){
		pos[p-1]=1;
		for(int i=p;i<=n;i++)id[i-p+1]=i;
		for(int i=1;i<p;i++)id[n+i-p+1]=i;
		for(int i=n;i;i--){
			while(vis[b[id[i]][pos[id[i]]]])pos[id[i]]++;
			vis[b[id[i]][pos[id[i]]]]=1;
			// cout<<p<<" "<<id[i]<<" "<<pos[id[i]]<<"\n";
		}
		for(int i=1;i<=n+1;i++)if(!vis[i])printf("%lld ",i);
		for(int i=1;i<=n+1;i++)vis[i]=0;
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("c.in","r",stdin);
//	freopen("c.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
