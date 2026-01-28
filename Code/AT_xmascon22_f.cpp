// Problem: AT_xmascon22_f Fast as Fast as Ryser
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_xmascon22_f
// Memory Limit: 2048 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2026-01-28 17:01:25
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ull unsigned long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline ull read(){
	ull x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
const int maxn=20;
const int inf=1e9;
bool mbe;

ull ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
void fmt1(ull *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]+=a[j];
		}
	}
}
void fmt2(ull *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]-=a[j];
		}
	}
}
ull tf[maxn+1],tg[maxn+1],th[maxn+1];
void xormul(ull *a,ull *b,ull *c,int n){
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
			th[i]=0;
			for(int j=0;j<=i;j++)th[i]+=tf[j]*tg[i-j];
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)c[s]+=ff[__builtin_popcount(s)][s];
}
void exp(ull *a,ull *b,int n){
	b[0]=1;
	for(int i=0;i<n;i++)xormul(a+(1<<i),b,b+(1<<i),i);
}
void xormul1(ull *a,ull *c,int n){
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
			for(int j=0;j<=i;j++)th[i]+=tf[j]*tg[i-j];
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)c[s^((1<<n)-1)]+=ff[__builtin_popcount(s)][s];
}
ull hh[maxn+1][1<<maxn];
void comptrans(ull *a,ull *b,ull *c,int n){
	for(int s=0;s<(1<<n);s++)hh[0][(1<<n)-1-s]=b[s];
	for(int i=n;i;i--){
		for(int j=0;j<i;j++){
			for(int s=0;s<(1<<i-1);s++)gg[j][s]=0;
		}
		for(int s=0;s<(1<<i-1);s++)gg[__builtin_popcount(s)][s]=a[s+(1<<i-1)];
		for(int j=0;j<i;j++)fmt1(gg[j],1<<i-1);
		for(int j=n-i+1;j;j--){
			xormul1(hh[j-1]+(1<<i-1),hh[j],i-1);
		}
		// cout<<i<<"\n";
		// for(int j=0;j<=n-i+1;j++){
			// for(int s=0;s<(1<<n);s++)cout<<hh[j][s]<<" ";cout<<"\n";
		// }
	}
	for(int i=0;i<=n;i++)c[i]=hh[i][0];
	// for(int i=0;i<=n;i++)cout<<c[i]<<" ";cout<<"\n";
}

int n,N;ull a[maxn<<1][maxn<<1];
ull msk[1<<maxn];
ull f[1<<maxn][maxn<<1],g[1<<maxn],h[1<<maxn];
ull ans[maxn+1];
void work(){
	N=n=read();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)a[i][j]=read();
	}
	if(n&1)n++;
	for(int s=0;s<(1<<n/2);s++){
		for(int i=0;i<n/2;i++)if(!(s&(1<<i)))msk[s]|=(1ll<<2*i)|(1ll<<2*i+1);
	}
	for(int mx=2;mx<=n;mx+=2){
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++)mems(f[s],0);
		f[1<<mx/2-1][mx-2]=1;
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++){
			for(int i=0;i<mx;i++)if(f[s][i]){
				for(ull t=msk[s]&((1ll<<mx)-1);t;t&=t-1){
					int j=__builtin_ctzll(t);
					f[s^(1<<j/2)][j^1]+=f[s][i]*a[i][j];
				}
				h[s]+=f[s][i]*a[mx-1][i];
				// cout<<s<<" "<<i<<" "<<f[s][i]<<" "<<(e[i]&(1<<mx-1))<<"\n";
			}
		}
	}
	exp(h,g,n/2);
	for(int s=0;s<(1<<n/2);s++)h[s]=g[s],g[s]=0;
	for(int mx=2;mx<=n;mx+=2){
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++)mems(f[s],0);
		f[1<<mx/2-1][mx-2]=1;
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++){
			for(int i=0;i<mx;i++)if(f[s][i]){
				for(ull t=msk[s]&((1ll<<mx)-1);t;t&=t-1){
					int j=__builtin_ctzll(t);
					f[s^(1<<j/2)][j^1]+=f[s][i]*a[i][j];
				}
				// cout<<s<<" "<<i<<" "<<f[s][i]<<" "<<(e[i]&(1<<mx-1))<<"\n";
			}
			for(int i=0;i<mx-1;i++)if(f[s][i])f[s][mx-1]+=f[s][i],f[s][i]=0;
		}
		for(int s=(1<<mx/2-1);s<(1<<mx/2);s++){
			for(int i=0;i<mx;i++)if(f[s][i]){
				for(ull t=msk[s]&((1ll<<mx)-1);t;t&=t-1){
					int j=__builtin_ctzll(t);
					f[s^(1<<j/2)][j^1]+=f[s][i]*a[i][j];
				}
				g[s]+=f[s][i];
				// cout<<s<<" "<<i<<" "<<f[s][i]<<" "<<(e[i]&(1<<mx-1))<<"\n";
			}
		}
	}
	// for(int s=0;s<(1<<n/2);s++)cout<<g[s]<<" ";cout<<"\n";
	// for(int s=0;s<(1<<n/2);s++)cout<<h[s]<<" ";cout<<"\n";
	comptrans(g,h,ans,n/2);
	reverse(ans,ans+n/2+1);
	for(int i=0;i<=N/2;i++)printf("%llu ",ans[i]);
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