// Problem: P5488 差分与前缀和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5488
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-03-11 17:04:18
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1004535809ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
inline int readmod(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x*10+ch-'0')%mod;ch=getchar();}
	return x;
}
const int maxn=100010;
const int inf=2e9;
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
namespace poly{
	int g=3,invg=ksm(3);
	int to[maxn<<2];
	void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
	void ntt(vector<int> &a,int fl){
		int n=a.size();
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int l=2;l<=n;l<<=1){
			int bas=ksm(fl==1?g:invg,(mod-1)/l),k=l>>1;
			for(int i=0;i<n;i+=l){
				int mul=1;
				for(int j=i;j<i+k;j++){
					int val=mul*a[j+k]%mod;
					inc(a[j+k]=a[j],mod-val),inc(a[j],val);
					mul=mul*bas%mod;
				}
			}
		}
		if(fl==-1){
			int invn=ksm(n);
			for(int i=0;i<n;i++)a[i]=a[i]*invn%mod;
		}
	}
	vector<int> mul(vector<int> a,vector<int> b){
		int n=a.size()-1,m=b.size()-1,k=1;
		while(k<n+m+1)k<<=1;
		for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
		vector<int> f(k),g(k);
		for(int i=0;i<=n;i++)f[i]=a[i];
		for(int i=0;i<=m;i++)g[i]=b[i];
		ntt(f,1),ntt(g,1);
		for(int i=0;i<k;i++)f[i]=f[i]*g[i]%mod;
		ntt(f,-1);f.resize(n+m+1);
		return f;
	}
}
using poly::mul;
int n,k,op;
vector<int> f,g;
int ni[maxn];
void work(){
	n=read();k=readmod();op=read();
	f.resize(n),g.resize(n);
	for(int i=0;i<n;i++)f[i]=read();
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	if(!op){
		g[0]=1;
		for(int i=1,mul=1;i<n;i++)mul=mul*(k+i-1)%mod*ni[i]%mod,g[i]=mul;
	}
	else{
		g[0]=1;
		for(int i=1,mul=1;i<n;i++)mul=mul*(k-i+1)%mod*ni[i]%mod,g[i]=(i&1)?mod-mul:mul;
	}
	// for(int i=0;i<n;i++)cout<<g[i]<<" ";cout<<endl;
	f=mul(f,g);
	for(int i=0;i<n;i++)printf("%lld ",f[i]);
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