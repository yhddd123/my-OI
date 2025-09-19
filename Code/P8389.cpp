#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define piii pair<int,pii>
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
const int inf=3e9;
bool mbe;

int n,k;
vector<pii> a;
void sovle1(){
	int mx=-inf,mn=inf;
	sort(a.begin(),a.end());
	for(auto [u,v]:a)mx=max(mx,v),mn=min(mn,v);
	printf("%d %d %d\n",a[0].fi,mn,max({1ll,mx-mn,a.back().fi-a[0].fi}));
}
int pmn[maxn],pmx[maxn],smn[maxn],smx[maxn];
pair<piii,piii> calc2(vector<pii> a,int lim=-inf){
	int n=a.size();
	sort(a.begin(),a.end());
	pmn[0]=pmx[0]=a[0].se;for(int i=1;i<n;i++)pmn[i]=min(pmn[i-1],a[i].se),pmx[i]=max(pmx[i-1],a[i].se);
	smn[n-1]=smx[n-1]=a[n-1].se;for(int i=n-2;~i;i--)smn[i]=min(smn[i+1],a[i].se),smx[i]=max(smx[i+1],a[i].se);
	int mn=inf;for(int i=0;i<n-1;i++){
		if(a[i+1].fi>a[i].fi&&a[i+1].fi>lim+max({1ll,a[i].fi-a[0].fi,pmx[i]-pmn[i]})){
			mn=min(mn,max({1ll,a[i].fi-a[0].fi,pmx[i]-pmn[i],a[n-1].fi-a[i+1].fi,smx[i+1]-smn[i+1]}));
		}
	}
	for(int i=0;i<n-1;i++)if(mn==max({1ll,a[i].fi-a[0].fi,pmx[i]-pmn[i],a[n-1].fi-a[i+1].fi,smx[i+1]-smn[i+1]})){
		if(a[i+1].fi>a[i].fi&&a[i+1].fi>lim+max({1ll,a[i].fi-a[0].fi,pmx[i]-pmn[i]})){
			return {{max({1ll,a[i].fi-a[0].fi,pmx[i]-pmn[i]}),{max(lim,a[i].fi-max({1ll,a[i].fi-a[0].fi,pmx[i]-pmn[i]})),pmn[i]}},{max({1ll,a[n-1].fi-a[i+1].fi,smx[i+1]-smn[i+1]}),{a[i+1].fi,smn[i+1]}}};
		}
	}
	return {{max(a[n-1].fi-a[0].fi,pmx[n-1]-pmn[n-1]),{a[0].fi,pmn[n-1]}},{1,{inf,inf}}};
}
pair<piii,piii> sovle2(vector<pii> a,int lim=-inf){
	if(!a.size())return {{1,{inf,inf}},{1,{-inf,-inf}}};
	if(a.size()==1)return {{1,{a[0].fi,a[0].se}},{1,{inf,inf}}};
	auto[p1,p2]=calc2(a,lim);
	for(int i=0;i<a.size();i++)swap(a[i].fi,a[i].se);
	auto[p3,p4]=calc2(a);
	swap(p3.se.fi,p3.se.se),swap(p4.se.fi,p4.se.se);
	for(int i=0;i<a.size();i++)swap(a[i].fi,a[i].se);
	// cout<<(max(p1.fi,p2.fi)<max(p3.fi,p4.fi))<<"\n";
	if(max(p1.fi,p2.fi)<max(p3.fi,p4.fi))return {p1,p2};
	return {p3,p4};
}
piii p1,p2,p3;
bool calc3(int x){
	sort(a.begin(),a.end());
	pmn[0]=pmx[0]=a[0].se;for(int i=1;i<n;i++)pmn[i]=min(pmn[i-1],a[i].se),pmx[i]=max(pmx[i-1],a[i].se);
	// for(int i=0;i<n;i++)cout<<pmx[i]<<" ";cout<<"\n";
	// for(int i=0;i<n;i++)cout<<pmn[i]<<" ";cout<<"\n";
	// for(auto[u,v]:a)cout<<u<<" "<<v<<"\n";
	for(int i=1;i<a.size();i++){
		if(max(a[i].fi-a[0].fi,pmx[i]-pmn[i])>x){
			vector<pii> b;
			for(int j=i;j<a.size();j++)b.pb(a[j]);
			p1={max({1ll,a[i-1].fi-a[0].fi,pmx[i-1]-pmn[i-1]}),{a[i-1].fi-max({1ll,a[i-1].fi-a[0].fi,pmx[i-1]-pmn[i-1]}),pmn[i-1]}};
			pair<piii,piii> p=sovle2(b,a[i-1].fi+1);
			p2=p.fi,p3=p.se;
			if(max(p2.fi,p3.fi)<=x)return 1;
			return 0;
		}
	}
	p1={max({1ll,a[n-1].fi-a[0].fi,pmx[n-1]-pmn[n-1]}),{a[0].fi,pmn[n-1]}},p2={1,{inf,inf}},p3={1,{-inf,-inf}};
	return 1;
}
bool check(int x){
	if(calc3(x))return 1;
	for(int i=0;i<a.size();i++)a[i].fi=-a[i].fi;
	if(calc3(x)){
		p1.se.fi=-p1.se.fi,p2.se.fi=-p2.se.fi,p3.se.fi=-p3.se.fi;
		p1.se.fi-=p1.fi,p2.se.fi-=p2.fi,p3.se.fi-=p3.fi;
		for(int i=0;i<a.size();i++)a[i].fi=-a[i].fi;
		return 1;
	}
	for(int i=0;i<a.size();i++)a[i].fi=-a[i].fi;
	for(int i=0;i<a.size();i++)swap(a[i].fi,a[i].se);
	if(calc3(x)){
		swap(p1.se.fi,p1.se.se),swap(p2.se.fi,p2.se.se),swap(p3.se.fi,p3.se.se);
		for(int i=0;i<a.size();i++)swap(a[i].fi,a[i].se);
		return 1;
	}
	for(int i=0;i<a.size();i++)a[i].fi=-a[i].fi;
	if(calc3(x)){
		p1.se.fi=-p1.se.fi,p2.se.fi=-p2.se.fi,p3.se.fi=-p3.se.fi;
		p1.se.fi-=p1.fi,p2.se.fi-=p2.fi,p3.se.fi-=p3.fi;
		swap(p1.se.fi,p1.se.se),swap(p2.se.fi,p2.se.se),swap(p3.se.fi,p3.se.se);
		for(int i=0;i<a.size();i++)a[i].fi=-a[i].fi;
		for(int i=0;i<a.size();i++)swap(a[i].fi,a[i].se);
		return 1;
	}
	for(int i=0;i<a.size();i++)a[i].fi=-a[i].fi;
	for(int i=0;i<a.size();i++)swap(a[i].fi,a[i].se);
	return 0;
}
void work(){
	n=read();k=read();a.resize(n);
	for(int i=0;i<n;i++)a[i]={read(),read()};
	if(k==1)return sovle1();
	if(k==2){
		auto[p1,p2]=sovle2(a);
		printf("%lld %lld %lld\n",p1.se.fi,p1.se.se,p1.fi);
		printf("%lld %lld %lld\n",p2.se.fi,p2.se.se,p2.fi);
		return ;
	}
	int l=1,r=2e9,res=2e9;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	// cout<<res<<"\n";
	check(res);
	printf("%lld %lld %lld\n",p1.se.fi,p1.se.se,p1.fi);
	printf("%lld %lld %lld\n",p2.se.fi,p2.se.se,p2.fi);
	printf("%lld %lld %lld\n",p3.se.fi,p3.se.se,p3.fi);
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