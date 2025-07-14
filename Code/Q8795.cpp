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

int n;
double a,b,x[maxn],f[maxn],g[maxn];
void work(){
	cin>>a>>b>>n>>x[1]>>x[n];
	f[1]=g[2]=1;
	for(int i=3;i<=n;i++){
		f[i]=f[i-1]*a+f[i-2]*b;
		g[i]=g[i-1]*a+g[i-2]*b;
	}
	x[2]=(x[n]-f[n]*x[1])/g[n];
	for(int i=3;i<n;i++)x[i]=a*x[i-1]+b*x[i-2];
	for(int i=1;i<=n;i++)printf("%.10lf\n",x[i]);
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
