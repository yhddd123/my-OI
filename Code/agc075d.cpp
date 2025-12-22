// Problem: D - Max Prod Plus
// Contest: AtCoder - AtCoder Grand Contest 075
// URL: https://atcoder.jp/contests/agc075/tasks/agc075_d
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-12-21 20:50:14
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int n,m,lim,ans;
int calc(int v1,int v2,int n){
	if(v1==v2)return (n+1)*ksm(v1,n)%mod;
	if(v1<v2)swap(v1,v2);
	return (ksm(v1,n+1)+mod-ksm(v2,n+1))*ksm(v1-v2)%mod;
}
int calc1(int v1,int v2,int n){
	if(v1==v2)return n*(n+1)/2%mod*ksm(v1,n)%mod;
	// int res=0;
	// for(int i=0;i<=n;i++)(res+=i*ksm(v1,i)%mod*ksm(v2,n-i))%=mod;
	// return res;
	return (n*ksm(v1,n+1)+mod-(n+1)*ksm(v1,n)%mod*v2%mod+v1*ksm(v2,n))%mod*ksm((v1-v2)*(v1-v2)%mod)%mod;
}
void work(){
	n=read();m=read(),lim=read();
	for(int i=1;i<=m;i++){
		for(int j=1;j<i&&i*j<=lim;j++){
			for(int k=1;k<=i&&i*j+k<=lim&&i*k<=lim;k++){
				int v=min(k,lim-i*k);
				int t=min(i,lim-i*max(j,k));
				// cout<<i<<" "<<j<<" "<<k<<" "<<v<<" "<<t<<"\n";
				if(v==k){
					int res=(calc(j,k,n-2)+mod-calc(j-1,k,n-2)+mod-calc(j,k-1,n-2)+calc(j-1,k-1,n-2))%mod;
					(ans+=res*t)%=mod;
				}
				else if(v==k-1){
					int res=(calc(j,k-1,n-3)+mod-calc(j-1,k-1,n-3))*(n-2)%mod;
					if(n<=5){
						for(int p=0;p<=n-3;p++){
							int res=(ksm(j,p)+mod-ksm(j-1,p))%mod;
							res=res*p%mod*ksm(k-1,n-p-3)%mod;
							(ans+=mod-res*t%mod)%=mod;
						}
					}
					else (res+=mod-(calc1(j,k-1,n-3)+mod-calc1(j-1,k-1,n-3))%mod)%=mod;
					(ans+=res*t)%=mod;
				}
				else{
					int res=(calc(j,k-1,n-2)+mod-calc(j-1,k-1,n-2)+mod-calc(j,v,n-2)+calc(j-1,v,n-2))%mod*ksm(k-1-v)%mod;
					(ans+=res*t)%=mod;
				}
			}
			int res=(ksm(j,n-2)+mod-ksm(j-1,n-2))%mod;
			res=res*min(i,lim-i*j)%mod;
			(ans+=res)%=mod;
		}
	}
	// cout<<ans<<"\n";
	for(int i=1;i<=m;i++){
		for(int k=1;k<=i&&i*k<=lim;k++){
			int v=min(k,lim-i*k);
			int t=min(i,lim-i*k);
			int res=1;
			if(v==k)res=res*(ksm(k,n-2)+mod-ksm(k-1,n-2))%mod;
			else if(v==k-1)res=res*(n-2)%mod*ksm(k-1,n-3)%mod;
			else res=res*(ksm(k-1,n-2)+mod-ksm(v,n-2))%mod*ksm(k-1-v)%mod;
			(ans+=res*t)%=mod;
			// cout<<i<<" "<<k<<" "<<v<<" "<<res<<"\n";
		}
	}
	// cout<<ans<<"\n";
	for(int i=1;i<=m;i++){
		if(i*i+i+1<=lim){
			int x=min(m,lim-i*i)-i;
			int res=(ksm(i,n-1)+mod-ksm(i-1,n-1)+mod-(n-1)*ksm(i-1,n-2)%mod)%mod;
			(ans+=res*x)%=mod;
			// cout<<ans<<" "<<res<<" "<<x<<"\n";
		}
		for(int j=1;j<i&&i*j+i+1<=lim;j++){
			int x=min(m,lim-i*j)-i;
			int res=(n-1)*(ksm(j,n-2)+mod-ksm(j-1,n-2))%mod;
			// cout<<i<<" "<<j<<" "<<res<<" "<<x<<"\n";
			(ans+=res*x)%=mod;
		}
	}
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