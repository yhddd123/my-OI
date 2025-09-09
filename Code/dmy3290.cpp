#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n;
vector<int> e[maxn];
int d[maxn];
int f[maxn][3];
void dfs(int u,int fa){
	if(e[u].size()==1){f[u][1]=f[u][2]=1;return ;}
	int f00=1,f01=0,f02=0,f10=1,f11=0;
	int mul=1;
	for(int v:e[u]){
		if(v==fa)continue;dfs(v,u);
		int g00,g01,g02,g10,g11;
		g00=(f[v][0]+f[v][1])*f00%mod;
		g01=(f[v][2]*f00+(f[v][0]+f[v][1])*f01)%mod;
		g02=(f[v][2]*f01+(f[v][0]+f[v][1])*f02)%mod;
		g10=f[v][0]*f10%mod;
		g11=(f[v][2]*f10+f[v][0]*f11)%mod;
		f00=g00,f01=g01,f02=g02,f10=g10,f11=g11;
		mul=mul*f[v][0]%mod;
	}
	f[u][0]=f02,f[u][1]=f11,f[u][2]=f01;
	(f[u][1]+=mul)%=mod,(f[u][2]+=mul)%=mod;
	// cout<<u<<" "<<f[u][0]<<" "<<f[u][1]<<" "<<f[u][2]<<"\n";
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	int rt=0;for(int i=1;i<=n;i++)if(e[i].size()!=1)rt=i;
	dfs(rt,0);
	printf("%lld\n",(f[rt][0]+f[rt][1])%mod);
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