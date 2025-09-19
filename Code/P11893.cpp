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
const int maxn=10000010;
const int inf=1e9;
bool mbe;

int l,n,n1,n2,ans;
char s[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
// int fac[maxn],inv[maxn],pw[maxn];
// int C(int m,int n){
    // if(n<0|m<0||m<n)return 0;
    // return fac[m]*inv[n]%mod*inv[m-n]%mod;}
// void init(int n){
    // fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    // inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    // pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
// }
void work(){
	// read();n=read();init(n);
	l=read();scanf("%s",s+1);
	for(int i=1;i<=l;i++){
		n1=n1*10+s[i]-'0',n2=n2*10+s[i]-'0';
		if(i%9==0)n1%=mod,n2%=mod-1;
	}
	n1%=mod,n2%=mod-1;
	if(l>=10)n1+=mod,n2+=mod-1;
	(ans+=2*(n1-1)*(n1-2)%mod*ksm(3,n2-3))%=mod;
	(ans+=mod-2*(n1-1)*(n1-2)%mod*(ksm(2,n2-3)+1)%mod)%=mod;
	(ans+=mod-(n1-1)*(n1-2)%mod*(ksm(2,n2-3)-2)%mod)%=mod;
	// for(int i=2;i<=n-3;i++)(ans+=2*(n-1)*(n-2)%mod*C(n-3,i-1)%mod*(pw[n-i-2]))%=mod;
	(ans+=(mod-n1+2)*ksm(3,n2-1)%mod)%=mod;
	(ans+=mod-(mod-n1+2)*(ksm(2,n2-1)+(n1-1)*ksm(2,n2-2)%mod+(n1-1)*2+1)%mod)%=mod;
	(ans+=mod-(mod-n1+2)*(ksm(2,n2-1)-2*n1)%mod)%=mod;
	// for(int i=2;i<=n-3;i++)(ans+=C(n-1,i)*(mod-n+2)%mod*(pw[n-i-1]))%=mod;
	// for(int i=2;i<=n-3;i++)(ans+=C(n-1,i)*(i-1)%mod*(n-i-2)%mod*(pw[n-i-1]-1))%=mod;
	ans%=mod,ans+=mod,ans%=mod;
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