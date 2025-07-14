#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=50010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],p[maxn],ans;
bitset<maxn> f[maxn],g[maxn],s;
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),p[a[i]]=i;
	for(int i=1;i<=n;i++)f[i].set(i);
	for(int i=n;i;i--)f[p[i]]|=f[p[i+1]];
	for(int i=n;i;i--)f[i]&=s,s.set(i);
	for(int i=1;i<=n;i+=m){
		for(int j=1;j<=m;j++)g[j].reset();
		if(i+m-1>n)break;
		g[m]=f[i+m-1];
		for(int j=i+m-2;j>=i;j--)g[j-i+1]=g[j-i+2]&(f[j]<<(i+m-1-j));
		s.set();
		for(int j=i;j<=i+m-1&&j+m-1<=n;j++){
			ans+=(s&g[j-i+1]).count();
			if(j+m<=n)s&=f[j+m]>>(j-i+1);
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
