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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,w,ans;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn],pw[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*w%mod;
}
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
	int gg=3,invg=ksm(gg);
	int to[maxn<<3];
	vector<int> ntt(vector<int> a,int flag){
		int n=a.size();
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int len=2;len<=n;len<<=1){
			int bas=ksm(flag==1?gg:invg,(mod-1)/len),l=len>>1;
			for(int i=0;i<n;i+=len){
				int mul=1;
				for(int j=i;j<i+l;j++){
					int val=mul*a[j+l]%mod;
					inc(a[j+l]=a[j],mod-val);
					inc(a[j],val);
					mul=mul*bas%mod;
				}
			}
		}
		if(flag==-1){
			int inv=ksm(n);
			for(int i=0;i<n;i++)a[i]=a[i]*inv%mod;
		}
		return a;
	}
	vector<int> mul(vector<int> a,vector<int> b){
		int n=a.size()-1,m=b.size()-1;int k=1;
		while(k<n+m+1)k<<=1;
		vector<int> f(k),g(k);
		for(int i=0;i<=n;i++)f[i]=a[i];
		for(int i=0;i<=m;i++)g[i]=b[i];
		for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
		f=ntt(f,1),g=ntt(g,1);
		for(int i=0;i<k;i++)f[i]=f[i]*g[i]%mod;
		f=ntt(f,-1);f.resize(n+m+1);
		return f;
	}
	vector<int> add(vector<int> a,vector<int> b){
		int n=a.size()-1,m=b.size()-1;
		vector<int>f(max(n,m)+1);
		for(int i=0;i<=n;i++)f[i]=a[i];
		for(int i=0;i<=m;i++)inc(f[i],b[i]);
		return f;
	}
}
using poly::mul;
int dp[maxn];
void sovle(int l,int r){
    if(l==r)return ;
    int mid=l+r>>1;
    sovle(l,mid);
    vector<int> f(mid-l+1),g(r-l+1);
    for(int i=l;i<=mid;i++)f[i-l]=dp[i-1]*inv[i-1]%mod;
    for(int i=1;i<=r-l;i++)g[i]=inv[i+1]*i%mod*pw[i-1]%mod;
    f=poly::mul(f,g);
    for(int i=mid+1;i<=r;i++)(dp[i]+=f[i-l]*fac[i])%=mod;
    sovle(mid+1,r);
}
void work(){
    n=read();w=read();init(n);
    dp[0]=1;
    // for(int i=2;i<=n;i++){
        // for(int j=1;j<i;j++)(dp[i]+=dp[j-1]*C(i,i-j+1)%mod*(i-j)%mod*pw[i-j-1])%=mod;
    // }
    sovle(1,n);
    for(int i=0;i<=n;i++)(ans+=dp[i]*C(n,i)%mod*pw[n-i])%=mod;
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