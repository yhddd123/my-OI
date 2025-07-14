#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
vector<pair<pii,int>> que[maxn];
int ans[maxn];
int pre[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int l=read()+1,r=read()+1,num=read();
		if(l>r)swap(l,r);
		que[r].push_back({{l,num},i});
	}
	for(int i=1;i<=n;i++){
		pre[a[i]]=i;
		for(auto [q,id]:que[i]){
			for(int j=0;j<=1000;j++)if(pre[j]>=q.fi)ans[id]=max(ans[id],j%q.se);
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
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
