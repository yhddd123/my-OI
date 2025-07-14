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

int T,opt,a,b,p;
int ksm(int a,int b,int mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int bsgs(int a,int t,int mod){
	map<int,int> mp;
	int mul=1,cur;
	int s=sqrt(mod)+1;
	for(int i=1;i<=s;i++){
		mul=mul*a%mod;
		mp[t*mul%mod]=i;
	}
	cur=mul;
	for(int i=1;i<=s;i++){
		if(mp[cur])return i*s-mp[cur];
		cur=cur*mul%mod;
	}
	return -1;
}

signed main(){
	T=read();opt=read();
	while(T--){
		a=read();b=read();p=read();
		if(opt==1){
			a%=p;
			printf("%lld\n",ksm(a,b,p));
		}
		if(opt==2){
			a%=p;b%=p;
			if(!a&&b)printf("Orz, I cannot find x!\n");
			else printf("%lld\n",b*ksm(a,p-2,p)%p);
		}
		if(opt==3){
			a%=p;b%=p;
			if(!a&&!b)printf("1\n");
			else if(!a&&b)printf("Orz, I cannot find x!\n");
			else{
				int ans=bsgs(a,b,p);
				if(ans==-1)printf("Orz, I cannot find x!\n");
				else printf("%lld\n",ans);
			}
		}
	}
}
