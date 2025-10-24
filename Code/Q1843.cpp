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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

namespace fft{
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
	int calc(db x){return (int)(x+0.5);}
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
int n,m,q,d[maxn];
map<pii,int> mp;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(u==v){d[u]++;continue;}
		if(u>v)swap(u,v);
		mp[{u,v}]++,d[u]++,d[v]++;
	}
	vector<int> f(m+1);
	for(int i=1;i<=n;i++)f[d[i]]++;
	f=fft::mul(f,f);
	for(int i=1;i<=n;i++)f[2*d[i]]--;
	for(int i=0;i<=2*m;i++)f[i]/=2;
	for(auto[p,w]:mp){
		auto[u,v]=p;
		f[d[u]+d[v]]--;
		f[d[u]+d[v]-w]++;
	}
	// for(int i=0;i<=2*m;i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i=2*m-1;~i;i--)f[i]+=f[i+1];
	q=read();
	while(q--){
		int k=read();
		if(k+1>2*m)puts("0");
		else printf("%lld\n",f[k+1]);
	}
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