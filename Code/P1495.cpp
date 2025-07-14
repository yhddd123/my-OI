#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],b[maxn],c[maxn];
int mul=1,ans;
inline int ksm(int a,int b,int mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;y=0;
		return ;
	}
	exgcd(b,a%b,x,y);
	int tmp=x;x=y;y=tmp-y*(a/b);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();b[i]=read();
		mul*=a[i];
	}
	for(int i=1;i<=n;i++){
		int x=0,y=0;
		//ax+by=1;
		//(mul/a[i])x+a[i]*y=1
		//(mul/a[i])x==1-a[i]*y(mod a[i])
		exgcd(mul/a[i],a[i],x,y);
		if(x<0)x+=a[i];
		ans+=mul/a[i]*b[i]%mul*x%mul;
		ans%=mul;
	}
	printf("%lld\n",ans);
}
