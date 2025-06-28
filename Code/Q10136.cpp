#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=200010;
const int inf=2e9;
bool mbe;

int n,a,b,c,d,e,f,g,h,ans;
void work(){
	cin>>a>>b>>c>>d>>e>>f>>g>>h;
	if(!b&&!d&&!f&&!h){cout<<min(a,e)*min(c,g)%mod<<"\n";return ;}
	n=max({a,b,c,d,e,f,g,h});
	if(n>2000)return ;
	for(int x=-n;x<=n;x++){
		for(int y=-n;y<=n;y++)if((x&1)==(y&1)){
			int val=1;
			if(x>=0)val=val*max(0ll,min(a-x,e)+1)%mod;
			else val=val*max(0ll,min(a,e+x)+1)%mod;
			if(y>=0)val=val*max(0ll,min(c-y,g)+1)%mod;
			else val=val*max(0ll,min(c,g+y)+1)%mod;
			if(x+y>=0)val=val*max(0ll,min(f-(x+y)/2,b)+1)%mod;
			else val=val*max(0ll,min(f,b+(x+y)/2)+1)%mod;
			if(x-y>=0)val=val*max(0ll,min(d-(x-y)/2,h)+1)%mod;
			else val=val*max(0ll,min(d,h+(x-y)/2)+1)%mod;
			// cout<<x<<" "<<y<<" "<<val<<"\n";
			(ans+=val)%=mod;
		}
	}
	(ans+=4*mod-(min(a,e)+min(c,g)+min(b,f)+min(d,h)+1))%=mod;
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