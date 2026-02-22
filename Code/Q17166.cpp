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
const int maxn=200010;
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
int n,m,a[maxn];
vector<int> f;
int ff[110][110];
vector<int> sovle(int l,int r,int p,vector<int> &dw){
	if(r-l+1<=100){
		for(int i=0;i<=r-l;i++)ff[i][0]=dw[i];
		for(int i=0;i<=r-l;i++){
			for(int j=1;j<=a[i+l]-p;j++){
				ff[i][j]=ff[i][j-1];
				(i&&j<=a[i+l-1]-p)&&(inc(ff[i][j],ff[i-1][j]),0);
			}
		}
		vector<int> ans(a[r]-p+1);
		for(int i=0;i<=a[r]-p;i++)ans[i]=ff[r-l][i];
		for(int i=l;i<=r;i++)f[i]=ff[i-l][a[i]-p];
		return ans;
	}
	if(l==r){
		for(int i=l;i<=r;i++)f[i]=dw[0];
		vector<int> ans(a[l]-p+1,dw[0]);
		return ans;
	}
	int mid=l+r>>1;
	vector<int> dwl=dw;dwl.resize(mid-l+1);
	vector<int> mf=sovle(l,mid,p,dwl);
	vector<int> ans(a[r]-p+1),dwr(r-mid);
	{
		vector<int> ff(mf.size()),gg(r-mid+1+ff.size());
		for(int i=1;i<ff.size();i++)ff[i]=mf[i]*1ll*inv[a[mid]-p-i]%mod;
		for(int i=0;i<gg.size();i++)gg[i]=fac[i];
		ff=poly::mul(ff,gg);
		for(int i=0;i<r-mid;i++)inc(dwr[i],ff[i+a[mid]-p]*1ll*inv[i]%mod);
		// for(int i=1;i<=a[mid]-p;i++){
			// for(int j=0;j<r-mid;j++)(dwr[j]+=mf[i]*1ll*C(j+a[mid]-p-i,j))%=mod;
		// }
	}
	{
		vector<int> ff(r-mid),gg(r-mid);
		for(int i=0;i<r-mid;i++)ff[i]=dw[i+mid-l+1];
		for(int i=0;i<r-mid;i++)gg[i]=C(i+a[mid]-p-1,a[mid]-p-1);
		ff=poly::mul(ff,gg);
		for(int i=0;i<r-mid;i++)inc(dwr[i],ff[i]);
		// for(int i=0;i<r-mid;i++){
			// for(int j=i;j<r-mid;j++)(dwr[j]+=dw[i+mid-l+1]*1ll*C(j-i+a[mid]-p-1,a[mid]-p-1))%=mod;
		// }
	}
	{
		vector<int> ff(a[mid]-p+1),gg(a[mid]-p+1);
		for(int i=1;i<=a[mid]-p;i++)ff[i]=mf[i];
		for(int i=0;i<=a[mid]-p;i++)gg[i]=C(r-mid-1+i,r-mid-1);
		ff=poly::mul(ff,gg);
		for(int i=1;i<=a[mid]-p;i++)inc(ans[i],ff[i]);
		// for(int i=1;i<=a[mid]-p;i++){
			// for(int j=i;j<=a[mid]-p;j++)(ans[j]+=mf[i]*1ll*C(r-mid-1+j-i,r-mid-1))%=mod;
		// }
	}
	{
		vector<int> ff(r-mid),gg(r-mid-1+a[mid]-p);
		for(int i=0;i<r-mid;i++)ff[i]=dw[i+mid-l+1]*1ll*inv[r-mid-1-i]%mod;
		for(int i=0;i<gg.size();i++)gg[i]=fac[i];
		ff=poly::mul(ff,gg);
		for(int i=1;i<=a[mid]-p;i++)inc(ans[i],ff[r-mid-1+i-1]*1ll*inv[i-1]%mod);
		// for(int i=0;i<r-mid;i++){
			// for(int j=1;j<=a[mid]-p;j++)(ans[j]+=dw[i+mid-l+1]*1ll*C(r-mid-1-i+j-1,j-1))%=mod;
		// }
	}
	ans[0]=dw[r-mid];
	if(a[mid]==p){
		for(int i=0;i<r-mid;i++)dwr[i]=dw[i+mid-l+1];
	}
	vector<int> rf=sovle(mid+1,r,a[mid],dwr);
	for(int i=a[mid]+1;i<=a[r];i++)ans[i-p]=rf[i-a[mid]];
	return ans;
}
void work(){
	n=read();m=read();init(2*maxn-10);
	vector<int> dw(n+1);f.resize(n+1);
	for(int i=1;i<=m;i++)dw[read()]=1;
	bool fl=0;if(dw[0])dw[0]=0,fl=1;
	for(int i=1;i<=n;i++)dw[i]+=dw[i-1];
	for(int i=1;i<=n;i++)a[i]=i;
	vector<int> h=sovle(0,n,1,dw);
	vector<int> ff=f,gg(n+1);
	for(int i=1;i<=n;i++)gg[i]=C(2*i-1,i-1);
	ff=poly::mul(ff,gg);
	for(int i=1;i<=n;i++)inc(f[i],ff[i]);
	if(fl)for(int i=1;i<=n;i++)inc(f[i],C(2*i-1,i));
	for(int i=1;i<=n;i++)printf("%lld\n",f[i]);
	
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}