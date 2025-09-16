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

int n,c;long long ans;
vector<int> e[maxn];
int dfn[maxn],rnk[maxn],idx,st[14][maxn],siz[maxn],dep[maxn],fa[maxn];
void dfs(int u){
	st[0][dfn[u]=++idx]=fa[u],rnk[idx]=u;siz[u]=1;dep[u]=dep[fa[u]]+1;
	for(int v:e[u]){
		if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
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
// Barrett 取模器（加速乘法/取模）
struct FastMod {
	unsigned long long m, im;
	FastMod(unsigned long long mod_) : m(mod_) {
		im = (~0ull) / m;
	}
	unsigned int reduce(unsigned long long a) const {
		unsigned long long q = (unsigned long long)((__uint128_t)im * a >> 64);
		unsigned long long r = a - q * m;
		if (r >= m) r -= m;
		return (unsigned int)r;
	}
	unsigned int mul(unsigned int a, unsigned int b) const {
		return reduce((unsigned long long)a * b);
	}
	unsigned int add(unsigned int a, unsigned int b) const {
		unsigned int s = a + b;
		if (s >= m) s -= m;
		return s;
	}
	unsigned int sub(unsigned int a, unsigned int b) const {
		return a >= b ? a - b : a + m - b;
	}
} FM(998244353u);
inline int C(int m,int n){
	// if(m<0||n<0||m<n)return 0;
	return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
inline int calc(int x,int y){
	unsigned int t = FM.mul((unsigned int)fac[x+y], (unsigned int)inv[x]);
	t = FM.mul(t, (unsigned int)inv[y]);
	return (int)FM.sub(t, 1u);
}
// inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
inline void inc(int &u,int v){u+=v,u+=(u>>31)&mod;}
int val[maxn];
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
	for(int j=1;j<=13;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	{
		int t = pw[n]-1; if(t<0) t += mod;
		unsigned int addv = FM.mul((unsigned int)t, (unsigned int)pwc1[n-1]);
		ans += addv;
	}
	for(int i=1;i<=n;i++){
		int t = pwc1[i]-1; if(t<0) t += mod;
		val[i] = (int)FM.mul((unsigned int)t, (unsigned int)pwc1[n-1-i]);
	}
	for(int u=1;u<=n;u++){
		for(int p=0;p<e[u].size();p++){
			int vv=e[u][p];
			for(int j=dfn[vv];j<dfn[vv]+siz[vv];j++){
				int v=rnk[j];
				int szu=n-siz[u],szv=siz[v],szvv=n-siz[vv];
				long long res=calc(n-siz[vv],siz[v]);
				res-=calc(szu,szv);
				for(int v1:e[u]){
					if(v1==vv)continue;
					res-=calc(siz[v1],szv);
					for(int v2:e[v])res+=calc(siz[v1],siz[v2]);
				}
				for(int v2:e[v]){
					res-=calc(szvv,siz[v2]);
					res+=calc(szu,siz[v2]);
				}
				res%=mod,res+=mod;
				{
					unsigned int prod = FM.mul((unsigned int)(res%mod), (unsigned int)val[dep[v]-dep[u]]);
					ans -= prod;
				}
			}
		}
		for(int j=dfn[u]+siz[u];j<=n;j++){
			int v=rnk[j];
			int szu=siz[u],szv=siz[v];
			long long res=calc(szu,szv);
			for(int v1:e[u]){
				res-=calc(siz[v1],szv);
				for(int v2:e[v])res+=calc(siz[v1],siz[v2]);
			}
			for(int v2:e[v])res-=calc(szu,siz[v2]);
			res%=mod,res+=mod;
			{
				unsigned int prod = FM.mul((unsigned int)(res%mod), (unsigned int)val[dis(u,v)]);
				ans -= prod;
			}
		}
	}
	ans%=mod,ans+=mod,ans%=mod;
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