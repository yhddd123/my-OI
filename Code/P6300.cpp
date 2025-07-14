#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=400010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],b=10;
namespace ploy{
	int to[maxn];
	int ksm(int a,int b=mod-2,int p=mod){
		int ans=1;
		while(b){
			if(b&1)ans=ans*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ans;
	}
	int g=3,invg=ksm(3);
	void ntt(int *a,int n,int flag){
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int k=2;k<=n;k<<=1){
			int bas=ksm(flag==1?g:invg,(mod-1)/k),l=k>>1;
			for(int i=0;i<n;i+=k){
				int mul=1;
				for(int j=i;j<i+l;j++){
					int val=a[j+l]*mul%mod;
					a[j+l]=a[j]-val;
					if(a[j+l]<0)a[j+l]+=mod;
					a[j]=a[j]+val;
					if(a[j]>=mod)a[j]-=mod;
					mul=mul*bas%mod;
				}
			}
		}
		int invn=ksm(n);
		if(flag==-1)for(int i=0;i<n;i++)a[i]=a[i]*invn%mod;
	}
	int a[maxn];
	void sqr(int *f,int *ans,int n){
		for(int i=0;i<=n;i++)a[i]=f[i];
		int m=2*n;n=1;while(n<=m)n<<=1;
		for(int i=0;i<n;i++)to[i]=(to[i>>1]>>1)|(i&1?n>>1:0);
		ntt(a,n,1);
		for(int i=0;i<n;i++)a[i]=a[i]*a[i]%mod;
		ntt(a,n,-1);
		for(int i=0;i<n;i++)ans[i]=a[i];
		for(int i=0;i<n;i++)a[i]=0;
	}
}
vector<int> id;
int ans[maxn],f[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[read()]++;
	for(int i=1;i<=m;i++)if(a[i]>b)id.push_back(i);
	for(int i:id){
		for(int j:id)ans[i+j]+=min(a[i],a[j])-b;
	}
	for(int j=1;j<=b;j++){
		for(int i=1;i<=m;i++)f[i]=(a[i]>=j);
		ploy::sqr(f,f,m);
		for(int i=1;i<=2*m;i++)ans[i]+=f[i];
	}
	for(int i=1;i<=2*m;i++)ans[i]/=2;
	int pos=1;
	for(int i=2;i<=2*m;i++){
		if(ans[i]>ans[pos])pos=i;
	}
	printf("%lld %lld\n",ans[pos],pos);
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
