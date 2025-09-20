#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=20000010;
const int inf=1e9;
bool mbe;

int n,ans;
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
int calc(int n,int m,int l,int r){
	if(l>=0||r<=0)return 0;
	if(n+l>=m||n+r<=m)return 0;
	int res=0;
	for(int k=-(m+r-l-1)/(r-l);k<=n/(r-l);k++)(res+=C(n+m,n-k*(r-l)))%=mod;
	for(int k=-(m-r+r-l-1)/(r-l);k<=(n+r)/(r-l);k++)(res+=mod-C(n+m,n-k*(r-l)+r))%=mod;
	return res%mod;
}
void work(){
    n=read();ans=0;
    for(int l=-n;l<=0;l++){
    	for(int r=0;r-l<=n;r++)if(((l+r)&1)==(n&1)){
    		(ans+=calc((n+l+r)/2,(n-l-r)/2,-r,-l)+calc((n+l+r)/2,(n-l-r)/2,-r-1,-l+1)+mod-calc((n+l+r)/2,(n-l-r)/2,-r-1,-l)+mod-calc((n+l+r)/2,(n-l-r)/2,-r,-l+1))%=mod;
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
    
    T=read();init(maxn-10);
    while(T--)work();
}