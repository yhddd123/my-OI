#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 998244353
using namespace std;
const int maxn=100010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],sum[maxn],d[maxn];
void dfs(int u,int fa){
	siz[u]=1;sum[u]=d[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];sum[u]+=sum[v];
	}
}
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
		d[u]++;d[v]++;
	}
	dfs(1,0);
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(siz[u]<siz[v]){
				ans+=d[u]*siz[u]%mod*(n-siz[u])%mod,ans%=mod;
			}
			else{
				ans+=(2*n-2-d[v])*(n-siz[v])%mod*siz[v]%mod,ans%=mod;
			}
		}
	}
	ans*=ksm(n*n%mod,mod-2),ans%=mod;
	printf("%lld\n",ans);
}

int T;
signed main(){
//		freopen("P3412_2.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
