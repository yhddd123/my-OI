#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
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

int n,m,ans;
int g[maxn][2],d[maxn];
vector<int> e[maxn];
int vis[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		g[i][0]=read(),g[i][1]=read();
		d[g[i][0]]++;d[g[i][1]]++;
	}
	for(int i=1;i<=m;i++){
		if(d[g[i][0]]<d[g[i][1]])swap(g[i][0],g[i][1]);
		else if(d[g[i][0]]==d[g[i][1]]&&g[i][0]>g[i][1])swap(g[i][0],g[i][1]);
		e[g[i][0]].push_back(g[i][1]);
	}
	for(int i=1;i<=n;i++){
		for(int u:e[i])vis[u]=i;
		for(int u:e[i]){
			for(int v:e[u])if(vis[v]==i)++ans;
		}
	}
	printf("%lld\n",ans);
}
