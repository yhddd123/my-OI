#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
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

int n,mod,ans;
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
int calc(int x,int y,int xx,int yy){return C(xx-x+yy-y,xx-x);}
void work(){
    n=read();mod=read();init(2*n);
    for(int k=1;k<=n;k++){
    	ans=0;int val=0,r=-1;
	    for(int i=1;i<k;i++){
	        int res=C(k,i)*i%mod;
	        // cout<<i<<" "<<res<<"\n";
	        (res+=mod-C(k,i)*max(0ll,2*i-k)%mod)%=mod;
	        int lim=min(k-i,i)-1;
	        while(r<lim)r++,(val+=C(k,r))%=mod;
	        while(r>lim)(val+=mod-C(k,r))%=mod,r--;
	        (res+=mod-val)%=mod;
	        // for(int j=0;j<n-i&&j<i;j++)(res+=mod-C(n,j))%=mod;
	        (ans+=res*fac[i]%mod*fac[k-i])%=mod;
	        // cout<<i<<" "<<res<<" "<<ans<<"\n";
	    }
	    printf("%lld\n",ans);
    }
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