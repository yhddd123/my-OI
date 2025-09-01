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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,ans[maxn];
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
const int maxm=1<<22;
struct hsh_table{
	int head[maxm],tot;
	struct nd{
		int nxt;
		int key;
		int val;
	}e[maxm];
	int hsh(int u){return u&(maxm-1);}
	bool find(int key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return 1;
		}
		return 0;
	}
	int &operator[](int key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,0};head[u]=tot;
		return e[tot].val;
	}
}mp;
int gg=3,B,bas;
int bsgs(int v){
	for(int i=0,mul=v;i<=mod/B;i++){
		if(mp.find(mul))return i*B+mp[mul];
		mul=1ll*mul*bas%mod;
	}
}
bool vis[maxn];
int pre[maxn],cnt;
int h[maxn];
namespace fft{
int _mod=mod-1;
struct cp{
	db a,b;
	cp(db u=0,db v=0){a=u,b=v;}
	cp operator+(const cp&tmp)const{return {a+tmp.a,b+tmp.b};}
	cp operator-(const cp&tmp)const{return {a-tmp.a,b-tmp.b};}
	cp operator*(const cp&tmp)const{return {a*tmp.a-b*tmp.b,a*tmp.b+b*tmp.a};}
};
const db pi=acos(-1);
int to[maxn<<3];
void fft(vector<cp> &a,int flag){
	int n=a.size();
	for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
	for(int l=2;l<=n;l<<=1){
		cp bas=cp(cos(2*pi/l),flag*sin(2*pi/l));
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			cp mul=cp(1,0);
			for(int j=i;j<i+k;j++){
				cp val=mul*a[j+k];
				a[j+k]=a[j]-val,a[j]=a[j]+val;
				mul=mul*bas;
			}
		}
	}
	if(flag==-1){
		for(int i=0;i<n;i++)a[i].a/=n,a[i].b/=n;
	}
}
const int B=(1<<15)-1;
int calc(db x){return (int)(x+0.5)%_mod;}
vector<int> mul(vector<int> a,vector<int> b){
	int n=a.size()-1,m=b.size()-1,k=1;
	while(k<n+m+1)k<<=1;
	for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
	vector<cp> f(k),g(k);
	for(int i=0;i<=n;i++)f[i]=cp(a[i],0),g[i]=cp(b[i],0);
	fft(f,1),fft(g,1);
	for(int i=0;i<k;i++)f[i]=f[i]*g[i];
	fft(f,-1);
	// for(int i=0;i<k;i++)cout<<calc(f[i].a)<<" "<<calc(f[i].b)<<"\n";
	vector<int> ans(n+m+1);
	for(int i=0;i<=n+m;i++)ans[i]=calc(f[i].a);
	return ans;
}
}
int f[maxn],g[maxn];
void work(){
	n=read();scanf("%s",s+1);B=sqrt(1ll*mod*n/log2(n)),bas=ksm(ksm(gg,B));
	for(int i=0,mul=1;i<B;i++){
		mp[mul]=i;
		mul=1ll*mul*gg%mod;
	}
	h[1]=0;for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,h[i]=bsgs(i);
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1,h[i*pre[j]]=(h[pre[j]]+h[i])%(mod-1);
			if(i%pre[j]==0)break;
		}
	}
	int fac=1;for(int i=1;i<=n;i++)fac=fac*i%mod;
	vector<int> a(n+1),b(n+1),c(n+1);
	for(int i=1;i<=n;i++)a[i]=(h[i]+mod-1-h[i+1])%(mod-1);
	for(int i=1;i<=n;i++)b[i]=(s[i]=='R');
	c=mtt::mul(a,b);
	for(int i=1;i<=n;i++)f[i]=ksm(gg,c[i]);
	for(int i=1;i<=n;i++)a[i]=(h[i]+mod-1-h[i+1])%(mod-1);
	reverse(s+1,s+n+1);
	for(int i=1;i<=n;i++)b[i]=(s[i]=='L');
	reverse(s+1,s+n+1);
	c=mtt::mul(a,b);
	for(int i=1;i<=n;i++)g[n-i+1]=ksm(gg,c[i]);
	for(int i=1;i<n;i++)if(s[i]=='L'&&s[i+1]=='R'){
		// int mul1=1,mul2=1;
		// for(int j=1;j<i;j++)if(s[j]=='R')mul1=mul1*(i-j)%mod*ksm(i-j+1)%mod;
		// for(int j=i+2;j<=n;j++)if(s[j]=='L')mul2=mul2*(j-i-1)%mod*ksm(j-i)%mod;
		// cout<<i<<" "<<mul1<<" "<<mul2<<" "<<f[i]<<" "<<g[i+1]<<"\n";
		ans[i]=ans[i+1]=fac*f[i]%mod*g[i+1]%mod;
	}
	if(s[1]=='R')ans[1]=fac*g[1]%mod;
	if(s[n]=='L')ans[n]=fac*f[n]%mod;
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	
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