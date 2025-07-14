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

int n,a,b,ans;
void work(){
	n=read();a=read();b=read();
	ans=n*(n+2)*(2*n+1)/8;
	// cout<<ans<<"\n";
	for(int i=1;i<=b;i++){
		int mn=b-i+1,mx=min(a-i+1,a);
		if(mn<=mx)ans-=mx-mn+1;
	}
	for(int i=b+1;i<=a+1;i++){
		int mn=i-b,mx=min(n-a,i-1);
		if(mn<=mx)ans-=mx-mn+1;
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
