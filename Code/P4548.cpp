#include<bits/stdc++.h>
#define mod 10000
using namespace std;
inline int read(){
	int x=0,fl=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}
const int maxn=100010;

int n,m,ans,pw[maxn];
int x,a[maxn],fail[maxn];

signed main(){
	n=read();m=read();
	pw[0]=1;for(int i=1;i<=maxn-10;i++)pw[i]=pw[i-1]*n%mod;
	while(m--){
		x=read();
		for(int i=1;i<=x;i++)a[i]=read();
		for(int i=2,j=0;i<=x;i++){
			while(j&&a[i]!=a[j+1])j=fail[j];
			if(a[i]==a[j+1])j++;
			fail[i]=j;
		}
		ans=0;
		while(x){
			ans+=pw[x];ans%=mod;
			x=fail[x];
		}
		printf("%d%d%d%d\n",ans/1000,ans/100%10,ans/10%10,ans%10);
	}
}
