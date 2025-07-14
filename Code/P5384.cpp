// Problem: P5384 [Cnoi2019] 雪松果树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5384
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int st[maxn],tp,dep[maxn];
#define pii pair<int,int>
vector<pii> que[maxn],p[maxn];
int ans[maxn];
void dfs(int u){
	st[++tp]=u;
	for(pii i:que[u]){
		if(tp-i.first<=0)continue;
		// cout<<st[tp-i.first]<<" "<<i.second<<"\n";
		p[st[tp-i.first]].push_back(i);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dep[v]=dep[u]+1;dfs(v);
	}
	tp--;
}
int t[maxn];
void dfs1(int u){
	for(pii i:p[u])ans[i.second]=-t[dep[u]+i.first];
	t[dep[u]]++;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs1(v);
	}
	for(pii i:p[u])ans[i.second]+=t[dep[u]+i.first];
}
void work(){
	n=read();q=read();
	for(int i=2;i<=n;i++){
		int u=read();
		add(u,i);
	}
	for(int i=1;i<=q;i++){
		int u=read(),k=read();
		que[u].push_back({k,i});
	}
	dfs(1);dfs1(1);
	for(int i=1;i<=q;i++)printf("%lld ",max(0ll,ans[i]-1));
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
