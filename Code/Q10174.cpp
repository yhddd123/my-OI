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
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,m,a[maxn],b[maxn],ans=1;
void work(){
	n=read();m=read();init(max(n,m));
	for(int i=1;i<=n;i++)a[i]=read()-1;
	for(int i=1;i<=m;i++)b[i]=read()-1;
	sort(a+1,a+n+1,greater<int>()),sort(b+1,b+m+1,greater<int>());
	int l1=1,l2=1;
	while(l1<=n||l2<=m){
		int r1=l1-1,r2=l2-1;
		int v=max(a[l1],b[l2]);
		while(r1<n&&a[r1+1]==v)r1++;
		while(r2<m&&b[r2+1]==v)r2++;
		int ni=v*ksm(v+1)%mod;
		int res=0;for(int i=0;i<=r1-l1+1;i++){
		(res+=C(r1-l1+1,i)*((i&1)?mod-1:1)%mod*ksm(v,i*r2)%mod*ksm(v+1,r1*r2-(l1-1)*(l2-1)-i*r2)%mod*ksm(1+mod-ksm(ni,r1-i),r2-l2+1))%=mod;
		}
		// cout<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<" "<<res<<"\n";
		ans=ans*res%mod;
		l1=r1+1,l2=r2+1;
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