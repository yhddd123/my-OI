#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],b[maxn];
vector<int> upd[maxn];
int ans[maxn];
int mn[maxn];
bool vis[maxn];
int pos[maxn];
void work(){
	n=read();m=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=b[i-1]+read(),vis[__gcd(n,b[i])]=1,pos[i]=__gcd(n,b[i]);
	for(int g=1;g<=n;g++)if(vis[g]){
		for(int i=0;i<g;i++)mn[i]=a[i];
		for(int i=g;i<n;i++)mn[i%g]=min(mn[i%g],a[i]);
		for(int i=1,res=mn[0];i<=m;i++){
			res=min(res,mn[b[i]%g]);
			if(pos[i]==g)ans[i]=res;
		}
	}
	for(int i=1;i<=m;i++)printf("%lld ",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}