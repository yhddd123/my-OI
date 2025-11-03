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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,k,a[maxn];
bool vis[maxn];
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read(),vis[i]=0;
	int ans=0;for(int i=1;i<n;i++)ans+=(__gcd(a[i],a[i+1])==1);
	vector<pii> pos;
	for(int l=1;l<=n;l++){
		int r=l;while(r<=n&&a[r]==1)r++;r--;
		if(a[l]==1){
			if(l<r)pos.pb({l,r});
			l=r;
		}
	}
	sort(pos.begin(),pos.end(),[&](pii u,pii v){
		if(u.fi==1||u.se==n)return false;
		if(v.fi==1||v.se==n)return true;
		return u.se-u.fi<v.se-v.fi;});
	for(int i=2;i<n;i++)if(k){
		if(__gcd(a[i-1],a[i])==1&&__gcd(a[i],a[i+1])==1&&a[i-1]!=1&&a[i+1]!=1&&!vis[i-1]&&!vis[i+1])vis[i]=1,ans-=2,k--;
	}
	for(auto[l,r]:pos){
		// cout<<l<<" "<<r<<"\n";
		if(l==1){
			for(int i=r;i>=l;i--)if(k)vis[i]=1,ans-=(i+1<=n)+(i==l&&i-1>=1),k--;
		}
		else{
			for(int i=l;i<=r;i++)if(k)vis[i]=1,ans-=(i-1>=1)+(i==r&&i+1<=n),k--;
		}
	// cout<<ans<<" "<<k<<"\n";
	}
	for(int i=1;i<n;i++)if(__gcd(a[i],a[i+1])==1&&!vis[i]&&!vis[i+1]&&k)ans--,k--;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("arrange.in","r",stdin);
	// freopen("arrange.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}