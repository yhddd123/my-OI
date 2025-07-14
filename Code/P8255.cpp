#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int x,z,y,n,m;
int T;
signed main(){
	T=read();
	while(T--){
		x=read();z=read();
		n=__gcd(z/x,x*x);
		m=sqrt(n);
		if(m*m!=n){
			printf("-1\n");
			continue;
		}
		if(z%(x*m)!=0){
			printf("-1\n");
			continue;
		}
		y=z/(x*m);
		printf("%lld\n",y);
	}
}

