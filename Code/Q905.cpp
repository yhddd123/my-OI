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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],ans;
int d[maxn];
vector<int> e[maxn];
int vis[maxn];
pii edge[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1;
		edge[i]={u,v};
		d[u]++,d[v]++;
	}
	for(int i=1;i<=m;i++){
		auto[u,v]=edge[i];
		if(d[u]<d[v]||(d[u]==d[v]&&u>v))swap(u,v);
		e[u].pb(v);
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u])vis[v]=u;
		for(int v:e[u]){
			for(int w:e[v])if(vis[w]==u)(ans+=a[u]*a[v]%mod*a[w])%=mod;
		}
	}
	printf("%lld\n",ans);
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