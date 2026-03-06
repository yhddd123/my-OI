// Problem: AT_agc049_e [AGC049E] Increment Decrement
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc049_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-03-05 15:10:36
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=55;
const int inf=1e9;
bool mbe;

int n,c,m,a[maxn][maxn],ans;
int lsh[maxn*maxn],len;
vector<int> upd[maxn*maxn];
int tim[maxn];
int f[maxn][maxn<<1],g[maxn][maxn<<1];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();c=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i][j]=read(),lsh[++len]=a[i][j];
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int p=lower_bound(lsh+1,lsh+len+1,a[i][j])-lsh;
			upd[p].pb(i);
		}
	}
	for(int i=1;i<=n;i++)tim[i]=m;
	for(int v=1;v<=len;v++){
		mems(f,0),mems(g,0);
		f[0][maxn-c]=1;
		for(int i=1;i<=n;i++){
			for(int j=-c-1;j<maxn;j++)if(f[i-1][j+maxn]||g[i-1][j+maxn]){
				if(tim[i]){
					int d=1+min(-j,0);
					int jj=d-min(c,-j);
					inc(f[i][jj+maxn],1ll*f[i-1][j+maxn]*tim[i]%mod);
					inc(g[i][jj+maxn],1ll*g[i-1][j+maxn]*tim[i]%mod);
					inc(g[i][jj+maxn],1ll*f[i-1][j+maxn]*(d+mod)%mod*tim[i]%mod);
				}
				if(tim[i]<m){
					int d=min(-j,0);
					int jj=d-1-min(c,-j);
					inc(f[i][jj+maxn],1ll*f[i-1][j+maxn]*(m-tim[i])%mod);
					inc(g[i][jj+maxn],1ll*g[i-1][j+maxn]*(m-tim[i])%mod);
					inc(g[i][jj+maxn],1ll*f[i-1][j+maxn]*(d+mod)%mod*(m-tim[i])%mod);
				}
			}
		}
		int res=0;
		for(int j=-c-1;j<maxn;j++){
			if(j>0)inc(res,1ll*f[n][j+maxn]*(mod-j)%mod);
			inc(res,g[n][j+maxn]);
		}
		inc(ans,1ll*res*(lsh[v]-lsh[v-1])%mod);
		// cout<<res<<"\n";
		for(int p:upd[v])tim[p]--;
	}
	printf("%d\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}