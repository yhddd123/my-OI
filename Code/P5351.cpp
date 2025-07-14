// Problem: P5351 Ruri Loves Maschera
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5351
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
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

int n,l,r,ans;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int sum,siz[maxn],mx[maxn],rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1;mx[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		getrt(v,u);siz[u]+=siz[v];mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],sum-siz[u]);
	if(mx[u]<mx[rt])rt=u;
}
struct bit{
	int c[maxn];
	int lowbit(int x){return x&(-x);}
	void updata(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
	int que(int u,int v){
		u=max(u,1ll);
		if(u>v)return 0;
		return query(v)-query(u-1);
	}
}t;
#define pii pair<int,int>
vector<pii> len[maxn],dis;
void dfs(int u,int fa,int tp,int d1,int d2){
	siz[u]=1;
	len[tp].push_back({d1,d2});dis.push_back({d1,d2});
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v]||v==fa)continue;
		dfs(v,u,tp,max(d1,e[i].w),d2+1);
		siz[u]+=siz[v];
	}
}
void sovle(int u){
	// cout<<u<<" "<<ans<<"\n";
	vis[u]=1;dis.clear();
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		len[v].clear();
		dfs(v,u,v,e[i].w,1);
	}
	sort(dis.begin(),dis.end());
	for(pii i:dis){
		if(i.second>=l&&i.second<=r)ans+=i.first;
		ans+=t.que(l-i.second,r-i.second)*i.first;
		t.updata(i.second,1);
		// cout<<i.first<<" "<<i.second<<" "<<ans<<"\n";
	}
	for(pii i:dis)t.updata(i.second,-1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		sort(len[v].begin(),len[v].end());
		for(pii j:len[v]){
			ans+=t.que(l-j.second,r-j.second)*j.first;
			t.updata(j.second,-1);
		}
		for(pii j:len[v])t.updata(j.second,1);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		rt=0;sum=siz[v];getrt(v,v);sovle(rt);
	}
}
void work(){
	n=read();l=read();r=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	mx[0]=inf;sum=n;getrt(1,1);sovle(rt);
	printf("%lld\n",ans*2);
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
