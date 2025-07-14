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

int a,t,p,ans;
//a^x=t(mod p),gcd(a,p)=1
map<int,int> mp;
int bsgs(int a,int t,int mod){
	int mul=1;
	int s=sqrt(mod)+1;
	for(int i=1;i<=s;i++){
		mul=mul*a%mod;
		mp[t*mul%mod]=i;
	}
	int cur=mul;
	for(int i=1;i<=s;i++){
		if(mp[cur])return i*s-mp[cur];
		cur=cur*mul%mod;
	}
	return -1;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	p=read();a=read();t=read();
	ans=bsgs(a,t,p);
	if(ans==-1)printf("no solution\n");
	else printf("%lld\n",ans);
}
