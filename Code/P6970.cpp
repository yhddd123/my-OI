// Problem: P6970 [NEERC2016] Game on Graph
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6970
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-18 09:18:43
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int d[maxn],du[maxn][2];
queue<pii> q;
int f[maxn][2],g[maxn][2];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(v,u);
	}
	for(int i=1;i<=tot;i++)d[e[i].to]++;
	for(int i=1;i<=n;i++)f[i][0]=f[i][1]=1;
	for(int i=1;i<=n;i++)if(!d[i])q.push({i,0}),q.push({i,1}),f[i][0]=f[i][1]=0;
	while(!q.empty()){
		int u=q.front().fi,fl=q.front().se;q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if((!fl&&f[v][fl^1])||(fl&&!--d[v]))f[v][fl^1]=0,q.push({v,fl^1});	
		}
	}
	// for(int i=1;i<=n;i++)cout<<f[i][0]<<" "<<f[i][1]<<"\n";
	for(int i=1;i<=tot;i++)d[e[i].to]++;
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			du[v][0]+=!f[u][1],du[v][1]+=!f[u][0];
		}
	}
	mems(g,-1);
	for(int i=1;i<=n;i++)if(!d[i])q.push({i,0}),q.push({i,1}),g[i][0]=g[i][1]=0;
	while(!q.empty()){
		int u=q.front().fi,fl=q.front().se;q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(f[v][fl^1])continue;
			if(!g[u][fl]){
				if(g[v][fl^1]==-1)q.push({v,fl^1}),g[v][fl^1]=1;
			}
			else{
				if(!--du[v][fl^1])q.push({v,fl^1}),g[v][fl^1]=0;
			}
		}
	}
	for(int i=1;i<=n;i++)if(g[i][0]==-1)g[i][0]=1;
	for(int i=1;i<=n;i++)if(g[i][1]==-1)g[i][1]=0;
	for(int i=1;i<=n;i++){
		if(f[i][0])putchar('D');
		else if(g[i][0])putchar('W');
		else putchar('L');
	}
	puts("");
	for(int i=1;i<=n;i++){
		if(f[i][1])putchar('D');
		else if(g[i][1])putchar('W');
		else putchar('L');
	}
	
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
