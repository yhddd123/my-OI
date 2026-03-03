// Problem: P11835 [省选联考 2025] 封印
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11835
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-03-03 08:31:31
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=2510;
const int inf=1e9;
bool mbe;

inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,a[maxn<<2],ans;
int f[maxn],g[maxn],nxt[maxn];
int st[maxn],tp,sum[maxn],sumg[maxn];
int que(int l,int r){return (sum[r]+(l?mod-sum[l-1]:0))%mod;}
int queg(int l,int r){return (sumg[r]+(l?mod-sumg[l-1]:0))%mod;}
vector<pii> to[maxn];
void work(){
	n=read();m=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	bool fl=1;for(int i=1;i<=n;i++)fl&=(a[i]==1);
	if(fl){printf("%d\n",n);return ;}
	a[0]=a[n]+1;for(int i=n+1;i<=3*n;i++)a[i]=a[i-n]-1;
	nxt[n+1]=n+1;for(int i=n;~i;i--)nxt[i]=(a[i]>1)?i:nxt[i+1];
	// for(int i=1;i<=n;i++)cout<<nxt[i]<<" ";cout<<"\n";
	pii mx={0,0};for(int i=1;i<=n;i++)mx=max(mx,{a[i],i});
	for(int i=1;i<=n;i++)ans+=(i<mx.se&&a[i]==mx.fi)+(i>mx.se&&a[i]==mx.fi-1);
	for(int p=0;p<=n;p++)if(a[p]>1){
		for(int i=1;i<=n;i++)f[i]=g[i]=0;
		f[0]=0,g[0]=1;
		if(p<n){
			sum[0]=sumg[0]=0;
			if(nxt[p+1]!=p+1){
				if(nxt[p+1]<=n)inc(f[nxt[p+1]-p],g[0]);
				else sumg[0]=g[0];
			}
		}
		else sum[0]=f[0],sumg[0]=g[0];
		st[tp=0]=0;
		for(int i=1;i<=n;i++){
			if(a[p+i]>0)inc(f[i],f[i-1]),inc(a[p+i]==1?g[i]:f[i],g[i-1]);
			while(tp&&a[p+st[tp]]<a[p+i]){
				if(a[p+i]>0){
					inc(f[i],que(st[tp-1],st[tp]-1));
					inc(a[p+i]==1?g[i]:f[i],queg(st[tp-1],st[tp]-1));
				}
				tp--;
			}
			st[++tp]=i;
			if(p+i<n){
				sum[i]=sum[i-1],sumg[i]=sumg[i-1];
				if(nxt[p+i+1]!=p+i+1){
					if(nxt[p+i+1]<=n)inc(f[nxt[p+i+1]-p],g[i]);
					else inc(sumg[i],g[i]);
				}
			}
			else{
				inc(sum[i]=sum[i-1],f[i]);
				inc(sumg[i]=sumg[i-1],g[i]);
			}
		}
		// for(int i=0;i<n;i++){
			// if(p+i<n){
				// int k=nxt[p+i+1];
				// for(int j=i+1,mx=0;j<=n;j++)if(a[p+j]>0){
					// if(a[p+j]>mx){
						// if(j==i+1)inc(f[j],f[i]),inc(a[p+j]==1?g[j]:f[j],g[i]);
						// else if(k>n||k==p+j)inc(a[p+j]==1?g[j]:f[j],g[i]);
						// mx=a[p+j];
					// }
				// }
			// }
			// else{
				// for(int j=i+1,mx=0;j<=n;j++)if(a[p+j]>0){
					// if(a[p+j]>mx){
						// inc(f[j],f[i]);
						// inc(a[p+j]==1?g[j]:f[j],g[i]);
						// mx=a[p+j];
					// }
				// }
			// }
		// }
		inc(ans,f[n]);
		inc(ans,g[n]);
		// cout<<p<<" "<<ans<<"\n";
		// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
		// for(int i=1;i<=n;i++)cout<<g[i]<<" ";cout<<"\n";
	}
	for(int p=n+1;p<=3*n;p++)if(a[p]>0){
		for(int i=1;i<=n;i++)f[i]=g[i]=0;
		f[0]=g[0]=1;
		int l1=min(n,p-n-1),l2=min(n,3*n-p);
		st[tp=0]=l1;to[l1].clear();
		for(int i=l1-1;~i;i--){
			to[i].clear();
			while(tp&&a[p-st[tp]]<a[p-i]){
				to[i].pb({st[tp]+1,st[tp-1]});
				tp--;
			}
			st[++tp]=i;
		}
		for(int i=0;i<=l1;i++)sum[i]=0;
		sum[0]=1,sum[1]=mod-1;
		for(int i=0;i<=l1;i++){
			if(i){
				inc(sum[i],sum[i-1]);
				if(a[p-i]>a[p]){
					inc(g[i]=sum[i],g[i-1]);
				}
			}
			for(auto[l,r]:to[i])inc(sum[l],g[i]),inc(sum[r+1],mod-g[i]);
		}
		// for(int i=0;i<l1;i++){
			// for(int j=i+1,mx=0;j<=l1;j++){
				// if(mx<a[p-i]){
					// if(a[p-j]>a[p])inc(g[j],g[i]);
				// }
				// mx=max(mx,a[p-j]);
			// }
		// }
		sum[0]=f[0];st[tp=0]=0;
		for(int i=1;i<=l2;i++){
			if(a[p+i]>=a[p])inc(f[i],f[i-1]);
			while(tp&&a[p+st[tp]]<a[p+i]){
				if(a[p+i]>=a[p])inc(f[i],que(st[tp-1],st[tp]-1));
				tp--;
			}
			st[++tp]=i;
			inc(sum[i]=sum[i-1],f[i]);
		}
		// for(int i=0;i<l2;i++){
			// for(int j=i+1,mx=0;j<=l2;j++){
				// if(a[p+j]>mx){
					// if(a[p+j]>=a[p])inc(f[j],f[i]);
					// mx=a[p+j];
				// }
			// }
		// }
		for(int i=0,j=n;i<=l1;i++,j--)if(j<=l2){
			// cout<<i<<" "<<j<<" "<<g[i]<<" "<<f[j]<<"\n";
			inc(ans,1ll*g[i]*f[j]%mod*a[p]%mod);
		}
		// cout<<p<<" "<<ans<<" p\n";
		// for(int i=0;i<=l1;i++)cout<<g[i]<<" ";cout<<"\n";
		// for(int i=0;i<=l2;i++)cout<<f[i]<<" ";cout<<"\n";
	}
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	read();int T=read();
	while(T--)work();
}