#include<bits/stdc++.h>
#define ull unsigned long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=100100;
const int B=60;
const ull U=(1ull<<B)-1;
const int B1=15;
const ull U1=(1<<B1)-1;
bool mbe;

int n,m,q,va[maxn],vb[maxn],ans;
vector<pii> f[maxn],g[maxn],h[maxn<<1];
vector<int> updg[maxn],updh[maxn];
void redo(vector<pii> &a){
	for(auto&[l,r]:a)if(l>r)swap(l,r);
	sort(a.begin(),a.end());
	vector<pii> b;
	for(auto[l,r]:a){
		if(!b.size()||b.back().se+1<l)b.pb({l,r});
		else b.back().se=max(b.back().se,r);
	}
	a=b;
}
int sum[maxn/B1+5][1<<B1];
ull a[maxn],b[maxn],c[maxn],pw[63];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)va[i]=read();
	for(int i=1;i<=n;i++)vb[i]=read();
	while(q--){
		int x=read(),y=read(),xx=read(),yy=read();
		if(x==xx)f[x].pb({y,yy});
		else if(y==yy)g[y].pb({x,xx});
		else h[y-x+n].pb({x,xx});
	}
	for(int i=1;i<=n;i++){
		redo(f[i]);
		redo(g[i]);
		for(auto[l,r]:g[i])updg[l].pb(i),updg[r+1].pb(i);
	}
	for(int i=-n;i<=n;i++){
		redo(h[i+n]);
		for(auto[l,r]:h[i+n])updh[l].pb(l+i),updh[r+1].pb(r+1+i);
	}
	for(int i=0;i<=n/B1;i++){
		for(int j=0;j<15;j++)sum[i][1<<j]=vb[B1*i+j];
		for(int s=1;s<=U1;s++)inc(sum[i][s]=sum[i][s&-s],sum[i][s&(s-1)]);
	}
	m=n/B;
	pw[0]=1;for(int i=1;i<=B;i++)pw[i]=pw[i-1]<<1ll;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++)a[j]=0;
		for(auto[l,r]:f[i]){
			int pl=l/B,pr=r/B;
			if(pl==pr)a[pl]|=pw[r%B+1]-pw[l%B];
			else{
				a[pl]|=pw[B]-pw[l%B];
				for(int j=pl+1;j<pr;j++)a[j]=pw[B]-1;
				a[pr]|=pw[r%B+1]-1;
			}
		}
		for(int p:updg[i])b[p/B]^=1ull<<(p%B);
		for(int p:updh[i])c[p/B]^=1ull<<(p%B);
		ull res=0;
		for(int j=0;j<=m;j++){
			ull s=a[j]&b[j]&c[j];
			if(s)res+=0ull+sum[j<<2][s&U1]+sum[j<<2|1][(s>>15)&U1]+sum[j<<2|2][(s>>30)&U1]+sum[j<<2|3][(s>>45)&U1];
			// if(s)cout<<i<<" "<<j<<"\n"<<a[j]<<"\n"<<b[j]<<"\n"<<c[j]<<"\n"<<s<<"\n";
			// if(s)cout<<i<<" "<<j<<" "<<s<<" "<<res<<"\n";
		}
		inc(ans,res%mod*va[i]%mod);
		// cout<<i<<" "<<ans<<"\n";
		for(int j=m;~j;j--)c[j]=((c[j]<<1)|(j?(c[j-1]>>B-1):0))&U;
	}
	printf("%lld\n",ans);	
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