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

int n,res=inf;
struct nd{
	int num,id;
}a[maxn],b[maxn];
bool cmp(nd u,nd v){return u.num<v.num;}
int sum[maxn],ans[maxn];

signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		int u=read()*2,v=read()*2;
		a[i]={(u+v)/2,i};b[i]={(u-v)/2,i};
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i].num;
	for(int i=1;i<=n;i++)ans[a[i].id]+=(i-1)*a[i].num-sum[i-1];
	for(int i=n;i>=1;i--)sum[i]=sum[i+1]+a[i].num;
	for(int i=1;i<=n;i++)ans[a[i].id]+=sum[i+1]-(n-i)*a[i].num;
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i].num;
	for(int i=1;i<=n;i++)ans[b[i].id]+=(i-1)*b[i].num-sum[i-1];
	for(int i=n;i>=1;i--)sum[i]=sum[i+1]+b[i].num;
	for(int i=1;i<=n;i++)ans[b[i].id]+=sum[i+1]-(n-i)*b[i].num;
	for(int i=1;i<=n;i++)res=min(res,ans[i]);
	printf("%lld\n",res/2);
}
