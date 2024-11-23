// Problem: P5656 【模板】二元一次不定方程 (exgcd)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5656
// Memory Limit: 16 MB
// Time Limit: 500000 ms
// Written by yhm.
// Start codeing:2024-10-17 15:02:35
// 
// Powered by CP Editor (https://cpeditor.org)

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

int a,b,c,g;
void exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1,y=0;
		return ;
	}
	exgcd(b,a%b,x,y);
	int p=x;
	x=y,y=p-(a/b)*y;
}
void work(){
	a=read(),b=read(),c=read(),g=__gcd(a,b);
	if(c%g){puts("-1");return ;}
	int x0=0,y0=0;
	exgcd(a,b,x0,y0);
	int x1=x0*c/g,y1=y0*c/g;
	int dx=b/g,dy=a/g;
	int l=(-x1+1+dx-1)/dx,r=(y1-1)/dy;
	if(x1+l*dx<=0)l++;
	if(y1-r*dy<=0)r--;
	if(x1+(l-1)*dx>0)l--;
	if(y1-(r+1)*dy>0)r++;
	int mnx=x1+l*dx,mny=y1-r*dy;
	if(l>r){printf("%lld %lld\n",mnx,mny);return ;}
	int mxx=x1+r*dx,mxy=y1-l*dy;
	printf("%lld %lld %lld %lld %lld\n",r-l+1,mnx,mny,mxx,mxy);
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
	
	T=read();
	while(T--)work();
}
