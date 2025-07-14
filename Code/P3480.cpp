#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],ans;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		n=read();ans=0;
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=n;i>=1;i--)a[i]=a[i]-a[i-1];
		for(int i=n;i>=1;i-=2)ans^=a[i];
		if(ans)printf("TAK\n");
		else printf("NIE\n");
	}
}
