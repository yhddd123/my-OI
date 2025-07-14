// Problem: P7606 [THUPC2021] 混乱邪恶
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7606
// Memory Limit: 512 MB
// Time Limit: 700000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=110;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,p,B=15,x,y;
bitset<35> dp[2][maxn][maxn][35];int cur;
int a[maxn][6][2];
int fx[6][2]={{0,1},{-1,0},{-1,-1},{0,-1},{1,0},{1,1}};
int inc(int u,int v){((u+=v)>=p)&&(u-=p);return u;}
void work(){
	n=read();p=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<6;j++)a[i][j][0]=read(),a[i][j][1]=read();
	}
	x=read(),y=read();
	srand(time(0));random_shuffle(a+1,a+n+1);
	dp[0][0][0][B][B]=1;
	// return;
	for(int i=1;i<=n;i++){
		for(int v0=0;v0<p;v0++)for(int v1=0;v1<p;v1++)for(int j=0;j<=2*B;j++)dp[i&1][v0][v1][j].reset();
		for(int v0=0;v0<p;v0++){
			for(int v1=0;v1<p;v1++){
				for(int j=0;j<=2*B;j++){
					dp[i&1][(v0+a[i][0][0])%p][(v1+a[i][0][1])%p][j]|=dp[cur][v0][v1][j]<<1;
					dp[i&1][(v0+a[i][1][0])%p][(v1+a[i][1][1])%p][j]|=dp[cur][v0][v1][j+1];
					dp[i&1][(v0+a[i][2][0])%p][(v1+a[i][2][1])%p][j]|=dp[cur][v0][v1][j+1]>>1;
					dp[i&1][(v0+a[i][3][0])%p][(v1+a[i][3][1])%p][j]|=dp[cur][v0][v1][j]>>1;
					dp[i&1][(v0+a[i][4][0])%p][(v1+a[i][4][1])%p][j]|=dp[cur][v0][v1][j-1];
					dp[i&1][(v0+a[i][5][0])%p][(v1+a[i][5][1])%p][j]|=dp[cur][v0][v1][j-1]<<1;
				}
			}
		}
		cur^=1;
	}
	if(dp[n&1][x][y][B][B])puts("Chaotic Evil");
	else puts("Not a true problem setter");
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
	
	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
