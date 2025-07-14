#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,a,b,ans;
set<int> s[maxn];
bool vis[maxn][maxn];
void work(){
	n=read();a=read(),b=read();
	s[0].insert(0);
	for(int i=1;i<=n;i++){
		int la=read()-a,ra=read()-a,lb=read()-b,rb=read()-b;
		if(ra<0||rb<0)continue;
		la=max(la,0ll),ra=min(ra,n),lb=max(lb,0ll),rb=min(rb,n);
		vector<pii> tmp;
		for(int j=la;j<=ra;j++){
			auto it=s[j].lower_bound(lb);
			while(it!=s[j].end()&&(*it)<=rb){
				tmp.push_back({j,(*it)+1}),tmp.push_back({j+1,(*it)});
				vis[j][(*it)]=1;
				it=s[j].erase(it);
			}
		}
		for(pii p:tmp)if(!vis[p.fi][p.se]){
			ans=max(ans,p.fi+p.se);
			s[p.fi].insert(p.se);
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
