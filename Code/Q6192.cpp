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
const int maxn=400010;
const int inf=1e9;
bool mbe;

unsigned seed;
unsigned get(unsigned &x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x % 1000;
}
int n,q,w[maxn];
pii a[maxn];
int id[maxn];
int tol[maxn],tor[maxn],sum[maxn];
int pl[maxn],pr[maxn];
int g[maxn],f[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	for(int i=1;i<=n;i++)sum[a[i].se]++;
	for(int i=1;i<=2*n;i++)sum[i]+=sum[i-1];
	for(int i=1,lst=0;i<=2*n;i++){
		if(2*sum[i]==i){
			for(int j=lst+1;j<=i;j++)tol[j]=lst+1,tor[j]=i;
			lst=i;
		}
	}
	for(int i=1;i<=n;i++)id[a[i].fi]=id[a[i].se]=i;
	set<pii> s;
	for(int i=2*n;i;i--){
		if(a[id[i]].se==i){
			s.insert({i,id[i]});
			pr[id[i]]=(*--s.end()).se;
		}
		else s.erase({a[id[i]].se,id[i]});
	}
	for(int i=1;i<=2*n;i++){
		if(a[id[i]].fi==i){
			s.insert({i,id[i]});
			pl[id[i]]=(*s.begin()).se;
		}
		else s.erase({a[id[i]].fi,id[i]});
	}
	for(int i=1;i<=n;i++)f[i]=0;
	for(int i=1;i<=2*n;i++)sum[i]=0;
	for(int i=1;i<=n;i++)g[i]=1;
	auto upd=[&](int l,int r,int w){
		// cout<<l<<" "<<r<<" "<<w<<"\n";
		sum[l]+=w,sum[r+1]-=w;};
	for(int i=1;i<=2*n;i++)if(a[id[i]].se==i){
		if(pr[id[i]]==id[i])continue;
		// cout<<id[i]<<" "<<pr[id[i]]<<"\n";
		upd(a[id[i]].se+1,a[pr[id[i]]].se,2*g[id[i]]);
		upd(a[pr[id[i]]].se+1,tor[i],g[id[i]]);
		g[pr[id[i]]]+=g[id[i]];
	}
	for(int i=1;i<=2*n;i++)sum[i]+=sum[i-1];
	for(int i=1;i<=n;i++)f[i]+=sum[a[i].fi];
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i=1;i<=2*n;i++)sum[i]=0;
	for(int i=1;i<=n;i++)g[i]=1;
	for(int i=2*n;i;i--)if(a[id[i]].fi==i){
		if(pl[id[i]]==id[i])continue;
		// cout<<id[i]<<" "<<pl[id[i]]<<"\n";
		upd(a[pl[id[i]]].fi,a[id[i]].fi-1,2*g[id[i]]);
		upd(tol[i],a[pl[id[i]]].fi-1,g[id[i]]);
		g[pl[id[i]]]+=g[id[i]];
	}
	for(int i=1;i<=2*n;i++)sum[i]+=sum[i-1];
	for(int i=1;i<=n;i++)f[i]+=sum[a[i].se];
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	int all=0;for(int i=1;i<=n;i++)all+=1;
	for(int i=1;i<=n;i++)f[i]+=all-1;
	for(int i=1;i<=2*n;i++)sum[i]=0;
	for(int i=1;i<=n;i++)sum[a[i].se]+=1;
	for(int i=1;i<=2*n;i++)sum[i]+=sum[i-1];
	for(int i=1;i<=n;i++)f[i]-=sum[a[i].fi];
	for(int i=1;i<=2*n;i++)sum[i]=0;
	for(int i=1;i<=n;i++)sum[a[i].fi]+=1;
	for(int i=2*n-1;i;i--)sum[i]+=sum[i+1];
	for(int i=1;i<=n;i++)f[i]-=sum[a[i].se];
	for(int i=1;i<=n;i++)printf("%lld\n",f[i]);
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