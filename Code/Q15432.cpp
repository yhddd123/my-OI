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
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int n1,n2,m;
vector<int> e[maxn];
int f[maxn],g[maxn];
int to[maxn],mn;
pii lst[maxn];
bool vis[maxn];
int dfs(int u){
	vis[u]=1;mn=min(mn,u);
	for(int v:e[u])if(!to[v])return u;
	for(int v:e[u])if(!vis[to[v]]){
		int p=dfs(to[v]);lst[to[v]]={u,v};
		if(p!=-1)return p;
	}
	return -1;
}
int st[maxn],tp;
void work(){
	n1=read(),n2=read(),m=read();long long ans=0;
	for(int i=1;i<=n2;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[v].pb(u);
	}
	for(int i=1;i<=max(n1,n2);i++)to[i]=f[i]=g[i]=0;
	for(int i=1;i<=n2;i++){
		for(int j=1;j<=i;j++)vis[j]=0;
		mn=i;
		int p=dfs(i);
		if(p==-1){
			if(mn!=i){
				f[mn]=0,f[i]=1;
				int x=mn;
				tp=0;while(x!=i){
					st[++tp]=x;
					x=lst[x].fi;
				}
				reverse(st+1,st+tp+1);
				for(int i=1;i<=tp;i++)to[lst[st[i]].se]=lst[st[i]].fi;
			}
		}
		else{
			int x=p;
			tp=0;while(x!=i){
				st[++tp]=x;
				x=lst[x].fi;
			}
			reverse(st+1,st+tp+1);
			for(int i=1;i<=tp;i++)to[lst[st[i]].se]=lst[st[i]].fi;
			for(int v:e[p])if(!to[v]){to[v]=p;break;}
			f[i]=1;
		}
		g[i+1]=0;for(int j=i;j;j--)g[j]=g[j+1]+f[j];
		for(int j=1;j<=i;j++)(ans+=1ll*g[j]*i*j*((i^j)+1))%=mod;
		// cout<<i<<" "<<p<<" "<<tp<<"\n";
		// for(int j=1;j<=n1;j++)cout<<to[j]<<" ";cout<<"\n";
		// for(int j=1;j<=i;j++)cout<<j<<" "<<i<<" "<<g[j]<<"\n";cout<<"\n";
	}
	printf("%lld\n",ans);
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