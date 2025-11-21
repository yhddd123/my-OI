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
int fac[maxn<<1],inv[maxn<<1];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
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
vector<int> mul1(vector<int> a,vector<int> b){
	int n=a.size()-1,m=b.size()-1;
	reverse(a.begin(),a.end());
	vector<int> ans=poly::mul(a,b);
	ans.erase(ans.begin(),ans.begin()+n);
	return ans;
}
int a[maxn];
vector<int> sovle(int l,int r,int p,vector<int> &dw){
	if(l==r){
		vector<int> ans(a[l]-p+1,dw[0]);
		return ans;
	}
	int mid=l+r>>1;
	vector<int> dwl=dw;dwl.resize(mid-l+1);
	vector<int> mf=sovle(l,mid,p,dwl);
	vector<int> ans(a[r]-p+1),dwr(r-mid);
	// vector<int> ff(mf.size()),gg(r+mid+1+mf.size());
	// for(int i=0;i<mf.size();i++)ff[i]=mf[i]*inv[a[mid]-p-i]%mod;
	// for(int i=0;i<gg.size();i++)gg[i]=fac[i];
	// ff=mul1(ff,gg);
	// for(int i=0;i<=r-mid;i++)dwr[i]=ff[i+1]*inv[i+1]%mod;
	for(int i=0;i<=a[mid]-p;i++){
		for(int j=0;j<=r-mid;j++)(dwr[j]+=mf[i]*C(j+1+a[mid]-p-i,j+1))%=mod;
	}
	for(int i=0;i<=r-mid;i++){
		for(int j=0;j<=i;j++)(dwr[j]+=dw[i+mid-l+1]*C(i-j+a[mid]-p,a[mid]-p))%=mod;
	}
	for(int i=0;i<=a[mid]-p;i++){
		for(int j=i;j<=a[mid]-p;j++)(ans[j]+=mf[i]*C(r-mid+j-i,r-mid))%=mod;
	}
	for(int i=0;i<=r-mid;i++){
		for(int j=0;j<=a[mid]-p;j++)(ans[j]+=dw[i+mid-l+1]*C(r-mid-i+j,j))%=mod;
	}
	vector<int> rf=sovle(mid+1,r,a[mid],dwr);
	for(int i=a[mid];i<=a[r];i++)ans[i-p]=rf[i-a[mid]];
	cout<<l<<" "<<r<<" "<<p<<" s\n";
	for(int i=p;i<=a[r];i++)cout<<ans[i-p]<<" ";cout<<"\n";
	return ans;
}
int n,m,k;
int f[1010][1010];
int calc(vector<int> &lim){
	// for(int v:lim)cout<<v<<" ";cout<<"\n";
	for(int i=0;i<=n;i++)a[i]=lim[i];
	for(int i=n-1;~i;i--)a[i]=min(a[i],a[i+1]);
	mems(f,0);f[0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=a[i];j++){
			if(i)(f[i][j]+=f[i-1][j])%=mod;
			if(j)(f[i][j]+=f[i][j-1])%=mod;
		}
	}
	// for(int i=0;i<=n;i++){
		// for(int j=0;j<=a[i];j++){
			// cout<<f[i][j]<<" ";
		// }
		// cout<<"\n";
	// }
	// cout<<f[n][m]<<" "<<C(n+m,n)<<"\n";
	return f[n][m];
}
void work(){
	m=read();n=read();k=read();init(n+m);
	vector<int> la(n+1,m),lb(n+1,m);
	for(int i=1;i<=k;i++){
		int l2=read(),l1=read(),r2=read(),r1=read();
		la[r1-1]=min(la[r1-1],l2);
		lb[l1+1]=min(lb[l1+1],m-r2);
	}
	reverse(lb.begin(),lb.end());
	printf("%lld\n",(calc(la)+calc(lb))*ksm(C(n+m,n))%mod);
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