#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,fl=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}
const int maxn=15;
int n,a[maxn],b[maxn],ans;
__int128 res,mul=1;
void exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;y=0;
		return ;
	}
	exgcd(b,a%b,x,y);
	int tmp=x;x=y;y=tmp-y*(a/b);
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read(),mul*=b[i];
	for(int i=1;i<=n;i++)a[i]=(a[i]%b[i]+b[i])%b[i];
	for(int i=1;i<=n;i++){
		int x,y;
		exgcd(mul/b[i],b[i],x,y);
		x=(x%b[i]+b[i])%b[i];
		res+=mul/b[i]*x%mul*a[i]%mul;res%=mul;
	}
	ans=res;
	printf("%lld\n",ans);
}
