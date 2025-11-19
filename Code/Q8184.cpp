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
const int maxn=510;
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
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,m,ans;
int f[maxn];
int pre[maxn],suf[maxn];
int calc(int k,int v){
	if(v<=k)return f[v];
	int res=0;
	pre[0]=1;for(int i=1;i<=k;i++)pre[i]=pre[i-1]*((v-i+mod)%mod)%mod;
	suf[k+1]=1;for(int i=k;~i;i--)suf[i]=suf[i+1]*((v-i+mod)%mod)%mod;
	for(int i=1;i<=k;i++){
		int val=pre[i-1]*suf[i+1]%mod*f[i]%mod*inv[i-1]%mod*inv[k-i]%mod;
		if((k-i)&1)(res+=mod-val)%mod;
		else (res+=val)%=mod;
	}
	return res;
}
int Ccalc(int n,int m){
	if(n<m)return 0;
	int res=1;for(int i=n;i>=n-m+1;i--)res=res*(i%mod)%mod;
	res=res*inv[m]%mod;
	return res;
}
void work(){
	n=read();m=read();init(m);
	for(int i=1;i<m;i++){
		for(int j=1;j<=m+1;j++)f[j]=(f[j-1]+Ccalc(n-i*j-1,m-i-1))%mod;
		(ans+=(((i-1)&1)?mod-1:1)*C(m,i)%mod*calc(m+1,(n-m)/i+1))%=mod;
	}
	printf("%lld\n",(ans+(n%m==0)*((m&1)?1:mod-1))%mod);
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