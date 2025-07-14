#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=250;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
double p[maxn],pw[maxn][maxn];
int d[maxn];
double f[maxn][maxn],g[maxn],ans;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		n=read();m=read();
		for(int i=1;i<=n;i++){
			scanf("%lf",&p[i]);
			d[i]=read();
		}
		for(int i=1;i<=n;i++){
			pw[i][0]=1.0;
			for(int j=1;j<=m;j++)pw[i][j]=1.0*pw[i][j-1]*(1.0-p[i]);
		}
		f[1][0]=pw[1][m];f[1][1]=1.0-pw[1][m];
		for(int i=2;i<=n;i++){
			for(int j=0;j<=i;j++){
				f[i][j]=0.0;
				if(j)f[i][j]=f[i-1][j-1]*(1.0-pw[i][m-j+1]);
				if(i!=j)f[i][j]+=f[i-1][j]*pw[i][m-j];
			}
		}
		g[1]=f[1][1];ans=f[1][1]*d[1];
		for(int i=2;i<=n;i++){
			g[i]=0.0;
			for(int j=0;j<=min(i-1,m-1);j++)g[i]+=f[i-1][j]*(1.0-pw[i][m-j]);
			ans+=g[i]*d[i];
		}
		printf("%.10lf\n",ans);
	}
}
