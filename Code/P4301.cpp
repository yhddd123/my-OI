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

int n,a[maxn];
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
int ans,num;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		bas::insert(a[i]);
		if(bas::cnt+num<i)num++,ans+=a[i];
	}
	printf("%lld\n",ans);
}
