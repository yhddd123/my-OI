// Problem: #3394. 「2020-2021 集训队作业」Tour
// Contest: LibreOJ
// URL: https://loj.ac/p/3394
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-12 15:12:51
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=800010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans;
int st1[maxn],tp1,st2[maxn],tp2,f1[maxn],f2[maxn];
int st[maxn];
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
namespace ploy{
	const int g=3,invg=ksm(3);
	int to[maxn];
	void ntt(int *a,int n,int flag){
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int k=2;k<=n;k<<=1){
			int bas=ksm(flag==1?g:invg,(mod-1)/k),l=k>>1;
			for(int i=0;i<n;i+=k){
				int mul=1;
				for(int j=i;j<i+l;j++){
					int val=mul*a[j+l]%mod;
					a[j+l]=a[j]-val;
					if(a[j+l]<0)a[j+l]+=mod;
					a[j]=a[j]+val;
					if(a[j]>=mod)a[j]-=mod;
					mul=mul*bas%mod;
				}
			}
		}
		int invn=ksm(n);
		if(flag==-1)for(int i=0;i<n;i++)a[i]*=invn,a[i]%=mod;
	}
	int a[maxn],b[maxn];
	vector<int> mul(vector<int> f,vector<int> g){
		int n=f.size(),m=g.size();
		for(int i=0;i<n;i++)a[i]=f[i];
		for(int i=0;i<m;i++)b[i]=g[i];
		m+=n,n=1;while(n<=m)n<<=1;
		for(int i=0;i<n;i++)to[i]=(to[i>>1]>>1)|(i&1?n>>1:0);
		ntt(a,n,1);ntt(b,n,1);
		for(int i=0;i<n;i++)a[i]=a[i]*b[i]%mod;
		ntt(a,n,-1);
		vector<int> ans(n);
		for(int i=0;i<n;i++)ans[i]=a[i];
		for(int i=0;i<n;i++)a[i]=b[i]=0;
		return ans;
	}
}
vector<int> sovle(int l,int r){
	if(l==r){
		vector<int> f(2);
		f[0]=st[l],f[1]=1;
		return f;
	}
	int mid=l+r>>1;
	vector<int> f=ploy::mul(sovle(l,mid),sovle(mid+1,r));
	cout<<l<<" "<<r<<"\n";
	for(int i:f)cout<<i<<" ";cout<<"\n";
	return f;
}
vector<int> work(vector<int> f){
	int n=f.size();
	vector<int> g(n);
	for(int i=0;i<n;i++)f[i]=f[i]*inv[i]%mod;
	for(int i=0;i<n;i++)g[i]=(i&1)?mod-inv[i]:inv[i];
	f=ploy::mul(f,g);n=f.size();
	for(int i=0;i<n;i++)f[i]=f[i]*fac[i]%mod;
	return f;
}
//F[n] 至多 
void sovle(int *a,int n,int *res){
	if(!n){res[0]=1;return ;}
	sort(a+1,a+n+1);
	for(int i=1,l=1,r=n,num=0;i<=n;i++){
		if(a[l]*a[r]<=m)st[i]=num,num++,l++;
		else st[i]=num,num--,r--;
	}
	vector<int> f=sovle(1,n);
	f=work(f);
	for(int i:f)cout<<i<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)res[i]=f[i];
}
void work(){
	n=read();m=read();
	fac[0]=1;for(int i=1;i<=maxn-10;i++)fac[i]=fac[i-1]*i%mod;
	inv[maxn-10]=ksm(fac[maxn-10]);for(int i=maxn-10-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++){
		int x=read();
		if(x>=0)st1[++tp1]=x;
		else st2[++tp2]=-x;
	}
	sovle(st1,tp1,f1),sovle(st2,tp2,f2);
	for(int i=0;i<=min(tp1,tp2);i++)(ans+=2*f1[i]*f2[i]+f1[i]*f2[i+1]+f1[i+1]*f2[i])%=mod;
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
