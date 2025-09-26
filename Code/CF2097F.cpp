#include<bits/stdc++.h>
// #define int long long
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
const int maxn=13;
const int inf=1.7e9;
bool mbe;

int n,m,a[maxn],b[maxn],c[maxn];
int f[1<<maxn],g[maxn][1<<maxn][2];
inline void chkmn(int &u,int v){(u>v)&&(u=v);}
void work(){
	n=read();m=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int s=0;s<(1<<n);s++){
		f[s]=0;for(int i=0;i<n;i++)if(!(s&(1<<i)))f[s]+=a[i];
	}
	for(int i=1;i<=m;i++){
		for(int i=0;i<n;i++)a[i]=read();
		for(int i=0;i<n;i++)b[i]=read();
		for(int i=0;i<n;i++)c[i]=read();
		for(int i=0;i<=n;i++){
			for(int s=0;s<(1<<n+1);s++)g[i][s][0]=g[i][s][1]=inf;
		}
		for(int s=0;s<(1<<n);s++)g[0][s|((s&1)<<n)][(s>>n-1)&1]=f[s];
		for(int i=0,j=n-1,k=1;i<n;i++,j=(j==n-1?0:j+1),k=(k==n-1?0:k+1)){
			auto calc=[&](bool fl1,bool fl2,bool fl3,bool fl){
				if(fl)return 0;
				return fl1*c[j]+fl2*b[i]+fl3*a[k];
			};
			for(int s=0;s<(1<<n+1);s++){
				for(int fl=0;fl<2;fl++)if(g[i][s][fl]<=inf){
					chkmn(g[i+1][s][(s>>i)&1],g[i][s][fl]+calc(fl,(s>>i)&1,(s>>i+1)&1,(s>>i)&1));
					chkmn(g[i+1][s^(1<<i)][(s>>i)&1],g[i][s][fl]+calc(fl,(s>>i)&1,(s>>i+1)&1,((s>>i)&1)^1));
				}
			}
		}
		for(int s=0;s<(1<<n);s++){
			f[s]=min({g[n][s][0],g[n][s][1],g[n][s|(1<<n)][0],g[n][s|(1<<n)][1]});
		}
		write(f[0]),puts("");
	}
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