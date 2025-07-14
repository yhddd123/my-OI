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

int p,a,b,x,t;
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
int y,ans;
int bsgs(int a,int t,int p){
	map<int,int> mp;
	int mul=1,cur;
	int s=sqrt(p)+1;
	for(int i=1;i<=s;i++){
		mul=mul*a%p;
		mp[mul*t%p]=i;
	}
	cur=mul;
	for(int i=1;i<=s;i++){
		if(mp[cur])return i*s-mp[cur];
		cur=cur*mul%p;
	}
	return -2;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		p=read();a=read();b=read();x=read();t=read();
		if(t==x)printf("1\n");
		else if(!a){
			if(b==t)printf("2\n");
			else printf("-1\n");
		}
		else if(a!=1){
			y=(t-b*ksm(1-a+p,p-2)%p+p)%p*ksm((x-b*ksm(1-a+p,p-2)%p+p)%p,p-2)%p;
//			cout<<y<<"\n";
			ans=bsgs(a,y,p)+1;
			printf("%lld\n",ans);
		}
		else{
			t-=x;t+=p;t%=p;
			if(t%(__gcd(b,p)))printf("-1\n");
			else{
				ans=(t*ksm(b,p-2)+1)%p;
				if(!ans)printf("%lld\n",p);
				else printf("%lld\n",ans);
			}
		}
	}
}
