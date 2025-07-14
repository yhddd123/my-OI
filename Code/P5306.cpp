// Problem: P5306 [COCI2018-2019#5] Transport
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5306
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-10 19:05:24
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int siz[maxn],w[maxn],num,rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		getrt(v,u);
		siz[u]+=siz[v],w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],num-siz[u]);
	if(w[u]<=num/2)rt=u;
}
int sum[maxn],del[maxn];
vector<int> id,id1,id2,id3;
void dfs(int u,int fa,int mx,int mn){
	siz[u]=1;
	if(sum[u]-del[u]>=mx)id.pb(sum[u]-del[u]);
	id1.pb(mn);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		sum[v]=sum[u]+a[v],del[v]=del[u]+e[i].w;
		dfs(v,u,max(mx,sum[u]-del[u]),min(mn,sum[u]-del[v]));
		siz[u]+=siz[v];
	}
}
int calc(int v,bool fl=0){
	int res=0;
	sort(id.begin(),id.end());
	sort(id1.begin(),id1.end());
	for(int i=0,j=id1.size()-1;i<id.size();i++){
		while(j>=0&&id[i]+id1[j]>=v)j--;
		res+=id1.size()-1-j;
	}
	if(fl){
		res+=id.size();
		for(int i:id1)if(i>=0)res++;
	}
	return res;
}
void sovle(int u){
	vis[u]=1;
	sum[u]=a[u],del[u]=0,siz[u]=1;
	id2.clear(),id3.clear();
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		sum[v]=sum[u]+a[v],del[v]=del[u]+e[i].w;
		id.clear(),id1.clear();
		dfs(v,u,a[u],sum[u]-del[v]);
		ans-=calc(a[u]);
		// cout<<u<<" "<<v<<"\n";
		// for(int j:id)cout<<j<<" ";cout<<"\n";
		// for(int j:id1)cout<<j<<" ";cout<<"\n";
		for(int j:id)id2.pb(j);
		for(int j:id1)id3.pb(j);
		siz[u]+=siz[v];
	}
	// cout<<ans<<"\n";
	swap(id,id2),swap(id1,id3);
	ans+=calc(a[u],1);
	// for(int i:id)cout<<i<<" ";cout<<"\n";
	// for(int i:id1)cout<<i<<" ";cout<<"\n";
	// cout<<u<<" "<<ans<<endl;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		num=siz[v];getrt(v,u);sovle(rt);
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	num=n;getrt(1,0);sovle(rt);
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
