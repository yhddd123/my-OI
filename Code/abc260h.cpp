// Problem: AT_abc260_h [ABC260Ex] Colorfulness
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc260_h
// Memory Limit: 1024 MB
// Time Limit: 8000 ms
// Written by yhm.
// Start codeing:2026-01-25 18:00:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353
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
const int maxn=250010;
const int inf=1e9;
bool mbe;

int n,m,t[maxn];
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
        ff=mul(ff,gg);
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
using poly::mul;
vector<int> cdq1(int l,int r){
	if(l==r){
		if(!t[l])return {1};
		vector<int> f(t[l]);
		for(int i=0;i<t[l];i++)f[i]=1ll*fac[t[l]]*inv[t[l]-i]%mod*C(t[l]-1,i)%mod;
		return f;
	}
	int mid=l+r>>1;
	vector<int> vl=cdq1(l,mid),vr=cdq1(mid+1,r);
	return mul(vl,vr);
}
int ans[maxn];
pair<vector<int>,vector<int>> cdq2(int l,int r){
	if(l==r){
		return {{ans[l]},{1,mod-l}};
	}
	int mid=l+r>>1;
	auto [a,b]=cdq2(l,mid);
	auto [c,d]=cdq2(mid+1,r);
	return {poly::add(mul(a,d),mul(b,c)),mul(b,d)};
}
void work(){
	n=read();m=read();init(n);
	for(int i=1;i<=n;i++)t[read()]++;
	vector<int> f=cdq1(1,n);f.resize(n);
	for(int i=0;i<f.size();i++)f[i]=1ll*f[i]*fac[n-i]%mod;
	vector<int> ff(n),gg(n);
	// for(int i=0;i<n;i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i=0;i<n;i++)ff[i]=1ll*f[i]*fac[i]%mod;
	for(int i=0;i<n;i++)gg[i]=1ll*((i&1)?mod-1:1)*inv[i]%mod;
	reverse(gg.begin(),gg.end());
	ff=poly::mul(ff,gg);
	for(int i=0;i<n;i++)ans[n-i-1]=1ll*ff[i+n-1]*inv[i]%mod;
	// for(int i=0;i<n;i++)cout<<ans[i]<<" ";cout<<"\n";
	auto[f1,f2]=cdq2(0,n-1);
	f2.resize(m+1);
	f1=poly::mul(f1,poly::ni(f2));
	for(int i=1;i<=m;i++)printf("%d ",f1[i]);puts("");
	// for(int i=1;i<=m;i++){
		// int res=0;
		// for(int j=0;j<n;j++)inc(res,1ll*ksm(j,i)*ans[j]%mod);
		// printf("%d ",res);
	// }
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