// Problem: P10559 [ICPC 2024 Xi'an I] The Last Cumulonimbus Cloud
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10559
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-29 15:42:11
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m,q;
int d[maxn];
vector<int> e[maxn],g[maxn];
int qq[maxn],h,t;
bool vis[maxn];
int a[maxn],b[maxn];
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
		d[u]++,d[v]++;
	}
	h=1,t=0;
	for(int i=1;i<=n;i++)if(d[i]<=10)qq[++t]=i;
	while(h<=t){
		int u=qq[h++];vis[u]=1;
		for(int v:e[u])if(!vis[v]){
			g[u].pb(v);
			if(--d[v]==10)qq[++t]=v;
		}
	}
	for(int u=1;u<=n;u++){
		int w=read();
		a[u]+=w;for(int v:g[u])b[v]+=w;
	}
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),w=read();
			a[u]+=w;for(int v:g[u])b[v]+=w;
		}
		else{
			int u=read();
			int ans=b[u];for(int v:g[u])ans+=a[v];
			printf("%lld\n",ans);
		}
	}
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