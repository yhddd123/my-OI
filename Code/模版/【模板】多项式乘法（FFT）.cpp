// namespace fft{
// 	struct cp{
// 		db a,b;
// 		cp(db u=0,db v=0){a=u,b=v;}
// 		cp operator+(const cp&tmp)const{return {a+tmp.a,b+tmp.b};}
// 		cp operator-(const cp&tmp)const{return {a-tmp.a,b-tmp.b};}
// 		cp operator*(const cp&tmp)const{return {a*tmp.a-b*tmp.b,a*tmp.b+b*tmp.a};}
// 	};
// 	const db pi=acos(-1);
// 	int to[maxn<<3];
// 	void fft(vector<cp> &a,int flag){
// 		int n=a.size();
// 		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
// 		for(int l=2;l<=n;l<<=1){
// 			cp bas=cp(cos(2*pi/l),flag*sin(2*pi/l));
// 			int k=l>>1;
// 			for(int i=0;i<n;i+=l){
// 				cp mul=cp(1,0);
// 				for(int j=i;j<i+k;j++){
// 					cp val=mul*a[j+k];
// 					a[j+k]=a[j]-val,a[j]=a[j]+val;
// 					mul=mul*bas;
// 				}
// 			}
// 		}
// 		if(flag==-1){
// 			for(int i=0;i<n;i++)a[i].a/=n,a[i].b/=n;
// 		}
// 	}
// 	const int B=(1<<15)-1;
// 	int calc(db x){return (int)(x+0.5);}
// 	vector<int> mul(vector<int> a,vector<int> b){
// 		int n=a.size()-1,m=b.size()-1,k=1;
// 		while(k<n+m+1)k<<=1;
// 		for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
// 		vector<cp> f(k),g(k);
// 		for(int i=0;i<=n;i++)f[i]=cp(a[i],0),g[i]=cp(b[i],0);
// 		fft(f,1),fft(g,1);
// 		for(int i=0;i<k;i++)f[i]=f[i]*g[i];
// 		fft(f,-1);
// 		// for(int i=0;i<k;i++)cout<<calc(f[i].a)<<" "<<calc(f[i].b)<<"\n";
// 		vector<int> ans(n+m+1);
// 		for(int i=0;i<=n+m;i++)ans[i]=calc(f[i].a);
// 		return ans;
// 	}
// }

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=4000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
vector<int> a,b;
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
	inline int ksm(int a,int b=mod-2){
		int ans=1;
		while(b){
			if(b&1)ans=ans*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ans;
	}
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
using poly::mul;
void work(){
	n=read();m=read();
	a.resize(n+1),b.resize(m+1);
	for(int i=0;i<=n;i++)a[i]=read();
	for(int i=0;i<=m;i++)b[i]=read();
	vector<int> c=mul(a,b);
	for(int i=0;i<=n+m;i++)printf("%lld ",c[i]);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}