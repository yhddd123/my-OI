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
const int inf=1e15;
bool mbe;

int n;db c;
db a[maxn];
void work(){
	c=read();n=read();
	db l=0,r=inf;
	for(int i=1;i<=n;i++){
		db x=read(),y=read();
		db d=x*sqrtl(c*c*c*c-4.0*5*(y*c*c+5*x*x));
		db pl=(x*c*c-d)/(2.0*5*x*x),pr=(x*c*c+d)/(2.0*5*x*x);
		// cout<<d<<" "<<pl<<" "<<pr<<"\n";
		l=max(l,pl),r=min(r,pr);
	}
	printf("%.3Lf\n",l+0.001);
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