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
const int maxn=21;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
int n,ans[maxn+1];
int f[1<<maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void fmt1(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],a[j]);
		}
	}
}
void fmt2(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],mod-a[j]);
		}
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
int tf[maxn+1],tg[maxn+1],th[maxn+1];
int hh[maxn+1][1<<maxn];
void xormul1(int *a,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s^((1<<n)-1)];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++)tg[i]=gg[i][s];
		for(int i=0;i<=n;i++){
			th[i]=0;
			for(int j=0;j<=i;j++)inc(th[i],1ll*tf[j]*tg[i-j]%mod);
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)inc(c[s^((1<<n)-1)],ff[__builtin_popcount(s)][s]);
}
void comptrans(int *a,int *c,int n){
	hh[0][(1<<n)-1]=1;
	for(int i=n;i;i--){
		for(int j=0;j<i;j++){
			for(int s=0;s<(1<<i-1);s++)gg[j][s]=0;
		}
		for(int s=0;s<(1<<i-1);s++)gg[__builtin_popcount(s)][s]=a[s+(1<<i-1)];
		for(int j=0;j<i;j++)fmt1(gg[j],1<<i-1);
		for(int j=n-i+1;j;j--){
			xormul1(hh[j-1]+(1<<i-1),hh[j],i-1);
		}
	}
	for(int i=0;i<=n;i++)c[i]=hh[i][0];
}
int ni[maxn+1];
void work(){
	n=read();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int x=read();
			if(x)f[(1<<i)|(1<<j)]=1;
		}
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))f[s]|=f[s^(1<<i)];
	}
	for(int s=0;s<(1<<n);s++)f[s]^=1;
	// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	comptrans(f,ans,n);
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)ans[i]=1ll*ans[i]*j%mod;
	}
	for(int i=n;~i;i--){
		for(int j=i-1;~j;j--){
			int mul=1;
			for(int k=1;k<=j;k++)mul=1ll*mul*(i-k+1)%mod*ni[k]%mod;
			inc(ans[i],1ll*ans[j]*mul%mod);
		}
	}
	// for(int i=0;i<=n;i++)cout<<ans[i]<<" ";cout<<"\n";
	for(int i=0;i<=n+1;i++)tf[i]=tg[i]=0;tg[1]=1;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j;j--)tg[j]=mod-1ll*i*tg[j]%mod,inc(tg[j],tg[j-1]);
	}
	for(int i=1;i<=n+1;i++)th[i]=tg[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++)tg[j]=th[j];
		for(int j=1;j<=n+1;j++)inc(tg[j],mod-tg[j-1]),tg[j]=mod-1ll*tg[j]*ni[i]%mod;
		int mul=ans[i];for(int j=0;j<i;j++)mul=1ll*mul*ni[i-j]%mod;
		if((n-i)&1)mul=mod-mul;
		for(int j=i+1;j<=n;j++)mul=1ll*mul*ni[j-i]%mod;
		for(int j=1;j<=n;j++)inc(tf[j],1ll*tg[j]*mul%mod);
	}
	for(int i=0;i<=n;i++)printf("%lld ",tf[i]);
}

bool med;
signed main(){
	// freopen("cat.in","r",stdin);
	// freopen("cat.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}