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

int n,ans,a[maxn];
void work(){
	n=read();ans=0;
	for(int i=0;i<n;i++)a[i]=read();
	bool fl=1;for(int i=1;i<=n;i++)fl&=(a[i]==0);
	if(fl){puts("0");return ;}
	multiset<pii> s;
	for(int i=0;i<n;i++)s.insert({a[i],i});
	int sum=0;for(int i=0;i<n;i++)sum+=a[i];
	if(sum<=0){puts("-1");return ;}
	while(ans<=3e6){
		int p=(*s.begin()).se;
		if(a[p]>=0)break;
		++ans;
		int p1=(p+n-1)%n,p2=(p+1)%n;
		s.erase(s.find({a[p],p}));
		s.erase(s.find({a[p1],p1}));
		s.erase(s.find({a[p2],p2}));
		a[p1]+=a[p],a[p2]+=a[p],a[p]=-a[p];
		s.insert({a[p],p});
		s.insert({a[p1],p1});
		s.insert({a[p2],p2});
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}