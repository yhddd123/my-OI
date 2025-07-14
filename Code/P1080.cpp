#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int maxn=10010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,ans,mul;
struct nd{
	int a,b;
	bool operator <(const nd &tmp)const{return a*b<tmp.a*tmp.b;}
}e[maxn];
void write(int x){
	static char buf[40];
	int len=-1;
	if(x<0) x=-x,putchar('-');
	do{
		buf[++len]=x%10+48;
		x/=10;
	}while(x);
	while(len>=0) putchar(buf[len--]);
}
signed main(){
	n=read();
	mul=read();e[0].b=read();
	for(int i=1;i<=n;i++){
		e[i].a=read();e[i].b=read();
	}
	sort(e+1,e+n+1);
	for(int i=1;i<=n;i++){
		ans=max(ans,mul/e[i].b);
		mul*=e[i].a;
	}
	write(ans);
}

