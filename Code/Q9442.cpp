#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans;
struct nd{
	int t,a,b,p;
}a[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}
int val[maxn],t[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read(),read(),0},a[i].p=a[i].a*ksm(a[i].b)%mod;
	sort(a+1,a+n+1,[&](nd u,nd v){return (u.t*(u.b-u.a)+(u.t+v.t)*u.a)*v.b<(v.t*(v.b-v.a)+(u.t+v.t)*v.a)*u.b;});
	// sort(a+1,a+n+1,[&](nd u,nd v){return u.a*v.b<v.a*u.b;});
	// sort(a+1,a+n+1,[&](nd u,nd v){return u.t<v.t;});
	// for(int i=1;i<=n;i++)cout<<a[i].t<<" "<<a[i].a<<" "<<a[i].b<<"\n";
	val[0]=1;for(int i=1;i<=n;i++)val[i]=val[i-1]*a[i].p%mod;
	for(int i=1;i<=n;i++)t[i]=(t[i-1]+a[i].t)%mod;
	int num=ksm(val[n]);
	// cout<<num<<"\n";
	for(int i=0;i<n;i++)(ans+=t[i+1]*num%mod*(val[i]*(1+mod-a[i+1].p)%mod))%=mod;
	(ans+=t[n])%=mod;
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