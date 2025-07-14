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

int n,a[maxn];
vector<pii> ans;
void work(){
	n=read();ans.clear();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=59;~i;i--){
		vector<int> id;
		for(int j=1;j<=n;j++)if(a[j]&(1ll<<i))id.pb(j);
		if(id.size()>2){
			puts("-1");
			return ;
		}
		if(!id.size())continue;
		int u=a[id[0]],v=a[id[1]];
		ans.pb({id[0],u-(u^v)});
		a[id[0]]=u^v,a[id[1]]=0;
	}
	printf("%lld\n",ans.size());
	for(auto[i,j]:ans)printf("%lld %lld\n",i,j);
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
