#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int a,b,c,d,xa,ya,xb,yb,xc,yc,xd,yd;
void work(){
	a=read(),b=read(),c=read(),d=read();
	xa=0,ya=sqrt(a);
	int v=(2*ya*ya+b-d)/(2*ya);
	// cout<<v<<"\n";
	xb=(-2*v+sqrt(4*v*v-4*2*(v*v-b)))/(2*2),yb=v+xb;
	// cout<<4*v*v-4*2*(v*v-b)<<" "<<xb<<" "<<yb<<"\n";
	xd=ya-yb,yd=ya+xb;xc=xb+xd-xa,yc=yb+yd-ya;
	if(xb*xb+yb*yb==b&&xc*xc+yc*yc==c&&xd*xd+yd*yd==d){
		printf("%lld %lld %lld %lld %lld %lld %lld\n",ya,xb,yb,xc,yc,xd,yd);
		return ;
	}
	xb=(-2*v-sqrt(4*v*v-4*2*(v*v-b)))/(2*2),yb=v+xb;
	xd=ya-yb,yd=ya+xb;xc=xb+xd-xa,yc=yb+yd-ya;
	if(xb*xb+yb*yb==b&&xc*xc+yc*yc==c&&xd*xd+yd*yd==d){
		printf("%lld %lld %lld %lld %lld %lld %lld\n",ya,xb,yb,xc,yc,xd,yd);
		return ;
	}
	v=(2*ya*ya+d-b)/(2*ya);
	// cout<<v<<"\n";
	xd=(-2*v+sqrt(4*v*v-4*2*(v*v-d)))/(2*2),yd=v+xd;
	xb=ya-yd,yb=ya+xd;xc=xb+xd-xa,yc=yb+yd-ya;
	if(xb*xb+yb*yb==b&&xc*xc+yc*yc==c&&xd*xd+yd*yd==d){
		printf("%lld %lld %lld %lld %lld %lld %lld\n",ya,xb,yb,xc,yc,xd,yd);
		return ;
	}
	xd=(-2*v-sqrt(4*v*v-4*2*(v*v-d)))/(2*2),yd=v+xd;
	xb=ya-yd,yb=ya+xd;xc=xb+xd-xa,yc=yb+yd-ya;
	if(xb*xb+yb*yb==b&&xc*xc+yc*yc==c&&xd*xd+yd*yd==d){
		printf("%lld %lld %lld %lld %lld %lld %lld\n",ya,xb,yb,xc,yc,xd,yd);
		return ;
	}
	
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
