#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,ans;
void work(){
	n=read();
	for(int a=1;(a*a+1)*a<=n;a++){
		for(int b=a;(a*b+1)*b<=n;b++){
			if(n%(a*b+1)==0)ans+=1+(a!=b);
		}
	}
	for(int a=1;(a*(a+1)+1)*a<=n;a++){
		for(int c=a;(a*(c+1)+1)*c<=n;c++){
			if(n%c==0&&(n/c-1)%a==0&&c<(n/c-1)/a)ans+=2;
		}
	}
	for(int c=1;((c+1)*(c+1)+1)*c<=n;c++){
		for(int a=c+1;(a*a+1)*c<=n;a++){
			if(n%c==0&&(n/c-1)%a==0&&c<(n/c-1)/a)ans+=1+(a!=(n/c-1)/a);
		}
	}	
	printf("%lld\n",ans+1);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}