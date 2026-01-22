#include<bits/stdc++.h>
// #define int long long
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
const int maxn=20010;
const int inf=1e9;
bool mbe;

int n,c,a[maxn],B=maxn-10;
// int f[maxn][maxn][maxn<<1];
int g[2][maxn<<1];
inline void chkmx(int &u,int v){(u<v)&&(u=v);}
void work(){
	n=read();c=read();
	for(int i=1;i<=n;i++)a[i]=read();a[n+1]=0;
	int p=-1,sum=0;for(int i=1;i<=n;i++){
		if(sum+a[i]>c){p=i-1;break;}
		sum+=a[i];
	}
	if(p==-1){printf("%lld\n",sum);return ;}
	// mems(f,0);
	// f[p+1][p][sum-c+B]=1;
	// for(int i=p+1;i;i--){
		// for(int j=p;j<=n;j++){
			// for(int k=-B;k<=B;k++)if(f[i][j][k+B]){
				// f[i][j+1][k+B]=1;
				// f[i-1][j][k+B]=1;
				// if(k<=0)f[i][j+1][k+a[j+1]+B]=1;
				// elsef[i-1][j][k-a[i-1]+B]=1;
			// }
		// }
	// }
	for(int o=0;o<2;o++)for(int k=-B;k<=B;k++)g[o][k+B]=0;
	g[p&1][sum-c+B]=p+1;
	for(int j=p+1;j<=n;j++){
		for(int k=-B;k<=B;k++)g[j&1][k+B]=g[(j-1)&1][k+B];
		for(int k=-B;k<=0;k++)chkmx(g[j&1][k+a[j]+B],g[(j-1)&1][k+B]);
		for(int k=B;k;k--){
			for(int i=g[(j-1)&1][k+B];i<g[j&1][k+B];i++)chkmx(g[j&1][k-a[i]+B],i);
		}
	}
	for(int i=0;i>=-B;i--)if(g[n&1][i+B]){printf("%lld\n",c+i);break;}
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