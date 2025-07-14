#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
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

int n,a[maxn];
map<ull,int> mp;
mt19937 rnd(time(0));
ull sum[maxn],val[maxn];
int f[maxn],g[maxn];
int c[maxn];
int l[maxn],r[maxn],pos[maxn];
int ans[maxn];
int q[maxn],h,t;
void work(){
	n=read();
	for(int i=1;i<=2*n;i++)a[i]=read();
	for(int i=1;i<=n;i++)val[i]=rnd();
	for(int i=1;i<=2*n;i++)sum[i]=sum[i-1]^val[a[i]];
	for(int i=1;i<=2*n;i++){
		mp[sum[i-1]]++;
		f[i]=mp[sum[i-1]];
	}
	mp.clear();
	for(int i=2*n;i;i--){
		mp[sum[i]]++;
		g[i]=mp[sum[i]];
	}
	mp[0]++;
	for(int i=1;i<=n;i++)pos[i]=2*n+1;
	for(int i=1;i<=2*n;i++){
		r[i]=pos[a[i]];pos[a[i]]=i;
	}
	for(int i=1;i<=n;i++)pos[i]=0;
	for(int i=1;i<=2*n;i++){
		l[i]=pos[a[i]];pos[a[i]]=i;
	}
	q[h=t=0]=0;
	for(int i=2;i<=2*n;i++){
		while(h<t&&r[q[t]]>r[i-1])t--;q[++t]=i-1;
		while(h<t&&r[q[h]]<=i)h++;
		if(h==t)continue;
		int p=q[h];
		cout<<i<<" "<<p<<"\n";
		for(int i=h;i<=t;i++)cout<<i<<" "<<q[i]<<" "<<r[q[i]]<<"\n";
		ans[p]+=f[i]*mp[sum[i-1]^val[a[p]]];
	}
	q[h=t=0]=0;
	for(int i=2*n-1;i;i--){
		while(h<t&&l[q[t]]<l[i+1])t--;q[++t]=i+1;
		while(h<t&&l[q[h]]>=i)h++;
		if(h==t)continue;
		int p=q[h];
		ans[p]+=g[i]*mp[sum[i-1]^val[a[p]]];
	}
	for(int i=1;i<=2*n;i++)printf("%lld ",ans[i]);
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
