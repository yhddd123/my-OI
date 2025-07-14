#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
int ans[maxn],tp;
void mul(int x){
	for(int i=1;i<=tp;i++)ans[i]*=x;
	for(int i=1;i<=tp;i++){
		if(ans[i]>=10)ans[i+1]+=ans[i]/10,ans[i]%=10;
	}
	while(ans[tp+1])tp++,ans[tp+1]+=ans[tp]/10,ans[tp]%=10;
}
void work(){
	n=read();ans[tp=1]=1;
	while(n>4)mul(3),n-=3;
	mul(n);
	printf("%lld\n",tp);
	for(int i=tp;i>=max(1ll,tp-99);i--)printf("%lld",ans[i]);
}
bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
