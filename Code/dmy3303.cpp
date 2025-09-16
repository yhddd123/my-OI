#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=30010;
const int inf=1e9;
bool mbe;

int n,c,ans;
vector<int> e[maxn];
int dfn[maxn],rnk[maxn],idx,siz[maxn],dep[maxn],fa[maxn];
void dfs(int u){
	rnk[dfn[u]=++idx]=u;siz[u]=1;dep[u]=dep[fa[u]]+1;
	for(int v:e[u]){
		if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
	}
}
int fac[maxn],inv[maxn],pw[maxn],pwc1[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
inline int C(int m,int n){
	// if(m<0||n<0||m<n)return 0;
	return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
inline int calc(int x,int y){return 1ll*fac[x+y]*inv[x]%mod*inv[y]%mod-1;}
// inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
inline void inc(int &u,int v){u+=v,u+=(u>>31)&mod;}
int val[maxn],f[maxn],g[maxn];
void work(){
	n=read();c=read();ans=1;
	pwc1[0]=1;for(int i=1;i<=n;i++)pwc1[i]=1ll*pwc1[i-1]*(c+1)%mod;
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	idx=0;dfs(1);
	for(int i=2;i<=n;i++){
		for(int j=0;j<e[i].size();j++)if(e[i][j]==fa[i]){
			for(int k=j;k+1<e[i].size();k++)e[i][k]=e[i][k+1];
			e[i].pop_back();
			break;
		}
	}
	ans+=1ll*(pw[n]-1)*pwc1[n-1]%mod;
	for(int i=1;i<=n;i++)val[i]=1ll*(pwc1[i]-1)*pwc1[n-1-i]%mod;
	g[1]=val[1];for(int i=2;i<=n;i++){
		inc(g[i]=val[i],-val[i-1]);
		inc(g[i],-val[i-1]);
		inc(g[i],val[i-2]-mod);
	}
	for(int i=1;i<=n;i++)f[i]=0;
	for(int u=1;u<=n;u++){
		for(int p=0;p<e[u].size();p++){
			int vv=e[u][p];
			for(int j=dfn[vv];j<dfn[vv]+siz[vv];j++){
				int v=rnk[j];
				inc(f[dep[v]-dep[u]],calc(n-siz[vv],siz[v])-mod);
				for(int j1=dfn[u]+1;j1<dfn[vv];j1++){
					int v1=rnk[j1];
					inc(f[dep[v]+dep[v1]-2*dep[u]],calc(siz[v1],siz[v])-mod);
				}
			}
		}
	}
	for(int i=1;i<=n;i++)inc(ans,-1ll*f[i]*g[i]%mod);
	printf("%d\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	n=maxn-10;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	
	T=read();
	while(T--)work();
}