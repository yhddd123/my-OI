// Problem: AT_arc083_d [ARC083F] Collecting Balls
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc083_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-22 20:58:45
// 
// Powered by CP Editor (https://cpeditor.org)

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

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn],ni[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
}
int n,ans=1;
vector<int> e[maxn],g[maxn];
bool vis[maxn];
vector<int> id;
int numv,nume,x,y;
void dfs(int u,int fa){
	vis[u]=1;id.pb(u);numv++;
	for(int v:e[u]){
		nume++;
		if(v==fa)continue;
		if(vis[v])x=u,y=v;
		else dfs(v,u);
	}
}
int d[maxn],siz[maxn],fr[maxn];
void dfs1(int u,int fa){
	fr[u]=fa;
	for(int v:e[u])if(v!=fa&&v!=x)dfs1(v,u);
}
void dfs(int u){
	siz[u]=1;
	for(int v:g[u])dfs(v),siz[u]+=siz[v];
}
int sovle(){
	for(int u:id)g[u].clear(),d[u]=fr[u]=0;
	dfs1(x,y);
	for(int u:id){
		for(int v:e[u]){
			if(v<fr[u])g[u].pb(v),d[v]++;
		}
	}
	for(int u:id)if(!d[u])dfs(u);
	// for(int u:id)cout<<u<<" "<<siz[u]<<"\n";
	int res=1;for(int u:id)res=res*ni[siz[u]]%mod;
	return res;
}
void work(){
	n=read();init(2*n);
	for(int i=1;i<=2*n;i++){
		int x=read(),y=read()+n;
		e[x].pb(y),e[y].pb(x);
	}
	for(int i=1,s=0;i<=2*n;i++)if(!vis[i]){
		id.clear();numv=nume=0;dfs(i,0);
		if(numv*2!=nume){puts("0");return ;}
		int num1=sovle();
		swap(x,y);
		int num2=sovle();
		// cout<<numv<<" "<<nume<<" "<<x<<" "<<y<<" "<<num1*fac[numv]%mod<<" "<<num2*fac[numv]%mod<<"\n";
		ans=ans*(num1+num2)%mod*fac[numv]%mod*C(s+numv,s)%mod;s+=numv;
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