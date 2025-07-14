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

int n,a[maxn],x,cnt;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		n=read();x=0;cnt=0;
		for(int i=1;i<=n;i++)a[i]=read(),x^=a[i],cnt+=(a[i]==1);
		if(cnt==n){
			if(n&1)printf("Brother\n");
			else printf("John\n");
		}
		else{
			if(!x)printf("Brother\n");
			else printf("John\n");
		}
	}
}
