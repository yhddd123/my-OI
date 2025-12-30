// Problem: CF2178H Create or Duplicate
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2178H
// Memory Limit: 1000 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2025-12-30 16:35:16
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
const int maxn=500010;
const int inf=1e18;
bool mbe;

int a,b,c,m,k;
vector<pii> e[maxn<<3];
priority_queue<pii> q;
int dis[maxn<<3];
bool vis[maxn<<3];
void work(){
	a=read(),b=read(),c=read(),m=read(),k=read();
	for(int i=0;i<m*8;i++)dis[i]=inf,vis[i]=0,e[i].clear();
	for(int i=0;i<m;i++){
		for(int s=0;s<(1<<3);s++){
			e[i*8+s].pb({(i+a)%m*8+(s|1),a});
			e[i*8+s].pb({(i+b)%m*8+(s|2),b});
			e[i*8+s].pb({(i+c)%m*8+(s|4),c});
			if(s)e[i*8+s].pb({(i*2)%m*8+s,k*__builtin_popcount(s)});
		}
	}
	dis[0]=0,q.push({0,0});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		// cout<<u<<" "<<dis[u]<<"\n";
		for(auto[v,w]:e[u]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({-dis[v],v});
			}
		}
	}
	printf("%lld\n",dis[7]-a-b-c);
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