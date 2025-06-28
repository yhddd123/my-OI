// Problem: AT_joisc2019_c
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_joisc2019_c
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-04-15 18:17:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define ll __int128
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,m;
bool vis[maxn];
int p[maxn];
struct fac{
	int a,b;
	fac(ll p=0,ll q=1){
		ll g=__gcd(p,q);
		p/=g,q/=g;
		a=p,b=q;
	}
	bool operator<(const fac&tmp)const{return (ll)a*tmp.b<(ll)tmp.a*b;}
	bool operator==(const fac&tmp)const{return (ll)a*tmp.b==(ll)tmp.a*b;}
	fac operator+(const fac&tmp)const{return fac((ll)a*tmp.b+(ll)b*tmp.a,(ll)b*tmp.b);}
	fac operator-(const fac&tmp)const{return fac((ll)a*tmp.b-(ll)b*tmp.a,(ll)b*tmp.b);}
	fac operator*(const fac&tmp)const{return fac((ll)a*tmp.a,(ll)b*tmp.b);}
	fac operator/(const fac&tmp)const{return fac((ll)a*tmp.b,(ll)b*tmp.a);}
}a[maxn],tmp[maxn],b[maxn][maxn],ans[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		fac sum=fac(0,1),lst=fac(0,1),pos=fac(0,1);
		for(int j=1;j<=m;j++)a[j]=tmp[j]=fac(read(),1),sum=sum+a[j];sum.b=n;
		for(int j=1,p=0;j<=m;j++){
			while(sum<lst+a[j]){
				pos=b[i][++p]=pos+(sum-lst)/tmp[j];
				a[j]=a[j]-(sum-lst);lst=fac(0,1);
			}
			if(a[j].a)lst=lst+a[j],pos={j,1};
		}
		// for(int j=1;j<=n;j++)cout<<b[i][j].a<<"/"<<b[i][j].b<<" ";cout<<"\n";
	}
	for(int i=1;i<=n;i++){
		fac mn={inf,1};
		for(int j=1;j<=n;j++)if(!vis[j])mn=min(mn,b[j][i]);
		ans[i]=mn;
		for(int j=1;j<=n;j++)if(!vis[j]&&b[j][i]==mn){vis[j]=1;p[i]=j;break;}
	}
	for(int i=1;i<n;i++){
		auto[p,q]=ans[i];
		int g=__gcd(p,q);
		p/=g,q/=g;
		printf("%lld %lld\n",p,q);
	}
	for(int i=1;i<=n;i++)printf("%lld ",p[i]);
	
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