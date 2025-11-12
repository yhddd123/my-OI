#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=6010;
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
void work(){
	n=read();m=read();init(maxn-10);
	for(int a=0;a<=n;a++){
		int b=n-a,d=b+n-m,c=m-d;
		if(!(0<=c&&c<=m&&0<=d&&d<=m))continue;
		int res=0;
		for(int t=0;t<=b&&t<=d;t++){
			(res+=((t&1)?mod-1:1)*C(b,t)%mod*C(d,t)%mod*fac[t]%mod*fac[c+2*(d-t)]%mod*ksm(2,mod-1-(d-t)))%=mod;
		}
		(ans+=C(n,a)*C(m,c)%mod*res%mod*ksm(2,mod-1-b))%=mod;
		// cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<res<<"\n";
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