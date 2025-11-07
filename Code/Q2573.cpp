#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=110;
const int inf=1e9;
bool mbe;

int n,k;
int f[2][maxn][maxn*maxn],o;
void work(){
	n=read();k=read();
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		memset(f[i&1],0,sizeof(f[i&1]));
		for(int j=0;j<i;j++){
			int jj=i-1-j;
			for(int s=0;s<=k;s++)if(f[o][j][s]){
				// cout<<i-1<<" "<<j<<" "<<s<<" "<<f[o][j][s]<<"\n";
				(f[i&1][j][s]+=f[o][j][s]*(n-j-2*jj)%mod*(n-j-2*jj-1))%=mod;
				if(s+i<=k)(f[i&1][j+1][s+i]+=f[o][j][s]*(n-j-2*jj))%=mod;
				if(s+i<=k)(f[i&1][j+1][s+i]+=f[o][j][s]*(n-j-2*jj)%mod*jj*2)%=mod;
				if(s+2*i<=k)(f[i&1][j+2][s+2*i]+=f[o][j][s]*jj%mod*jj)%=mod;
			}
		}
		o^=1;
	}
	printf("%lld\n",f[n&1][n][k]);
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