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
inline void write128(__int128 x){static char buf[40];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m=1,q;__int128 ans;
// int pp[maxn];
unordered_map<int,int> mp;
int p(int i){
	if(mp[i])return mp[i];
	int res=(m-i+1)/2;
	if(!((m-i)&1)&&i>=m-2*n+2)res++;
	return mp[i]=res;
}
int calc(int l,int r){return (l+r)*(r-l+1)/2;}
__int128 calc1(int n){return (__int128)n*(n+1)*(2*n+1)/6;}
int pre(int i){
	if(i<0)return 0;
	int res=0;
	if(!i)return p(i);
	if(m&1){
		if(i&1)return res=pre(i-1)+p(i);
		else res+=p(0)+2*calc(m/2-i/2+1,m/2);
	}
	else{
		if(i&1)res+=2*calc(m/2-(i+1)/2+1,m/2);
		else return pre(i-1)+p(i);
	}
	if(i>=m-2*n+1)res+=(i-m+2*n)/2;
	return res;
}
void work(){
	// for(int i=1;i<=20;i++){
		// for(int j=0;j<=i;j++)cout<<setw(7)<<(((i-j)&1)?(1<<j)*(i-j):0);cout<<"\n";
	// }
	n=read();q=read();
	// while(n){
		// if(n<(m+1)/2)break;
		// ans+=(__int128)(m+1)/2*m;
		// n-=(m+1)/2,m++;
	// }
	// m--;
	int l=0,r=2000000000,res=0;
	while(l<=r){
		int mid=l+r>>1;
		int val=2*calc(1,(mid+1)/2)+((mid&1)?-(mid+1)/2:0);
		if(val<=n)res=mid,l=mid+1;
		else r=mid-1;
	}
	m=res,n-=2*calc(1,(m+1)/2)+((m&1)?-(m+1)/2:0);
	// cout<<m<<" "<<n<<"\n";
	ans=(__int128)(4*calc1((m+1)/2)-calc(1,(m+1)/2)+((m&1)?-(m+1)/2*(m+1):0));
	ans+=(__int128)n*(m+1);
	write128(ans),puts("");
	// for(int i=0;i<=m;i++)pp[i]=(m-i+1)/2;
	// for(int i=m;i>=m-2*n+2;i-=2)pp[i]++;
	// for(int i=0;i<=m;i++)cout<<pp[i]<<" "<<p(i)<<" "<<pre(i)<<"\n";
	while(q--){
		int len=read();
		int l=0,r=m,res=m;
		while(l<=r){
			int mid=l+r>>1;
			if(pre(mid-1)+2*p(mid)-1>=len)res=mid,r=mid-1;
			else l=mid+1;
		}
		// cout<<res<<" "<<len<<"\n";
		len-=pre(res-1);
		for(int i=res;i<=m;i++){
			if(len>2*p(i)-1)len-=p(i);
			else{
				if(len&1){write(len+i),puts("");break;}
				else len>>=1;
			}
		}
	}
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