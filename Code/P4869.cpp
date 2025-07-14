#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 10086
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

int n,q,a[maxn],ans;
struct basis{
	int p[65],cnt;
	bool insert(int x){
		for(int i=30;~i;i--)if(x&(1ll<<i)){
			if(!p[i]){
				p[i]=x;++cnt;
				return true;
			}
			x^=p[i];
		}
		return false;
	}
	int query(){
		int ans=0;
		for(int i=30;~i;i--){
			ans=max(ans,ans^p[i]);
		}
		return ans;
	}
}b;
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
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b.insert(a[i]);
	q=read();int num=0;
	for(int i=0;i<=30;i++)if(b.p[i]){
		if(q&(1ll<<i))ans+=(1ll<<num);
		num++;
	}
	ans=(ans*ksm(2,n-b.cnt)+1)%mod;
	printf("%lld\n",ans);
}
