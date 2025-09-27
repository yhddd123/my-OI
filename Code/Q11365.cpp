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
int fac[maxn],inv[maxn];
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
        for(int i=0;i<k;i++)a[i]=a[i]*b[i]%mod;
        ntt(a,-1);a.resize(n+m+1);
        return a;
    }
    vector<int> add(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1;
        a.resize(max(n,m)+1);
        for(int i=0;i<=m;i++)inc(a[i],b[i]);
        return a;
    }
}
int n,ans;
char s[maxn];
struct node{
	vector<int> f[3][3];
	int calc(int p){
		int ans=0;
		for(int i=0;i<3;i++){
			for(int j=i;j<3;j++)inc(ans,f[i][j][p]);
		}
		return ans;
	}
};
node finit(int c){
	node f;
	for(int i=0;i<3;i++){
		for(int j=i;j<3;j++)f.f[i][j].resize(2);
	}
	f.f[c][c][1]=1;
	return f;
}
node sovle(int l,int r){
	if(l==r)return finit(s[l]=='B'?0:(s[l]=='Y'?1:2));
	int mid=l+r>>1;
	node g=sovle(l,mid),h=sovle(mid+1,r);
	node f;
	for(int i=0;i<3;i++){
		for(int j=i;j<3;j++){
			f.f[i][j]=poly::add(f.f[i][j],g.f[i][j]);
			f.f[i][j]=poly::add(f.f[i][j],h.f[i][j]);
			for(int k=j;k<3;k++){
				for(int l=k;l<3;l++)f.f[i][l]=poly::add(f.f[i][l],poly::mul(g.f[i][j],h.f[k][l]));
			}
		}
	}
	// cout<<l<<" "<<r<<"\n";
	// for(int i=1;i<=r-l+1;i++)cout<<f.calc(i)<<" ";cout<<"\n";
	return f;
}	
void work(){
	scanf("%s",s+1);n=strlen(s+1);init(n);
	node f=sovle(1,n);
	for(int i=1;i<=n;i++){
		// cout<<i<<" "<<f.calc(i)<<" "<<C(n,i)<<"\n";
		(ans+=(C(n,i)+mod-f.calc(i))*ksm(C(n,i)))%=mod;
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