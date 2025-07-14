#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
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

int a,b,c,t[maxn],mxt;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	a=read();b=read();c=read();
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			for(int k=1;k<=c;k++)t[i+j+k]++;
		}
	}
	for(int i=1;i<=a+b+c;i++)if(t[i]>t[mxt])mxt=i;
	printf("%lld\n",mxt);
}
