// Problem: AT_abc289_h [ABC289Ex] Trio
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc289_h
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-30 18:36:18
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
const int maxn=100010;
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
                    int val=1ll*a[j+k]*mul%mod;
                    inc(a[j+k]=a[j],mod-val);
                    inc(a[j],val);
                    mul=1ll*mul*bas%mod;
                }
            }
        }
        if(fl==-1){
            int inv=ksm(n);
            for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
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
        for(int i=0;i<k;i++)a[i]=1ll*a[i]*b[i]%mod;
        ntt(a,-1);a.resize(n+m+1);
        return a;
    }
    vector<int> add(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1;
        a.resize(max(n,m)+1);
        for(int i=0;i<=m;i++)inc(a[i],b[i]);
        return a;
    }
    vector<int> del(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1;
        a.resize(max(n,m)+1);
        for(int i=0;i<=m;i++)inc(a[i],mod-b[i]);
        return a;
    }
    vector<int> f,g;
    void cdqni(int l,int r){
        if(r-l+1<=64){
            for(int i=l;i<=r;i++){
                for(int j=l;j<i;j++)inc(g[i],1ll*g[j]*f[i-j]%mod);
                g[i]=1ll*(mod-g[i])*g[0]%mod;
            }
            return ;
        }
        if(l==r){g[l]=1ll*(mod-g[l])*g[0]%mod;return ;}
        int mid=l+r>>1;
        cdqni(l,mid);
        vector<int> ff(mid-l+1),gg(r-l+1);
        for(int i=l;i<=mid;i++)ff[i-l]=g[i];
        for(int i=0;i<=r-l;i++)gg[i]=f[i];
        ff=poly::mul(ff,gg);
        for(int i=mid+1;i<=r;i++)inc(g[i],ff[i-l]);
        cdqni(mid+1,r);
    }
    vector<int> ni(vector<int> a){
        int n=a.size()-1;
        f.resize(n+1),g.resize(n+1);
        for(int i=0;i<=n;i++)f[i]=a[i],g[i]=0;
        g[0]=ksm(f[0]);for(int i=1;i<=n;i++)inc(g[i],1ll*g[0]*f[i]%mod);
        cdqni(1,n);
        return g;
    }
}
int n,a,b,c;
void sovle(int a,int b,int c){
	if(a>b)swap(a,b);
	if(a>c)swap(a,);
	if(b>c)swap(b,c);
	
	
}
void work(){
	n=read();a=read(),b=read(),c=read();
	vector<int> f=sovle(a,b,c),g=sovle(0,0,0);
	vector<int> h=f*poly::ni(g);
	printf("%lld\n",h[n]);
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