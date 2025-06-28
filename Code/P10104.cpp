// Problem: P10104 [GDKOI2023 提高组] 异或图
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10104
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-05-30 11:50:38
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
const int maxn=15;
const int inf=1e9;
bool mbe;

int n,m,c,a[maxn],ans;
int e[1<<maxn],mn[1<<maxn];
void fmt(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)]*w)%=mod;
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1],ni[maxn+1];
void xorln(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			gg[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(gg[i]+=mod-ff[j][s]*gg[i-j]%mod)%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=gg[i-1]*ni[i]%mod;
	}
	for(int i=1;i<=n;i++)fmt(ff[i],n,mod-1);
	b[0]=0;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
int f[1<<maxn],g[1<<maxn],coef[1<<maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int calc(vector<int> a){
	int n=a.size();
	int s=0;for(int v:a)s^=v;
	int ans=(s==0);
	for(int d=59;~d;d--){
		int f[2][2],g[2][2];
		for(auto j:{0,1})for(auto k:{0,1})f[j][k]=g[j][k]=0;f[0][0]=1;
		bool fl=0;
		for(int i=0;i<n;i++){
			for(auto j:{0,1})for(auto k:{0,1})g[j][k]=0;
			if(a[i]&(1ll<<d)){
				fl^=1;a[i]^=1ll<<d;
				for(auto j:{0,1})for(auto k:{0,1}){
					(g[j^1][k]+=f[j][k]*((a[i]+1)%mod))%=mod;
					(g[j][k|1]+=f[j][k]*((1ll<<d)%mod))%=mod;
				}				
			}
			else{
				for(auto j:{0,1})for(auto k:{0,1}){
					(g[j][k]+=f[j][k]*((a[i]+1)%mod))%=mod;
				}
			}
			swap(f,g);
		}
		(ans+=f[0][1]*ksm((1ll<<d)%mod))%=mod;
		if(fl)break;
	}
	return ans;
}
int calc(int s){
	vector<int> v;
	for(int i=0;i<n;i++)if(s&(1<<i))v.pb(a[i]);
	if(c==0)return calc(v);
	int ans=0;
	v.pb(c);ans=calc(v);
	v.back()--;(ans+=mod-calc(v))%=mod;
	return ans;
}
int id[maxn],rnk[maxn];
void work(){
	n=read();m=read();c=read();
	for(int i=0;i<n;i++)a[i]=read(),id[i]=i;
	sort(id,id+n,[&](int u,int v){return a[u]<a[v];});for(int i=0;i<n;i++)rnk[id[i]]=i;
	sort(a,a+n);
	for(int i=1;i<=m;i++){
		int u=rnk[read()-1],v=rnk[read()-1];
		e[(1<<u)|(1<<v)]++;
	}
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	fmt(e,n,1);
	for(int s=0;s<(1<<n);s++)if(!e[s])coef[s]=1;
	xorln(coef,coef,n);
	// for(int s=0;s<(1<<n);s++)cout<<coef[s]<<" ";cout<<"\n";
	f[0]=1;
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(f[s]){
			int ss=((1<<i)-1)|(s&((1<<n)-(1<<i)));
			if(ss&(1<<i))(g[s^(1<<i)]+=f[s])%=mod;
			else{
				for(int tt=((1<<n)-1)^(1<<i)^ss,t=tt;;t=(t-1)&tt){
					if(__builtin_popcount(t|(1<<i))&1)(g[s|(1<<i)|t]+=f[s]*coef[t|(1<<i)])%=mod;
					else (g[s|t]+=f[s]*coef[t|(1<<i)]%mod*((a[i]+1)%mod))%=mod;
					if(!t)break;
				}
			}
		}
		for(int s=0;s<(1<<n);s++)f[s]=g[s],g[s]=0;
	}
	// for(int s=0;s<(1<<n);s++)cout<<s<<" "<<f[s]<<" "<<calc(s)<<"\n";
	for(int s=0;s<(1<<n);s++)(ans+=f[s]*calc(s))%=mod;
	printf("%lld\n",ans);
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