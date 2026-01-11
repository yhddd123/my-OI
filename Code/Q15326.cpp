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
const int maxn=250010;
const int inf=1e9;
bool mbe;

int n,ans;
char s[maxn];
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
    if(n<0|m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int cat(int n){return C(2*n,n)*ksm(n+1)%mod;}
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
        a.resize(max(n,m)+1);
        for(int i=0;i<=m;i++)inc(a[i],b[i]);
        return a;
    }
}
struct node{
	vector<int> f[2][2];
};
node sovle(int l,int r){
	if(l==r){
		node res;
		res.f[0][0].pb(1);
		res.f[0][1].pb(0);
		res.f[1][0].pb(0);
		res.f[1][1].pb(0),res.f[1][1].pb(s[l]==s[l-1]?mod-1:1);
		return res;
	}
	int mid=l+r>>1;
	node resl=sovle(l,mid),resr=sovle(mid+1,r);
	node res;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			res.f[i][j]=poly::add(res.f[i][j],poly::mul(resl.f[i][0],resr.f[0][j]));
			res.f[i][j]=poly::add(res.f[i][j],poly::mul(resl.f[i][1],resr.f[0][j]));
			res.f[i][j]=poly::add(res.f[i][j],poly::mul(resl.f[i][0],resr.f[1][j]));
		}
	}
	return res;
}
int val[maxn];
void work(){
	n=read();scanf("%s",s+1);init(2*n);
	if(n==1){puts(s[1]=='0'?"1":"0");return ;}
	node res=sovle(2,n);
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<res.f[i][j].size();k++)inc(val[k],res.f[i][j][k]);
		}
	}
	for(int i=0;i<=n/2;i++)(ans+=cat(n-i-1)*val[i])%=mod;
	// for(int i=0;i<=n/2;i++)cout<<val[i]<<" ";cout<<"\n";
	printf("%lld\n",ans*(mod+1)/2%mod);
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