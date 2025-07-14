// Problem: P10643 [NordicOI 2022] 嬉皮爵士 Hipster Jazz
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10643
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-22 21:14:34
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
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int col[maxn],num[maxn];
queue<int> q;
bool vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			num[u]+=(col[u]==col[v])-(col[u]!=col[v]);
		}
	}
	for(int i=1;i<=n;i++)if(num[i]>0)q.push(i),vis[i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		if(num[u]<=0)continue;
		col[u]^=1,num[u]=-num[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			num[v]-=(col[u]!=col[v])-(col[u]==col[v]);
			num[v]+=(col[u]==col[v])-(col[u]!=col[v]);
			if(!vis[v]&&num[v]>0)q.push(v),vis[v]=1;
		}
	}
	for(int i=1;i<=n;i++){
		if(col[i])putchar('S');
		else putchar('P');
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
