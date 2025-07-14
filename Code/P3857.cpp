#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 2008
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

int n,m,a[maxn];
char c[maxn];
namespace bas{
	const int bit=50,N=55;
	int p[N],cnt;
	void insert(int x){
		for(int i=bit;i>=0;i--)if(x&(1ll<<i)){
			if(!p[i]){
				++cnt;
				p[i]=x;
				return ;
			}
			x^=p[i];
		}
	}
	int quemx(int x){
		for(int i=bit;i>=0;i--)x=max(x,x^p[i]);
		return x;
	}
}
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	m=read();n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c);
		for(int j=0;j<m;j++)a[i]+=(c[j]=='O')*(1ll<<j);
		bas::insert(a[i]);
	}
	printf("%lld\n",ksm(2,bas::cnt));
}
