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
const int maxn=410;
const int inf=1e9;
bool mbe;

int n,m;
vector<pii> e[maxn];
bitset<maxn> f[maxn];
int cnt;
void ins(bitset<maxn> &g){
	for(int i=1;i<=m;i++)if(g.test(i)){
		if(!f[i].test(i)){f[i]=g;++cnt;break;}
		g^=f[i];
	}
}
bool vis[maxn];
int pre[maxn],eid[maxn],dep[maxn];
void dfs(int u){
	vis[u]=1;
	for(auto[v,id]:e[u])if(!vis[v]){
		pre[v]=u,eid[v]=id;dep[v]=dep[u]+1;dfs(v);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb({v,i});
	}
	for(int u=1;u<=n;u++){
		for(int i=1;i<=n;i++)vis[i]=0;
		dep[u]=0;dfs(u);
		for(int x=u;x<=n;x++)if(vis[x]){
			for(auto[y,id]:e[x])if(pre[y]!=x){
				bitset<maxn> g;g.set(id);
				int xx=x,yy=y;
				while(xx!=yy){
					if(dep[xx]<dep[yy])swap(xx,yy);
					g.set(eid[xx]),xx=pre[xx];
				}
				ins(g);
			}
		}
	}
	int pw=1;for(int i=1;i<=m-cnt;i++)pw=pw*2%mod;
	printf("%lld\n",pw);
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