#include<bits/stdc++.h>
// #define int long long
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
const int maxn=210;
const int inf=1e9;
bool mbe;

inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn],ni[maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
}
int n,rt,ans,val;
vector<int> e[maxn];
int siz[maxn],rnk[maxn],idx;
void dfs(int u,int fa){
	siz[u]=1;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);siz[u]+=siz[v];
	}
	val=1ll*val*ni[siz[u]]%mod;
	for(int i=0;i<e[u].size();i++)if(e[u][i]==fa)e[u][i]=e[u].back(),e[u].pop_back();
}
int f[maxn][maxn];
void dfs(int u,int fa,int mul){
	mul=1ll*mul*siz[u]%mod*ni[siz[u]-1]%mod;
	rnk[++idx]=u;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		inc(ans,1ll*abs(u-v)*siz[v]%mod*mul%mod);
		dfs(v,u,mul);
		for(int j=i+1;j<e[u].size();j++){
			int w=e[u][j];
			f[v][w]=mul;
		}
	}
}
void down(int u,int v){
	// cout<<u<<" "<<v<<" "<<f[u][v]<<"\n";
	inc(ans,2ll*f[u][v]*ni[siz[u]+siz[v]-1]%mod*siz[u]*siz[v]%mod*abs(u-v)%mod);
	for(int w:e[u])inc(f[w][v],1ll*f[u][v]*ni[siz[u]+siz[v]-1]%mod*siz[u]%mod);
	for(int w:e[v])inc(f[u][w],1ll*f[u][v]*ni[siz[u]+siz[v]-1]%mod*siz[v]%mod);
}
void work(){
	n=read();rt=read();init(n);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	val=fac[n-1];
	dfs(rt,0);dfs(rt,0,1);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)if(f[rnk[i]][rnk[j]])down(rnk[i],rnk[j]);
	}
	printf("%d\n",1ll*ans*val%mod);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}