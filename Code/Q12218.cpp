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
const int maxn=21;
const int inf=1e9;
bool mbe;

int n,k;
int C[maxn][maxn];
int val[maxn][maxn];
void work(){
	n=read();k=read();
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int i=0;i<=n;i++){
		for(int j=i;~j;j--)val[i][j]=val[i][j+1]+C[i][j];
	}
	vector<pii> e;
	for(int i=n;i;i--){
		for(int j=i;j;j--){
			// cout<<i<<" "<<j<<" "<<val[i-1][j-1]<<" "<<k<<"\n";
			if(k-val[i-1][j]<(1<<i-1)){
				for(int p=1;p<=j;p++)e.pb({i,p});
				k-=val[i-1][j];
				break;
			}
		}
	}
	printf("%d\n",e.size());
	for(auto[u,v]:e)printf("%d %d\n",u,v);
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