#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=5010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,p,x;
char s[maxn];
int c[maxn][maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace ploy{
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
	int to[maxn<<2];
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
		f=ntt(f,-1);
		vector<int> ans(p-1);
		for(int i=0;i<k;i++)inc(ans[i%(p-1)],f[i]);
		return ans;
	}
}
using ploy::mul;
vector<int> bas,ans;
int a[maxn];
bool check(int x){
	for(int i=0,val=1;i<p-1;i++,val=val*x%p){
		if(i&&val==1)return 0;
	}
	return 1;
}
void work(){
	scanf("%s",s+1);n=strlen(s+1);reverse(s+1,s+n+1);
	p=read();x=read();
	for(int i=0;i<p;i++){
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)c[i][j]=(c[i-1][j-1]+c[i-1][j])%p;
	}
	int gen=1;while(!check(gen))gen++;
	// cout<<gen<<"\n";
	for(int i=0,g=1;i<p-1;i++,g=g*gen%p)a[g]=i;
	// for(int i=1;i<p;i++)cout<<a[i]<<" ";cout<<"\n";
	bas.resize(p-1),ans.resize(p-1);
	for(int i=0;i<p;i++){
		for(int j=0;j<=i;j++)bas[a[c[i][j]]]++;
	}
	ans[0]=1;
	for(int i=1;i<=n;i++){
		if(s[i]=='1')ans=mul(ans,bas);
		bas=mul(bas,bas);
	}
	printf("%lld\n",ans[a[x]]);
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
