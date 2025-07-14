#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans;
struct nd{
	int x,val;
}a[maxn];
bool cmp(nd u,nd v){return u.val>v.val;}
namespace bas{
	const int N=65,bit=61;
	int p[N],cnt;
	bool insert(int x){
		for(int i=bit;i>=0;i--)if(x&(1ll<<i)){
			if(!p[i]){
				++cnt;
				p[i]=x;
				return true;
			}
			x^=p[i];
		}
		return false;
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
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		bool fl=bas::insert(a[i].x);
		if(fl)ans+=a[i].val;
	}
	printf("%lld\n",ans);
}
