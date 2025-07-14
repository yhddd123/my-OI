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

int a,b;
int p=1000000000;
map<int,int> mp;
int ph(int n){
	if(mp[n])return mp[n];
	int x=n,res=n;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			while(x%i==0)x/=i;
			res=res*(i-1)/i;
		}
	}
	if(x>1)res=res*(x-1)/x;
	return mp[n]=res;
}
int ksm(int a,int b,int mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		if(ans>=mod)ans%=mod,ans+=mod;
		if(a>=mod)a%=mod,a+=mod;
		b>>=1;
	}
	return ans;
}
int s(int n,int m,int mod){
	if(!m||mod==1)return 1;
	return ksm(n,s(n,m-1,ph(mod)),mod);
}
int st[12],tp;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		a=read();b=read();
		if(!a){
			if(b&1)printf("0\n");
			else printf("1\n");
			continue;
		}
		int ans=s(a,b,p);
		if(ans>=p){
			printf("...");
			ans%=p;tp=0;
			while(ans){
				st[++tp]=ans%10;
				ans/=10;
			}
			for(int i=tp+1;i<=9;i++)st[i]=0;
			for(int i=9;i>=1;i--)printf("%lld",st[i]);
			printf("\n");
		}
		else printf("%lld\n",ans);
	}
}
