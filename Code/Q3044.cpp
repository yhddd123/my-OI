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

int n,a[maxn],b[maxn],ans;
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n){tree[x]+=w,x+=lb(x);}
}
int que(int x){
	int res=0;
	while(x){res+=tree[x],x-=lb(x);}
	return res;
}
int to[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	vector<int> pos;
	for(int i=1;i<=n;i++)if(b[i]<=(n+1)/2)pos.pb(i);
	reverse(pos.begin(),pos.end());
	for(int i=1;i<=n;i++)if(a[i]>n/2)to[i]=pos.back(),pos.pop_back();
	for(int i=1;i<=n;i++)if(b[i]>(n+1)/2)pos.pb(i);
	reverse(pos.begin(),pos.end());
	for(int i=1;i<=n;i++)if(a[i]<=n/2)to[i]=pos.back(),pos.pop_back();
	int res=0;
	for(int i=1;i<=n;i++){
		res+=i-1-que(to[i]);
		upd(to[i],1);
	}
	mems(tree,0);
	ans=res;
	if(n&1){
		vector<int> pos;
		for(int i=1;i<=n;i++)if(b[i]<=n/2)pos.pb(i);
		reverse(pos.begin(),pos.end());
		for(int i=1;i<=n;i++)if(a[i]>(n+1)/2)to[i]=pos.back(),pos.pop_back();
		for(int i=1;i<=n;i++)if(b[i]>n/2)pos.pb(i);
		reverse(pos.begin(),pos.end());
		for(int i=1;i<=n;i++)if(a[i]<=(n+1)/2)to[i]=pos.back(),pos.pop_back();
		int res=0;
		for(int i=1;i<=n;i++){
			res+=i-1-que(to[i]);
			upd(to[i],1);
		}
		ans=min(ans,res);
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("pop.in","r",stdin);
//	freopen("pop.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
