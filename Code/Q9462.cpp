#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n,m,r;
pii a[maxn];
vector<int> ans;
void work(){
	n=read();r=read();m=read();
	for(int i=1;i<=n;i++){
		int u=read(),v=read();
		a[i]={u*u+v*v,i};
	}
	sort(a+1,a+n+1);
	ans.clear();
	for(int i=1;i<=n;i++)if(a[i].fi<=(r-2*m)*(r-2*m))ans.pb(a[i].se);
	if(!ans.size()){
		for(int i=1;i<=n;i++)if(a[i].fi==a[1].fi)ans.pb(a[i].se);
	}
	printf("%lld\n",(int)ans.size());
	sort(ans.begin(),ans.end());
	for(int i:ans)printf("%lld ",i);puts("");
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
	
	T=read();
	while(T--)work();
}
