#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=2110;
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
char s[maxn];
int e[maxn][maxn],g[maxn][maxn];
void add(){
	int num=m-n-3;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)g[i][j]=e[i][j];
		for(int j=1;j<=num;j++)if(i&(1<<j-1))g[i][n+j]=g[n+j][i]=1;
	}
	int a=n+num+1,b=n+num+2,c=n+num+3;
	for(int i=1;i<=b;i++)if(i!=a)g[i][a]=g[a][i]=1;
	for(int i=1;i<=n;i++)g[i][b]=g[b][i]=1;
	g[n+1][c]=g[c][n+1]=g[b][c]=g[c][b]=1;
	for(int i=1;i<num;i++)g[n+i][n+i+1]=g[n+i+1][n+i]=1;
}
bool vis[maxn],bk[maxn];
int d[maxn],id[maxn];
void del(){
	int num=n-m-3;
	int a=0,b=0,c=0;
	for(int i=1;i<=n;i++)d[i]=id[i]=vis[i]=bk[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(e[i][j])d[i]++;
		if(d[i]>d[a])a=i;
	}
	for(int i=1;i<=n;i++)if(i!=a&&!e[i][a])c=i;
	for(int i=1;i<=n;i++)if(e[i][c]){
		if(d[i]>=d[b])b=i;
	}
	// printf("%d %d %d\n",a,b,c);
	for(int i=1;i<=n;i++)if(e[i][b]&&i!=a&&i!=c)vis[i]=1;
	int p=0;for(int i=1;i<=n;i++)if(e[i][c]&&i!=b)p=i;
	for(int i=1;i<=num;i++){
		// printf("%d %d\n",i,p);
		for(int j=1;j<=n;j++)if(e[p][j]&&vis[j])id[j]+=(1<<i-1);
		bk[p]=1;
		for(int j=1;j<=n;j++)if(e[p][j]&&!vis[j]&&j!=a&&j!=c&&!bk[j]){p=j;break;}
	}
	for(int i=1;i<=n;i++)if(vis[i]&&!id[i])id[i]=m;
	// for(int i=1;i<=n;i++)printf("%d %d %d\n",i,vis[i],id[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(e[i][j]&&vis[i]&&vis[j])g[id[i]][id[j]]=1;
	}
}
void work(){
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)e[i][j]=s[j]-'0';
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++)g[i][j]=0;
	}
	if(n<m)add();
	else del();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++)printf("%d",g[i][j]);
		printf("\n");
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
	
	while(~scanf("%d%d",&n,&m))work();
}