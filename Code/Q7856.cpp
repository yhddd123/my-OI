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
const int maxn=1000010;
const int maxm=20;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
    int gen=3,invg=ksm(3);
    int to[maxn<<3];
    void ntt(vector<int> &a,int fl){
        int n=a.size();
        for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
        for(int l=2;l<=n;l<<=1){
            int bas=ksm(fl==1?gen:invg,(mod-1)/l),k=l>>1;
            for(int i=0;i<n;i+=l){
                int mul=1;
                for(int j=i;j<i+k;j++){
                    int val=a[j+k]*mul%mod;
                    inc(a[j+k]=a[j],mod-val);
                    inc(a[j],val);
                    mul=mul*bas%mod;
                }
            }
        }
        if(fl==-1){
            int inv=ksm(n);
            for(int i=0;i<n;i++)a[i]=a[i]*inv%mod;
        }
    }
    vector<int> mul(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1,k=1;
        while(k<n+m+1)k<<=1;
        a.resize(k);b.resize(k);
        for(int i=0;i<k;i++)to[i]=to[i>>1]>>1|((i&1)?(k>>1):0);
        ntt(a,1);ntt(b,1);
        for(int &v:a)v=(v%mod+mod)%mod;
        for(int &v:b)v=(v%mod+mod)%mod;
        for(int i=0;i<k;i++)a[i]=a[i]*b[i]%mod;
        ntt(a,-1);a.resize(n+m+1);
        return a;
    }
}
int n,m,k,t[1<<maxm],a[1<<maxm];
void fwtxor(int *a,int n,int fl=1){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++){
				int u=a[j],v=a[j+k];
				a[j]=(u+v)*fl%mod,a[j+k]=(u+mod-v)*fl%mod;
			}
		}
	}
}
void work(){
	n=read();m=read();k=read();init(n);
	vector<int> f(n+1),g(n+1);
	for(int i=0;i<=n;i++)f[i]=inv[i];
	for(int i=0;i<=n;i++)g[i]=ksm(2,2*n-k-i)*inv[i]%mod*C(n-i,k-n+i)%mod;
	f=poly::mul(f,g);
	for(int i=0;i<=n;i++)f[i]=(((n-i)&1)?mod-1:1)*fac[i]%mod*f[i]%mod;
	// for(int j=0;j<=n;j++){
		// for(int i=0;i<=j;i++)(f[j]+=C(j,i)*ksm(2,2*n-k-j+i)%mod*C(n-j+i,k-n+j-i))%=mod;
		// f[j]=f[j]*(((n-j)&1)?mod-1:1)%mod;
	// }
	for(int i=1;i<=n;i++)t[read()]++;
	fwtxor(t,1<<m);
	for(int s=0;s<(1<<m);s++){
		// int cnt=0;for(int ss=0;ss<(1<<m);ss++)if(!(__builtin_popcount(s&ss)&1))cnt+=t[ss];
		if(t[s]>n)t[s]-=mod;
		a[s]=f[(n+t[s])/2];
	}
	fwtxor(a,1<<m,(mod+1)/2);
	for(int s=0;s<(1<<m);s++)printf("%lld%c",a[s]," \n"[s==(1<<m)-1]);
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