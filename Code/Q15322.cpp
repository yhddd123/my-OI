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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=100010;
const int maxm=1<<18;
const int inf=1e18;
bool mbe;

int n,c,a[maxn];
int f[maxn],val[maxm];
inline void chkmn(int &u,int v){(u>v)&&(u=v);}
void work(){
	n=read();c=read();
	for(int i=1;i<=n;i++)a[i]=read();a[++n]=0;
	mems(val,0x3f);
	for(int s=0;s<(1<<9);s++)chkmn(val[s],s-c);
	for(int i=1;i<=n;i++){
		int s1=a[i]&((1<<9)-1),s2=a[i]>>9;
		f[i]=inf;for(int s=0;s<(1<<9);s++)chkmn(f[i],val[s1|(s<<9)]+((s^s2)<<9)+i*c);
		for(int s=0;s<(1<<9);s++)chkmn(val[s|(s2<<9)],f[i]+(s^s1)-(i+1)*c);
	}
	printf("%lld\n",f[n]);
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