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
const int maxn=200010;
const int maxm=910;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
int f[maxn][maxm],p[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		int u=read(),v=read();
		a[u]=v,a[v]=u;
	}
	for(int i=1;i<=2*n+1;i++){
		f[i][0]=i-1;
		for(int j=1;j<=maxm-10;j++)f[i][j]=2*n+1;
	}
	for(int j=1;j<=maxm-10;j++){
		for(int i=2*n;i;i--){
			f[i][j]=f[i+1][j];
			if(i<=a[i]){
				while(p[i]<j&&f[i+1][p[i]+1]<a[i])p[i]++;
				// cout<<i<<" "<<p[i]<<"\n";
				if(p[i]<j)f[i][j]=min(f[i][j],f[a[i]+1][j-1-p[i]]);
			}
		}
		if(f[1][j]<=2*n)ans=j;
	}
	printf("%d\n",ans);
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