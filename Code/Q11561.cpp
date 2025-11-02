#include<bits/stdc++.h>
#define int long long
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
const int maxn=1400010;
const int inf=1e9;
bool mbe;

int n,d[maxn],cnt[maxn];
vector<pii> g[maxn];
tuple<int,int,int> edge[maxn];
int vis[maxn],val[maxn];
int id[maxn];
void work(){
	n=read();
	for(int i=1;i<=2*n;i++)g[i].clear(),d[i]=cnt[i]=0,id[i]=i;
	for(int i=1;i<=n;i++){
		int u=read(),v=read(),w=read();
		d[u]+=w,d[v]+=w;
		cnt[u]++,cnt[v]++;edge[i]={u,v,w};
	}
	for(int i=1;i<=n;i++){
		auto[u,v,w]=edge[i];
		if(cnt[u]<cnt[v])g[u].pb({v,w});
		else g[v].pb({u,w});
	}
	for(int i=1;i<=2*n;i++)vis[i]=0;
	int mx=0;for(int i=1;i<=2*n;i++)mx=max(mx,d[i]);
	for(int u=1;u<=2*n;u++){
		for(auto[v,w]:g[u])vis[v]=u,val[v]=w;
		for(auto[v,w1]:g[u]){
			for(auto[w,w2]:g[v])if(vis[w]==u)mx=max(mx,w1+w2+val[w]);
		}
	}
	printf("%lld\n",mx);
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