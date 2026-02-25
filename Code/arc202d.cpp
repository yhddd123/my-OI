// Problem: AT_arc202_d [ARC202D] King
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc202_d
// Memory Limit: 1024 MB
// Time Limit: 15000 ms
// Written by yhm.
// Start codeing:2026-02-25 16:54:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=300010;
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
int fac[maxn<<1],inv[maxn<<1];
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
}
int n,m,t,a,b,c,d,ans;
const int B=800;
int f[maxn],g[maxn];
vector<int> calc(int n,int t,int a,int b){
	vector<int> ans(t+1);
	if(n<=B){
		for(int i=1;i<=n;i++)f[i]=0;f[a]=1;ans[0]=(a==b);
		for(int i=1;i<=t;i++){
			for(int i=2;i<=n;i++)inc(g[i-1],f[i]);
			for(int i=1;i<n;i++)inc(g[i+1],f[i]);
			for(int i=1;i<=n;i++)inc(f[i],g[i]),g[i]=0;
			ans[i]=f[b];
		}
		return ans;
	}
	int l=0,r=n+1;
	for(int i=abs(a-b);i<=t;i+=2){
		int p=a,o=1;
		while(abs(p-b)<=i){
			if(o==1)inc(ans[i],C(i,(i+abs(p-b))/2));
			else inc(ans[i],mod-C(i,(i+abs(p-b))/2));
			if(o==1)p=2*l-p;
			else p=2*r-p;
			o^=1;
		}
		p=a,o=1;
		while(abs(p-b)<=i){
			if(o==1)inc(ans[i],C(i,(i+abs(p-b))/2));
			else inc(ans[i],mod-C(i,(i+abs(p-b))/2));
			if(o==1)p=2*r-p;
			else p=2*l-p;
			o^=1;
		}
		inc(ans[i],mod-C(i,(i+abs(a-b))/2));
	}
	vector<int> ff(t+1);
	for(int i=0;i<=t;i++)ff[i]=inv[i];
	for(int i=0;i<=t;i++)ans[i]=1ll*ans[i]*inv[i]%mod;
	ans=poly::mul(ans,ff);
	for(int i=0;i<=t;i++)ans[i]=1ll*ans[i]*fac[i]%mod;
	ans.resize(t+1);
	return ans;
}
void work(){
	n=read();m=read();t=read();a=read();b=read();c=read();d=read();init(2*maxn-10);
	vector<int> f=calc(n,t,a,c);
	vector<int> g=calc(m,t,b,d);
	// for(int v:f)cout<<v<<" ";cout<<"\n";
	// for(int v:g)cout<<v<<" ";cout<<"\n";
	for(int i=0;i<=t;i++)inc(ans,1ll*(((t-i)&1)?mod-1:1)*C(t,i)%mod*f[i]%mod*g[i]%mod);
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}