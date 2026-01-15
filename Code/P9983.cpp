// Problem: P9983 [USACO23DEC] Cowntact Tracing P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9983
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-15 17:14:29
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,q,ans,k;
char s[maxn];
vector<int> e[maxn];
int dis[maxn];
bool vis[maxn],bk[maxn];
int dfs(int u,int fa){
	int dpu=0;bk[u]=1;
	for(int v:e[u])if(v!=fa&&s[v]=='1'){
		int dpv=dfs(v,u);
		if(dpu*dpv>=0){
			if(abs(dpu)<abs(dpv))dpu=dpv;
		}
		else{
			if(dpu<0)swap(dpu,dpv);
			if(dpu-1<-dpv)dpu=dpv;
		}
	}
	dpu--;
	if(dpu<0&&(!fa||-dpu>k-dis[fa]))dpu=k-dis[u],++ans;
	// cout<<u<<" "<<dpu<<" "<<ans<<"\n";
	return dpu;
}
void sovle(){
	ans=0;
	for(int i=1;i<=n;i++)dis[i]=n+1;
	queue<int> q;
	for(int i=1;i<=n;i++)if(s[i]=='0')dis[i]=0,q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u]){
			if(dis[v]>dis[u]+1)dis[v]=dis[u]+1,q.push(v);
		}
	}
	for(int i=1;i<=n;i++)vis[i]=(dis[i]>k);
	for(int i=1;i<=n;i++)dis[i]=n+1;
	for(int i=1;i<=n;i++)if(vis[i])dis[i]=0,q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u]){
			if(dis[v]>dis[u]+1)dis[v]=dis[u]+1,q.push(v);
		}
	}
	for(int i=1;i<=n;i++)if(s[i]=='1'&&dis[i]>k){puts("-1");return ;}
	for(int i=1;i<=n;i++)bk[i]=0;
	for(int i=1;i<=n;i++)if(s[i]=='1'&&!bk[i]){
		dfs(i,0);
	}
	printf("%lld\n",ans);
}
void work(){
	n=read();scanf("%s",s+1);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	q=read();
	while(q--)k=read(),sovle();
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