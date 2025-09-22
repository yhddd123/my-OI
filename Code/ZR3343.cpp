#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=150010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans[maxn];
#define lb(x) (x&(-x))
pii tree[maxn];
void upd(int x,pii w){
    while(x<=n)tree[x]=max(tree[x],w),x+=lb(x);
}
pii que(int x){
    pii res={-inf,0};
    while(x)res=max(res,tree[x]),x-=lb(x);
    return res;
}
void clr(){
    for(int i=1;i<=n;i++)tree[i]={-inf,0};
}
int tree1[maxn];
void upd1(int x,int w){
    while(x<=n)tree1[x]=max(tree1[x],w),x+=lb(x);
}
int que1(int x){
    int res=0;
    while(x)res=max(res,tree1[x]),x-=lb(x);
    return res;
}
void clr1(){
    for(int i=1;i<=n;i++)tree1[i]=0;
}
const int B=200;
int f[maxn],g[maxn];
pii dp[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)f[i]=-inf;f[0]=0;
    for(int i=1;i<=B&&i<=n;i++){
        int mx=0;g[0]=-inf;
        clr1();upd1(n,f[0]);
        for(int j=1;j<=n;j++){
            g[j]=max(mx,que1(a[j]))+1;
            upd1(a[j],g[j]);mx=max(mx,f[j]);
        }
        for(int j=0;j<=n;j++)f[j]=g[j];
        // for(int j=0;j<=n;j++)cout<<f[j]<<" ";cout<<"\n";
        mx=0;for(int j=1;j<=n;j++)mx=max(mx,f[j]);
        ans[i]=mx;
    }
    // for(int i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<"\n";
	for(int c=0,lst=n;c<=n/B;c++){
		clr();dp[0]={0,0};pii mx={0,0};
		for(int i=1;i<=n;i++){
			dp[i]=max(que(a[i]),{mx.fi-c,mx.se-1});dp[i].fi++;
			upd(a[i],dp[i]),mx=max(mx,dp[i]);
		}
		mx.se=-mx.se;
		// for(int i=1;i<=n;i++)cout<<dp[i].fi<<" "<<dp[i].se<<"\n";
		for(int j=mx.se;j<=lst;j++)ans[j]=mx.fi+j*c;
		lst=mx.se-1;
		// cout<<c<<" "<<lst<<"\n";
		if(lst<=B)break;
	}
    for(int i=1;i<=n;i++)write(ans[i]),putchar(' ');puts("");
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    read();T=read();
    while(T--)work();
}