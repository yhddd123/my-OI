#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
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

int n,a[maxn],s[maxn];
unsigned long long ans;
int f[maxn],g[maxn];ull s1[maxn],s2[maxn];
void sovle(int l,int r){
	if(l==r){ans+=a[l];return ;}
	int mid=l+r>>1;
	sovle(l,mid),sovle(mid+1,r);
	f[mid]=g[mid]=a[mid],f[mid+1]=g[mid+1]=a[mid+1];
	for(int i=mid-1,mx=s[mid];i>=l;i--){
		mx=max(mx,s[i]);
		g[i]=max(g[i+1],s[mid]-s[i-1]);
		f[i]=max(f[i+1],mx-s[i-1]);
	}
	for(int i=mid+2,mx=-s[mid];i<=r;i++){
		mx=max(mx,-s[i-1]);
		g[i]=max(g[i-1],s[i]-s[mid]);
		f[i]=max(f[i-1],s[i]+mx);
	}
	s1[l-1]=0;for(int i=l;i<=mid;i++)s1[i]=s1[i-1]+f[i];
	s2[l-1]=0;for(int i=l;i<=mid;i++)s2[i]=s2[i-1]+g[i];
	for(int i=mid+1,p1=mid,p2=mid,p3=mid;i<=r;i++){
		while(p1>=l&&f[p1]<=f[i])p1--;
		while(p2>=l&&f[p2]<=g[p2]+g[i])p2--;
		while(p3>=l&&g[p3]+g[i]<=f[i])p3--;
		int pl=min(p1,p2),pr=max(p1,p3);
		// cout<<i<<" "<<pl<<" "<<pr<<"\n";
		if(l<=pl)ans+=s1[pl];
		if(pl+1<=pr)ans+=(s2[pr]-s2[pl])+1ull*(pr-pl)*g[i];
		if(pr+1<=mid)ans+=1ull*f[i]*(mid-pr);
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),s[i]=s[i-1]+a[i];
	sovle(1,n);
	printf("%llu\n",ans);
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