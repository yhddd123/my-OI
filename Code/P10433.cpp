// Problem: P10433 [JOIST 2024] 棋盘游戏 / Board Game
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10433
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-04 09:34:24
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
const int maxn=50010;
const int inf=1e18;
bool mbe;

int n,m,k;
vector<int> e[maxn];
char s[maxn];
int d1[maxn],d2[maxn];
bool vis[maxn];
void bfs1(){
	queue<int> q;
	for(int i=1;i<=n;i++)d1[i]=n+1;
	for(int i=1;i<=n;i++)if(s[i]=='1')d1[i]=0,q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u]){
			if(d1[v]>d1[u]+1){
				d1[v]=d1[u]+1;
				q.push(v);
			}
		}
	}
}
void bfs2(){
	deque<int> q;
	for(int i=1;i<=n;i++)d2[i]=n+1,vis[i]=0;
	for(int i=1;i<=n;i++)if(s[i]=='1'){
		bool fl=0;for(int v:e[i])fl|=(s[v]=='1');
		if(fl)d2[i]=0,q.pb(i);
	}
	while(!q.empty()){
		int u=q.front();q.pop_front();
		if(vis[u])continue;vis[u]=1;
		for(int v:e[u]){
			int w=s[u]=='1'?0:1;
			if(d2[v]>d2[u]+w){
				d2[v]=d2[u]+w;
				if(!w)q.push_front(v);
				else q.pb(v);
			}
		}
	}
}
int tk[maxn],tb[maxn],f[maxn];
int ans[maxn];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	scanf("%s",s+1);
	bfs1(),bfs2();
	int p=read();
	auto upd=[&](int l,int r,int k,int b){
		// cout<<l<<" "<<r<<" "<<k<<" "<<b<<"\n";
		if(l>r)return ;
		tk[l]+=k,tk[r+1]-=k,tb[l]+=b,tb[r+1]-=b;
	};
	for(int i=2;i<=k;i++){
		int u=read();
		int dd1=d1[u],dd2=d2[u];
		if(s[u]=='1')dd1=2;
		dd1-=2;
		// int pos=dd2-dd1;
		// upd(1,min(pos,n),2,dd1);
		// upd(pos+1,n,1,dd2);
		for(int j=1;j<=n;j++)f[j]+=min(2*j+dd1,j+dd2);
		// cout<<u<<" "<<s[u]<<" "<<d1[u]<<" "<<d2[u]<<"\n";
	}
	// for(int i=1;i<=n;i++)tk[i]+=tk[i-1],tb[i]+=tb[i-1];
	// for(int i=1;i<=n;i++)f[i]=tk[i]*i+tb[i];
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	queue<tuple<int,int,int>> q;
	for(int i=1;i<=n;i++)ans[i]=inf;ans[p]=0;
	q.push({p,0,0});
	while(!q.empty()){
		auto[u,k,d]=q.front();q.pop();
		for(int v:e[u]){
			int w=d+f[k]+1;
			if(ans[v]>w){
				ans[v]=w;
				q.push({v,k+(s[v]=='1'),d+1});
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);	
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