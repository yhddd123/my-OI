#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=1200010;
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
char s[maxn],t[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int gg=3,invg=ksm(3);
int to[maxn];
void ntt(int *a,int n,int fl){
	for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
	for(int l=2;l<=n;l<<=1){
		int bas=ksm(fl==1?gg:invg,(mod-1)/l),k=l>>1;
		for(int i=0;i<n;i+=l){
			int mul=1;
			for(int j=i;j<i+k;j++){
				int val=a[j+k]*mul%mod;
				a[j+k]=(a[j]+mod-val)%mod;
				(a[j]+=val)%=mod;
				mul=mul*bas%mod;
			}
		}
	}
	if(fl==-1){
		int inv=ksm(n);
		for(int i=0;i<n;i++)a[i]=a[i]*inv%mod;
	}
}
int f[maxn],g[maxn],res[maxn];
vector<int> ans;
void work(){
	scanf("%s%s",t,s);n=strlen(s),m=strlen(t);
	reverse(t,t+m);
	int lim=1;while(lim<n)lim<<=1;
	for(int i=0;i<lim;i++)to[i]=(to[i>>1]>>1)|((i&1)?lim>>1:0);
	for(int i=0;i<m;i++)if(t[i]!='*')f[i]=(t[i]-'a')*(t[i]-'a');
	for(int i=0;i<n;i++)if(s[i]!='*')g[i]=1;
	ntt(f,lim,1),ntt(g,lim,1);
	for(int i=0;i<lim;i++)res[i]=f[i]*g[i]%mod,f[i]=g[i]=0;
	for(int i=0;i<m;i++)if(t[i]!='*')f[i]=t[i]-'a';
	for(int i=0;i<n;i++)if(s[i]!='*')g[i]=s[i]-'a';
	ntt(f,lim,1),ntt(g,lim,1);
	for(int i=0;i<lim;i++)(res[i]+=mod-2*f[i]*g[i]%mod)%=mod,f[i]=g[i]=0;
	for(int i=0;i<m;i++)if(t[i]!='*')f[i]=1;
	for(int i=0;i<n;i++)if(s[i]!='*')g[i]=(s[i]-'a')*(s[i]-'a');
	ntt(f,lim,1),ntt(g,lim,1);
	for(int i=0;i<lim;i++)(res[i]+=f[i]*g[i])%=mod,f[i]=g[i]=0;
	ntt(res,lim,-1);
	// for(int i=0;i<lim;i++)cout<<res[i]<<" ";cout<<"\n";
	for(int i=m-1;i<n;i++)if(!res[i])ans.pb(i-m+2);
	for(int i:ans)printf("%lld ",i);
	
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