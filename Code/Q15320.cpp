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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans=0;
int p[60];
void insert(int x){
	for(int i=59;i>=0;i--)if(x&(1ll<<i)){
		if(!p[i]){
			p[i]=x;
			return ;
		}
		x^=p[i];
	}
}
void init(){
	for(int i=0;i<=59;i++)p[i]=0;
}
int quemx(int lim){
	int res=0;
	for(int i=59;i>=0;i--)if(lim&(1ll<<i))res=max(res,res^p[i]);
	return res;
}
void work(){
	n=read();ans=0;
	int sum=0;for(int i=1;i<=n;i++)a[i]=read(),sum^=a[i];
	init();
	for(int i=1;i<=n;i++)insert(a[i]&((1ll<<60)-1-sum));
	ans=max(sum,quemx((1ll<<60)-1-sum));
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