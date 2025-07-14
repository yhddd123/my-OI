// Problem: P6190 [NOI Online #1 入门组] 魔法
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6190
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
using namespace std;
const int maxn=110;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
struct mat{
	int e[maxn][maxn];
	mat(){
		memset(e,0x3f,sizeof(e));
		for(int i=1;i<=n;i++)e[i][i]=0;
	}
	mat operator *(const mat&tmp)const{
		mat res;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					res.e[i][j]=min(res.e[i][j],e[i][k]+tmp.e[k][j]);
				}
			}
		}
		return res;
	}
}ans;
int dis[maxn][maxn][2];
mat ksm(mat a,int b){
	mat ans;
	// for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans.e[i][j]=dis[i][j][0];
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();m=read();k=read();
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++)dis[i][i][0]=dis[i][i][1]=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		dis[u][v][0]=w,dis[u][v][1]=-w;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j][0]=min(dis[i][j][0],dis[i][k][0]+dis[k][j][0]);
				dis[i][j][1]=min({dis[i][j][1],dis[i][k][1]+dis[k][j][0],dis[i][k][0]+dis[k][j][1]});
			}
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans.e[i][j]=dis[i][j][1];
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)cout<<dis[i][j][1]<<" ";
		// cout<<"\n";
	// }
	ans=ksm(ans,k);
	printf("%lld\n",min(dis[1][n][0],ans.e[1][n]));
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)cout<<ans.e[i][j]<<" ";
		// cout<<"\n";
	// }
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
