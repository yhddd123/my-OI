#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
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

int n,a[maxn];
namespace bas{
	const int bit=50,N=55;
	int p[N];
	void insert(int x){
		for(int i=bit;i>=0;i--)if(x&(1ll<<i)){
			if(!p[i]){
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

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)bas::insert(a[i]);
	printf("%lld\n",bas::quemx(0));
}
