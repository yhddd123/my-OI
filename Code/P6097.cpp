#include<bits/stdc++.h>
// #define int long long
#define mod 1000000009ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=21;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[1<<maxn],b[1<<maxn],c[1<<maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
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
int tf[maxn+1],tg[maxn+1],hh[maxn+1];
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fmt1(gg[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++)tg[i]=gg[i][s];
		for(int i=0;i<=n;i++){
			hh[i]=0;
			for(int j=0;j<=i;j++)inc(hh[i],1ll*tf[j]*tg[i-j]%mod);
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)inc(c[s],ff[__builtin_popcount(s)][s]);
}
void work(){
	n=read();
	for(int s=0;s<(1<<n);s++)a[s]=read();
	for(int s=0;s<(1<<n);s++)b[s]=read();
	xormul(a,b,c,n);
	for(int s=0;s<(1<<n);s++)printf("%lld ",c[s]);
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