#include<bits/stdc++.h>
#define ll long long
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
const int maxn=23;
const int inf=1e9;
bool mbe;

int n,m;
pii edge[maxn*maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,id;
}e[maxn<<1];
void add(int u,int v,int id){e[++tot]={head[u],v,id};head[u]=tot;}
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int val[maxn];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		val[v]=val[u]^(1<<e[i].id-1),dfs(v,u);
	}
}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
int fac[maxn*maxn],inv[maxn*maxn];
int num[1<<maxn-1];
int f[1<<maxn-1],g[1<<maxn-1];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		edge[i]={u,v};
	}
	for(int i=1;i<n;i++)ff[i]=i;
	for(int i=1;i<n;i++){
		auto[u,v]=edge[i];
		if(fd(u)==fd(v)){puts("0");return ;}
		ff[fd(u)]=fd(v);
		add(u,v,i),add(v,u,i);
	}
	dfs(0,0);
	for(int i=n;i<=m;i++){
		auto[u,v]=edge[i];
		// cout<<u<<" "<<v<<" "<<(val[u]^val[v])<<"\n";
		num[val[u]^val[v]]++;
	}
	for(int i=0;i<n-1;i++){
		for(int s=0;s<(1<<n-1);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
	}
	fac[0]=1;for(int i=1;i<=m;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[m]=ksm(fac[m]);for(int i=m-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	f[0]=1;
	for(int s=0;s<(1<<n-1);s++){
		// cout<<s<<" "<<f[s]<<" "<<g[s]<<"\n";
		int sz=sz=__builtin_popcount(s),s1=((1<<n-1)-1)^s,cnt=sz+num[(1<<n-1)-1]-num[s1];
		// cout<<sz<<" "<<cnt<<"\n";
		for(int i=0;i<n-1;i++)if(!(s&(1<<i))){
			int s2=s1^(1<<i);
			int k=num[s1]-num[s2];
			int ff=1ll*f[s]*fac[cnt+k]%mod*inv[cnt]%mod;
			int gg=1ll*g[s]*fac[cnt+k+1]%mod*inv[cnt+1]%mod;
			// cout<<s<<" "<<i<<" "<<k<<" "<<ff<<" "<<gg<<"\n";
			(f[s|(1<<i)]+=ff)%=mod;
			(g[s|(1<<i)]+=gg)%=mod;
			(g[s|(1<<i)]+=1ll*(sz+1)*ff%mod)%=mod;
		}
	}
	printf("%d\n",g[(1<<n-1)-1]);
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