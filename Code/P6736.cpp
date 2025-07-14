#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int a,n,b,p;
int bsgs(int a,int t,int mod){
	map<int,int> mpp;
	int mul=1,cur=1,s=sqrt(mod)+1;
	for(int i=1;i<=s;i++){
		mul=mul*a%mod;
		mpp[t*mul%mod]=i;
	}
	for(int i=1;i<=s;i++){
		cur=cur*mul%mod;
		if(mpp[cur])return i*s-mpp[cur];
	}
	return -1;
}
map<int,int> mp;
int ph(int n){
	if(mp[n])return mp[n];
	int x=n,res=n;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			while(x%i==0)x/=i;
			res=res/i*(i-1);
		}
	}
	if(x!=1)res=res/x*(x-1);
	return mp[n]=res;
}
inline int ksm(int a,int b,int mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
		if(ans>=mod)ans%=mod,ans+=mod;
		if(a>=mod)a%=mod,a+=mod;
	}
	return ans;
}
int s(int n,int r,int mod){
	if(!r||mod==1)return 1;
	return ksm(n,s(n,r-1,ph(mod)),mod);
}

int T;
signed main(){
	T=read();mp[1]=1;
	while(T--){
		a=read();n=read();b=read();p=read();
		if(b==1||p==1){
			printf("0\n");
			continue;
		}
		b%=p;
		if(n==1)printf("%lld\n",bsgs(a,b,p));
		else if(n==2){
			bool fl=0;
			for(int i=1;i<=30;i++){
				if(s(a,i,p)%p==b){
					printf("%lld\n",i);
					fl=1;break;
				}
			}
			if(!fl)printf("-1\n");
		}
		else{
			if(a%p==b)printf("1\n");
			else if(a==1){
				if(b==1)printf("0\n");
				else printf("-1\n");
			}
			else if(a==2){
				if(b==4%p)printf("2\n");
				else if(b==65536%p)printf("3\n");
				else if(b==s(a,30,p)%p)printf("4\n");
				else printf("-1\n");
			}
			else if(b==s(a,a,p)%p)printf("2\n");
			else if(b==s(a,30,p)%p)printf("3\n");
			else printf("-1\n");
		}
	}
}
