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

int p;
map<int,int> mp;
int ph(int n){
	if(mp[n])return mp[n];
	int x=n,res=n;
	for(int i=2;i*i<=n;i++){
		if(x%i==0){
			while(x%i==0)x/=i;
			res=res*(i-1)/i;
		}
	}
	if(x!=1)res=res*(x-1)/x;
	return mp[n]=res;
}
inline int ksm(int a,int b,int mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int s(int mod){
	if(mod==1)return 0;
	return ksm(2,s(ph(mod))+ph(mod),mod);
}

int T;
signed main(){
	T=read();
	while(T--){
		p=read();
		printf("%lld\n",s(p));
	}
}
