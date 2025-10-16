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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m,k,ans;
int pw[maxn],f[maxn];
vector<int> e[maxn];
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				int siz=0;siz++;
				while(st[tp--]!=v)siz++;
				siz++;
				ans=ans*f[siz]%mod;
				// cout<<siz<<"\n";
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
void work(){
	n=read();m=read();k=read();ans=1;
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*(k-1)%mod;
	f[1]=1,f[2]=k-1;for(int i=3;i<=n;i++)f[i]=(pw[i-1]+mod-f[i-1])%mod;
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)dfn[i]=0;idx=0;
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	printf("%lld\n",ans*k%mod);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}