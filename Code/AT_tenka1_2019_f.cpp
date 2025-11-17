#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n,x,mod,ans;
int f[maxn][maxn<<1];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int C[maxn][maxn];
int g[maxn],h[maxn];
void work(){
	n=read();x=read();mod=read();
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	f[0][0]=1;for(int i=1;i<=n;i++){
		for(int j=0;j<=2*(i-1)&&j<x;j++)if(f[i-1][j]){
			inc(f[i][j],f[i-1][j]);
			inc(f[i][j+1],f[i-1][j]);
			inc(f[i][j+2],f[i-1][j]);
		}
	}
	for(int j=0;j<x;j++)inc(ans,f[n][j]);
	auto upd=[&](int l,int r,int w){
		if(l>r)return ;
		inc(h[l],w),inc(h[r+1],mod-w);
	};
	if(x&1){
		for(int k=x/2+1;k<=n;k++)(ans+=C[n][k])%=mod;
		for(int i=0;i<x-1;i+=2){
			for(int j=0;i+2*j<x-1&&i+j+2<=n;j++){
				int v=(x-1-i-2*j-1)/2;
				int pl=(x-i-2*j-2)/2+1,pr=min(2*v,n-i-j-2),w=C[i+j][i];
				if(pl>pr)continue;
				(g[i+j+2+pl]+=w*(min(pl,2*v-pl)+1))%=mod;
				upd(i+j+2+pl+1,i+j+2+min(v,pr),w);
				upd(i+j+2+max(pl+1,v+1),i+j+2+pr,mod-w);
				(g[i+j+2+pr+1]+=mod-w*(min(pr,2*v-pr)+1)%mod)%=mod;
			}
		}
		for(int i=1;i<=n;i++){
			inc(h[i],h[i-1]),inc(g[i],h[i]),inc(g[i],g[i-1]);
			(ans+=C[n][i]*g[i])%=mod;
		}
	}
	else{
		int v=x/2-1;
		for(int k=0;k<=2*v;k++)if(2*k+1>=x&&k+1<=n)(ans+=C[n][k+1]*(min(k,2*v-k)+1))%=mod;
		for(int i=1;i<x-1;i+=2){
			for(int j=0;i+2*j<x-1&&i+j+2<=n;j++){
				int v=(x-1-i-2*j-1)/2;
				int pl=(x-i-2*j-2)/2+1,pr=min(2*v,n-i-j-2),w=C[i+j][i];
				if(pl>pr)continue;
				(g[i+j+2+pl]+=w*(min(pl,2*v-pl)+1))%=mod;
				upd(i+j+2+pl+1,i+j+2+min(v,pr),w);
				upd(i+j+2+max(pl+1,v+1),i+j+2+pr,mod-w);
				(g[i+j+2+pr+1]+=mod-w*(min(pr,2*v-pr)+1)%mod)%=mod;
			}
		}
		for(int i=1;i<=n;i++){
			inc(h[i],h[i-1]),inc(g[i],h[i]),inc(g[i],g[i-1]);
			(ans+=C[n][i]*g[i])%=mod;
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("sequence.in","r",stdin);
	// freopen("sequence.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}