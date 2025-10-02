// Problem: AT_arc176_d [ARC176D] Swap Permutation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc176_d
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-10-02 20:51:58
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
const int maxk=4;
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
int n,m,a[maxn],l=3,ans;
struct mat{
	int e[maxk][maxk];
	mat(){memset(e,0,sizeof(e));}
}bas;
mat operator*(mat &u,mat &v){
	mat res;
	for(int i=0;i<l;i++){
		for(int k=0;k<l;k++){
			for(int j=0;j<l;j++)(res.e[i][j]+=u.e[i][k]*v.e[k][j])%=mod;
		}
	}
	return res;
}
mat one(){
	mat res;
	for(int i=0;i<l;i++)res.e[i][i]=1;
	return res;
}
mat qpow(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
int val[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	bas.e[0][0]=((n-2)*(n-3)/2+1)%mod,bas.e[1][0]=2*(n-2),bas.e[2][0]=0;
	bas.e[0][1]=1,bas.e[1][1]=((n-2)*(n-3)/2+n-3+2)%mod,bas.e[2][1]=n-3;
	bas.e[0][2]=0,bas.e[1][2]=4,bas.e[2][2]=((n-2)*(n-3)/2+2*(n-4)+1)%mod;
	bas=qpow(bas,m);
	// cout<<bas.e[0][0]<<" "<<bas.e[1][0]<<" "<<bas.e[2][0]<<"\n";
	int ni2=ksm(n-2),ni3=ksm(n-3);
	for(int i=1;i<=n;i++)val[i]=(i*(i-1)-(i-1)*i/2+(n-i)*(n+i+1)/2-i*(n-i))%mod;
	// for(int i=1;i<=n;i++)cout<<val[i]<<" ";cout<<"\n";
	int sum=0;for(int i=1;i<=n;i++)(sum+=val[i])%=mod;
	for(int i=1;i<n;i++){
		// cout<<val[a[i]]<<" "<<val[a[i+1]]<<" "<<abs(a[i]-a[i+1])<<"\n";
		(ans+=bas.e[0][0]*abs(a[i]-a[i+1]))%=mod;
		(ans+=bas.e[1][0]*(mod+1)/2%mod*(val[a[i]]-abs(a[i]-a[i+1])+mod)%mod*ni2)%=mod;
		(ans+=bas.e[1][0]*(mod+1)/2%mod*(val[a[i+1]]-abs(a[i]-a[i+1])+mod)%mod*ni2)%=mod;
		(ans+=bas.e[2][0]*(sum-2*(val[a[i]]+val[a[i+1]]-abs(a[i]-a[i+1])+mod)%mod+mod)%mod*ni2%mod*ni3)%=mod;
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