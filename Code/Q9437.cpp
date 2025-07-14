#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,a[maxn],b[maxn],c[maxn],d[maxn];
int id[maxn],ans;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=c[i-1]+read();
	for(int i=1;i<=n;i++)d[i]=d[i-1]+read();
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]-b[u]<a[v]-b[v];});
	int sum=0;for(int i=1;i<=n;i++)sum+=b[i];
	ans=sum+d[n];
	for(int i=1;i<=n;i++){
		sum+=a[id[i]]-b[id[i]];
		ans=min(ans,sum+c[i]+d[n-i]);
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