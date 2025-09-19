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
const int maxn=1<<15;
const int inf=1e9;
bool mbe;

void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
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
int n,k;
int fac[maxn],inv[maxn];
void work(){
    n=read();k=read();
    fac[0]=1;for(int i=1;i<=k;i++)fac[i]=fac[i-1]*i%mod;
    inv[k]=ksm(fac[k]);for(int i=k-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    vector<int> f(k+1),g(k+1);
    for(int i=0,mul=1;i<=k;i++,mul=mul*(n-i+1)%mod)f[i]=((i&1)?mod-1:1)*inv[i]%mod*ksm(mul)%mod;
    for(int i=0;i<=k;i++)g[i]=inv[i]*inv[i]%mod*ksm(2,i)%mod;
    f=poly::mul(f,g);
    for(int i=1,mul=n;i<=k&&i<=n;i++,mul=mul*(n-i+1)%mod){
        int ans=f[i]*fac[i]%mod*mul%mod;
        printf("%lld ",ans);
    }
    for(int i=n+1;i<=k;i++)putchar('0'),putchar(' ');
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